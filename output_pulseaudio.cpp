#include "stdafx.h"
#include "SDK/output.h"
#include "SDK/core_api.h"
#include <sstream>
#include <windows.h>
#include <pathcch.h>
#include <mutex>
#include "pulse.h"

namespace {
	typedef HRESULT(CALLBACK* LPFNDLLFUNC1)(DWORD, UINT*);
	static pa_strerror g_pa_strerror;
	static pa_threaded_mainloop_new g_pa_threaded_mainloop_new;
	static pa_threaded_mainloop_free g_pa_threaded_mainloop_free;
	static pa_threaded_mainloop_start g_pa_threaded_mainloop_start;
	static pa_threaded_mainloop_stop g_pa_threaded_mainloop_stop;
	static pa_threaded_mainloop_lock g_pa_threaded_mainloop_lock;
	static pa_threaded_mainloop_unlock g_pa_threaded_mainloop_unlock;
	static pa_threaded_mainloop_wait g_pa_threaded_mainloop_wait;
	static pa_threaded_mainloop_signal g_pa_threaded_mainloop_signal;
	static pa_threaded_mainloop_accept g_pa_threaded_mainloop_accept;
	static pa_threaded_mainloop_get_retval g_pa_threaded_mainloop_get_retval;
	static pa_threaded_mainloop_get_api g_pa_threaded_mainloop_get_api;
	static pa_stream_new g_pa_stream_new;
	static pa_stream_connect_playback g_pa_stream_connect_playback;
	static pa_stream_disconnect g_pa_stream_disconnect;
	static pa_stream_unref g_pa_stream_unref;
	static pa_stream_write g_pa_stream_write;
	static pa_stream_cancel_write g_pa_stream_cancel_write;
	static pa_stream_drop g_pa_stream_drop;
	static pa_stream_writable_size g_pa_stream_writable_size;
	static pa_stream_drain g_pa_stream_drain;
	static pa_stream_set_write_callback g_pa_stream_set_write_callback;
	static pa_stream_set_state_callback g_pa_stream_set_state_callback;
	static pa_stream_set_started_callback g_pa_stream_set_started_callback;
	static pa_stream_set_underflow_callback g_pa_stream_set_underflow_callback;
	static pa_stream_cork g_pa_stream_cork;
	static pa_stream_flush g_pa_stream_flush;
	static pa_stream_update_sample_rate g_pa_stream_update_sample_rate;
	static pa_stream_get_state g_pa_stream_get_state;
	static pa_stream_get_sample_spec g_pa_stream_get_sample_spec;
	static pa_stream_get_latency g_pa_stream_get_latency;
	static pa_stream_get_timing_info g_pa_stream_get_timing_info;
	static pa_stream_trigger g_pa_stream_trigger;
	static pa_stream_update_timing_info g_pa_stream_update_timing_info;
	static pa_proplist_new g_pa_proplist_new;
	static pa_proplist_free g_pa_proplist_free;
	static pa_proplist_set g_pa_proplist_set;
	static pa_proplist_sets g_pa_proplist_sets;
	static pa_proplist_setp g_pa_proplist_setp;
	static pa_context_new_with_proplist g_pa_context_new_with_proplist;
	static pa_context_unref g_pa_context_unref;
	static pa_context_connect g_pa_context_connect;
	static pa_context_disconnect g_pa_context_disconnect;
	static pa_context_get_state g_pa_context_get_state;
	static pa_context_set_state_callback g_pa_context_set_state_callback;
	static pa_context_set_event_callback g_pa_context_set_event_callback;
	static pa_operation_unref g_pa_operation_unref;
	static pa_bytes_to_usec g_pa_bytes_to_usec;
	static pa_usec_to_bytes g_pa_usec_to_bytes;
	static pa_channel_map_init_auto g_pa_channel_map_init_auto;
	static bool g_pa_is_loaded = false;
	static bool is_using_winelib = false;

	class output_pulse : public output_v4
	{
	public:
		output_pulse(const GUID& p_device, double p_buffer_length, bool p_dither, t_uint32 p_bitdepth)
			: buffer_length(p_buffer_length), m_incoming_ptr(0), progressing(false), draining(false), drained(false)
		{
			if (!g_pa_is_loaded)
			{
				console::error("Pulseaudio: dll could not be loaded");
				throw exception_output_invalidated();
			}

			mainloop = g_pa_threaded_mainloop_new();
			if (g_pa_threaded_mainloop_start(mainloop) < 0)
			{
				g_pa_threaded_mainloop_free(mainloop);
				console::error("Pulseaudio: failed to start playback thread");
				throw exception_output_invalidated();
			}
			pa_proplist* proplist = g_pa_proplist_new();
			g_pa_proplist_sets(proplist, PA_PROP_APPLICATION_NAME, "foobar2000");
			g_pa_proplist_sets(proplist, PA_PROP_APPLICATION_ID, "foobar2000");
			g_pa_proplist_sets(proplist, PA_PROP_APPLICATION_ICON_NAME, "foobar2000");

			pa_mainloop_api* api;
			g_pa_threaded_mainloop_lock(mainloop);
			api = g_pa_threaded_mainloop_get_api(mainloop);
			context = g_pa_context_new_with_proplist(api, "foobar2000", proplist);
			if (proplist != NULL) g_pa_proplist_free(proplist);

			g_pa_context_set_state_callback(context, context_state_cb, this);

			const char* server = is_using_winelib ? NULL : "127.0.0.1";
			if (g_pa_context_connect(context, server, (pa_context_flags_t)0, NULL) < 0
				|| context_wait(context, mainloop))
			{
				g_pa_context_unref(context);
				g_pa_threaded_mainloop_unlock(mainloop);
				g_pa_threaded_mainloop_stop(mainloop);
				g_pa_threaded_mainloop_free(mainloop);

				console::error("Pulseaudio: failed to connect");
				throw exception_output_invalidated();
			}

			g_pa_threaded_mainloop_unlock(mainloop);

			trigger_update.create(true, true);
		}
		~output_pulse()
		{
			trigger_update.release();

			g_pa_threaded_mainloop_lock(mainloop);

			close_stream();

			g_pa_context_disconnect(context);
			g_pa_context_set_state_callback(context, NULL, NULL);
			g_pa_context_unref(context);
			g_pa_threaded_mainloop_unlock(mainloop);
			g_pa_threaded_mainloop_stop(mainloop);
			g_pa_threaded_mainloop_free(mainloop);
		}

		void pause(bool p_state)
		{
			if (stream == NULL)
				return;

			g_pa_threaded_mainloop_lock(mainloop);
			pa_operation* op = g_pa_stream_cork(stream, p_state ? 1 : 0, NULL, NULL);
			if (op != NULL)
			{
				g_pa_operation_unref(op);
			}
			g_pa_threaded_mainloop_unlock(mainloop);
		}

		void volume_set(double p_val)
		{
		}

		void flush() {
			m_incoming_ptr = 0;
			m_incoming.set_size(0);
			if (stream == NULL)
				return;

			g_pa_threaded_mainloop_lock(mainloop);
			pa_operation* op = g_pa_stream_cork(stream, 1, NULL, NULL);
			if (op != NULL)
			{
				g_pa_operation_unref(op);
			}
			op = g_pa_stream_flush(stream, NULL, NULL);
			if (op != NULL)
			{
				g_pa_operation_unref(op);
			}
			op = g_pa_stream_cork(stream, 0, NULL, NULL);
			if (op != NULL)
			{
				g_pa_operation_unref(op);
			}
			g_pa_threaded_mainloop_unlock(mainloop);
		}

		void flush_changing_track() {
			flush();
		}

		void update(bool& p_ready) {
			p_ready = update_v2() > 0;
		}

		size_t update_v2() {
			trigger_update.set_state(false);

			if (m_incoming_spec != m_active_spec)
			{
				if (drained)
				{
					drained = false;
					open_incoming_spec();
				}
				else
				{
					force_play();
				}
			}

			size_t retCanWriteSamples = 0;
			if (m_incoming_spec == m_active_spec && m_incoming_ptr < m_incoming.get_size()) {
				retCanWriteSamples = write();
			}
			else if (m_incoming_ptr == m_incoming.get_size()) {
				retCanWriteSamples = SIZE_MAX;
			}
			return retCanWriteSamples;
		}

		void force_play()
		{
			if (draining)
				return;

			if (stream != NULL)
			{
				g_pa_threaded_mainloop_lock(mainloop);
				draining = true;
				drained = false;
				pa_operation* op = g_pa_stream_drain(stream, stream_drained_cb, this);
				if (op != NULL)
				{
					g_pa_operation_unref(op);
				}
				else
				{
					// nothing to drain
					draining = false;
					drained = true;
				}
				op = g_pa_stream_trigger(stream, NULL, NULL);
				if (op != NULL)
				{
					g_pa_operation_unref(op);
				}
				g_pa_threaded_mainloop_unlock(mainloop);
			}
			else
			{
				draining = false;
				drained = true;
			}
		}

		double get_latency() {
			double ret = 0;
			if (m_incoming_spec.is_valid()) {
				ret += audio_math::samples_to_time((m_incoming.get_size() - m_incoming_ptr) / m_incoming_spec.m_channels, m_incoming_spec.m_sample_rate);
			}
			if (m_active_spec.is_valid() && !drained) {
				pa_usec_t latency;
				if (stream != NULL && g_pa_stream_get_latency(stream, &latency, NULL) > -1)
				{
					ret += (latency * 0.000001);
				}
			}
			return ret;
		}

		void process_samples(const audio_chunk& p_chunk) {
			pfc::dynamic_assert(m_incoming_ptr == m_incoming.get_size());
			t_samplespec spec;
			spec.fromchunk(p_chunk);
			if (!spec.is_valid()) pfc::throw_exception_with_message< exception_io_data >("Invalid audio stream specifications");
			m_incoming_spec = spec;
			size_t length = p_chunk.get_used_size();
			m_incoming.set_data_fromptr(p_chunk.get_data(), length);
			m_incoming_ptr = 0;
		}

		bool is_progressing()
		{
			return progressing;
		}

		pfc::eventHandle_t get_trigger_event()
		{
			return trigger_update.get_handle();
		}

		static void g_enum_devices(output_device_enum_callback& p_callback) {
			const GUID device = { 0x8bf1c19, 0x5b9d, 0x4992, { 0x76, 0x18, 0x13, 0x8b, 0xa2, 0x1, 0xd7, 0xa6 } };
			if (g_pa_is_loaded || load_pulse_dll())
			{
				if (is_using_winelib)
				{
					p_callback.on_device(device, "native", 6);
				}
				else
				{
					p_callback.on_device(device, "localhost", 9);
				}
			}

		}
		static GUID g_get_guid() {
			static const GUID guid = { 0xfe94df9, 0xc8e2, 0x40a1, { 0x40, 0xa1, 0xb1, 0x2a, 0x4a, 0x6c, 0xe4, 0x9e } };
			return guid;
		}
		static bool g_advanced_settings_query() { return false; }
		static bool g_needs_bitdepth_config() { return false; }
		static bool g_needs_dither_config() { return false; }
		static bool g_needs_device_list_prefixes() { return true; }
		static bool g_supports_multiple_streams() { return false; }
		static bool g_is_high_latency() { return false; }
		static uint32_t g_extra_flags() { return 0; }
		static void g_advanced_settings_popup(HWND p_parent, POINT p_menupoint) {}
		static const char* g_get_name() { return "Pulseaudio"; }


	private:

		pa_context* context = NULL;
		pa_threaded_mainloop* mainloop = NULL;
		pa_stream* stream = NULL;

		pfc::array_t<audio_sample, pfc::alloc_fast_aggressive> m_incoming;
		size_t m_incoming_ptr;
		t_samplespec m_incoming_spec, m_active_spec;

		double buffer_length;

		bool progressing;
		bool draining;
		bool drained;

		pfc::event trigger_update;

		service_ptr_t<playback_control> playback_control;

		static bool context_wait(pa_context* ctx, pa_threaded_mainloop* ml)
		{
			pa_context_state_t state;
			while ((state = g_pa_context_get_state(ctx)) != PA_CONTEXT_READY)
			{
				if (state == PA_CONTEXT_FAILED || state == PA_CONTEXT_TERMINATED)
					return -1;
				g_pa_threaded_mainloop_wait(ml);
			}
			return 0;
		}

		static void context_state_cb(pa_context* ctx, void* userdata)
		{
			output_pulse* output = (output_pulse*)userdata;

			switch (g_pa_context_get_state(ctx))
			{
			case PA_CONTEXT_FAILED:
				console::error("Pulseaudio: connection failed");
				fb2k::inMainThread([]() {
					playback_control::get()->stop();
					});
			case PA_CONTEXT_READY:
			case PA_CONTEXT_TERMINATED:
				g_pa_threaded_mainloop_signal(output->mainloop, 0);
			default:
				break;
			}
		}

		static int stream_wait(pa_stream* s, pa_threaded_mainloop* ml)
		{
			pa_stream_state_t state;

			while ((state = g_pa_stream_get_state(s)) != PA_STREAM_READY) {
				if (state == PA_STREAM_FAILED || state == PA_STREAM_TERMINATED)
					return -1;
				g_pa_threaded_mainloop_wait(ml);
			}
			return 0;
		}

		static void stream_state_cb(pa_stream* s, void* userdata)
		{
			pa_threaded_mainloop* ml = (pa_threaded_mainloop*)userdata;

			switch (g_pa_stream_get_state(s)) {
			case PA_STREAM_READY:
			case PA_STREAM_FAILED:
			case PA_STREAM_TERMINATED:
				g_pa_threaded_mainloop_signal(ml, 0);
			default:
				break;
			}
		}

		static void stream_started_cb(pa_stream* s, void* userdata)
		{
			output_pulse* output = (output_pulse*)userdata;
			output->progressing = true;
		}

		static void stream_underflow_cb(pa_stream* s, void* userdata)
		{
			output_pulse* output = (output_pulse*)userdata;
			output->progressing = false;
			console::info("Pulseaudio: buffer underrun");
			output->trigger_update.set_state(true);
		}

		static void stream_write_cb(pa_stream* s, size_t nbytes, void* userdata)
		{
			output_pulse* output = (output_pulse*)userdata;
			output->trigger_update.set_state(true);
		}

		size_t write()
		{
			if (stream == NULL || m_incoming_spec != m_active_spec)
			{
				return 0;
			}

			g_pa_threaded_mainloop_lock(mainloop);
			size_t cw_samples = g_pa_stream_writable_size(stream) / sizeof(audio_sample);
			size_t delta = pfc::min_t(m_incoming.get_size() - m_incoming_ptr, cw_samples);
			if (g_pa_stream_write(stream, m_incoming.get_ptr() + m_incoming_ptr, delta * sizeof(audio_sample), NULL, 0, PA_SEEK_RELATIVE) < 0)
			{
				console::error("Pulseaudio: error writing to stream");
				return 0;
			}
			else
			{
				m_incoming_ptr += delta;
			}
			g_pa_threaded_mainloop_unlock(mainloop);

			return (cw_samples - delta) / m_incoming_spec.m_channels;
		}

		void close_stream()
		{
			if (stream != NULL)
			{
				g_pa_stream_set_state_callback(stream, NULL, NULL);
				g_pa_stream_set_started_callback(stream, NULL, NULL);
				g_pa_stream_set_underflow_callback(stream, NULL, NULL);
				g_pa_stream_set_write_callback(stream, NULL, NULL);
				g_pa_stream_disconnect(stream);
				g_pa_stream_unref(stream);
				stream = NULL;
				progressing = false;
			}
		}

		void open_incoming_spec()
		{
			if (!m_incoming_spec.is_valid())
				return;

			pa_sample_spec ss;
			ss.channels = m_incoming_spec.m_channels;
			ss.rate = m_incoming_spec.m_sample_rate;
			ss.format = PA_SAMPLE_FLOAT32LE;

			struct pa_channel_map map;
			const pa_channel_map* map_ptr = g_pa_channel_map_init_auto(&map, ss.channels, PA_CHANNEL_MAP_WAVEEX);

			pa_stream_flags_t flags =
				(pa_stream_flags_t)(PA_STREAM_INTERPOLATE_TIMING | PA_STREAM_AUTO_TIMING_UPDATE);

			struct pa_buffer_attr attr;
			attr.maxlength = ceil(m_incoming_spec.time_to_samples(buffer_length) * m_incoming_spec.m_channels * 4);
			attr.fragsize = 0;
			attr.minreq = (uint32_t)-1;
			attr.prebuf = (uint32_t)-1;
			attr.tlength = ceil(m_incoming_spec.time_to_samples(buffer_length) * m_incoming_spec.m_channels * 4);

			g_pa_threaded_mainloop_lock(mainloop);

			close_stream();

			stream = g_pa_stream_new(context, "Audio", &ss, map_ptr);
			progressing = false;
			if (stream == NULL) {
				g_pa_threaded_mainloop_unlock(mainloop);
				console::error("Pulseaudio: failed to create stream");
				throw exception_output_invalidated();
			}

			g_pa_stream_set_state_callback(stream, stream_state_cb, mainloop);
			g_pa_stream_set_started_callback(stream, stream_started_cb, this);
			g_pa_stream_set_underflow_callback(stream, stream_underflow_cb, this);
			g_pa_stream_set_write_callback(stream, stream_write_cb, this);

			if (g_pa_stream_connect_playback(stream, NULL, &attr,
				flags, NULL, NULL) < 0 || stream_wait(stream, mainloop))
			{
				g_pa_threaded_mainloop_unlock(mainloop);
				console::error("Pulseaudio: failed to connect stream");
				throw exception_output_invalidated();
			}

			m_active_spec = m_incoming_spec;

			g_pa_threaded_mainloop_unlock(mainloop);

			trigger_update.set_state(true);
		}

		static void stream_drained_cb(pa_stream* s, int success, void* userdata)
		{
			output_pulse* output = (output_pulse*)userdata;
			output->draining = false;
			output->drained = true;
			output->trigger_update.set_state(true);
		}

		static bool load_pulse_dll()
		{
			HMODULE libpulse;
			pfc::string_formatter path = core_api::get_my_full_path();
			path.truncate(path.scan_filename());
			std::wstringstream wpath_libpulse;
			wpath_libpulse << path << "pulse\\libpulse-0.dll";
			libpulse = LoadLibraryExW(wpath_libpulse.str().c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
			wchar_t szFullPath[MAX_PATH] = {};
			GetCurrentDirectory(MAX_PATH, szFullPath);
			if (libpulse == NULL)
			{
				std::stringstream error;
				error << "Could not load libpulse-0.dll: error code " << GetLastError();
				console::error(error.str().c_str());
				return false;
			}

			g_pa_strerror = (pa_strerror)GetProcAddress(libpulse, "pa_strerror");
			g_pa_threaded_mainloop_new = (pa_threaded_mainloop_new)GetProcAddress(libpulse, "pa_threaded_mainloop_new");
			g_pa_threaded_mainloop_free = (pa_threaded_mainloop_free)GetProcAddress(libpulse, "pa_threaded_mainloop_free");
			g_pa_threaded_mainloop_start = (pa_threaded_mainloop_start)GetProcAddress(libpulse, "pa_threaded_mainloop_start");
			g_pa_threaded_mainloop_stop = (pa_threaded_mainloop_stop)GetProcAddress(libpulse, "pa_threaded_mainloop_stop");
			g_pa_threaded_mainloop_lock = (pa_threaded_mainloop_lock)GetProcAddress(libpulse, "pa_threaded_mainloop_lock");
			g_pa_threaded_mainloop_unlock = (pa_threaded_mainloop_unlock)GetProcAddress(libpulse, "pa_threaded_mainloop_unlock");
			g_pa_threaded_mainloop_wait = (pa_threaded_mainloop_wait)GetProcAddress(libpulse, "pa_threaded_mainloop_wait");
			g_pa_threaded_mainloop_signal = (pa_threaded_mainloop_signal)GetProcAddress(libpulse, "pa_threaded_mainloop_signal");
			g_pa_threaded_mainloop_accept = (pa_threaded_mainloop_accept)GetProcAddress(libpulse, "pa_threaded_mainloop_accept");
			g_pa_threaded_mainloop_get_retval = (pa_threaded_mainloop_get_retval)GetProcAddress(libpulse, "pa_threaded_mainloop_get_retval");
			g_pa_threaded_mainloop_get_api = (pa_threaded_mainloop_get_api)GetProcAddress(libpulse, "pa_threaded_mainloop_get_api");

			g_pa_stream_new = (pa_stream_new)GetProcAddress(libpulse, "pa_stream_new");
			g_pa_stream_connect_playback = (pa_stream_connect_playback)GetProcAddress(libpulse, "pa_stream_connect_playback");
			g_pa_stream_disconnect = (pa_stream_disconnect)GetProcAddress(libpulse, "pa_stream_disconnect");
			g_pa_stream_unref = (pa_stream_unref)GetProcAddress(libpulse, "pa_stream_unref");
			g_pa_stream_write = (pa_stream_write)GetProcAddress(libpulse, "pa_stream_write");
			g_pa_stream_cancel_write = (pa_stream_cancel_write)GetProcAddress(libpulse, "pa_stream_cancel_write");
			g_pa_stream_drop = (pa_stream_drop)GetProcAddress(libpulse, "pa_stream_drop");
			g_pa_stream_writable_size = (pa_stream_writable_size)GetProcAddress(libpulse, "pa_stream_writable_size");
			g_pa_stream_drain = (pa_stream_drain)GetProcAddress(libpulse, "pa_stream_drain");
			g_pa_stream_set_write_callback = (pa_stream_set_write_callback)GetProcAddress(libpulse, "pa_stream_set_write_callback");
			g_pa_stream_set_state_callback = (pa_stream_set_state_callback)GetProcAddress(libpulse, "pa_stream_set_state_callback");
			g_pa_stream_set_started_callback = (pa_stream_set_started_callback)GetProcAddress(libpulse, "pa_stream_set_started_callback");
			g_pa_stream_set_underflow_callback = (pa_stream_set_underflow_callback)GetProcAddress(libpulse, "pa_stream_set_underflow_callback");
			g_pa_stream_cork = (pa_stream_cork)GetProcAddress(libpulse, "pa_stream_cork");
			g_pa_stream_flush = (pa_stream_flush)GetProcAddress(libpulse, "pa_stream_flush");
			g_pa_stream_update_sample_rate = (pa_stream_update_sample_rate)GetProcAddress(libpulse, "pa_stream_update_sample_rate");
			g_pa_stream_get_state = (pa_stream_get_state)GetProcAddress(libpulse, "pa_stream_get_state");
			g_pa_stream_get_sample_spec = (pa_stream_get_sample_spec)GetProcAddress(libpulse, "pa_stream_get_sample_spec");
			g_pa_stream_get_latency = (pa_stream_get_latency)GetProcAddress(libpulse, "pa_stream_get_latency");
			g_pa_stream_get_timing_info = (pa_stream_get_timing_info)GetProcAddress(libpulse, "pa_stream_get_timing_info");
			g_pa_stream_trigger = (pa_stream_trigger)GetProcAddress(libpulse, "pa_stream_trigger");
			g_pa_stream_update_timing_info = (pa_stream_update_timing_info)GetProcAddress(libpulse, "pa_stream_update_timing_info");

			g_pa_proplist_new = (pa_proplist_new)GetProcAddress(libpulse, "pa_proplist_new");
			g_pa_proplist_free = (pa_proplist_free)GetProcAddress(libpulse, "pa_proplist_free");
			g_pa_proplist_set = (pa_proplist_set)GetProcAddress(libpulse, "pa_proplist_set");
			g_pa_proplist_sets = (pa_proplist_sets)GetProcAddress(libpulse, "pa_proplist_sets");
			g_pa_proplist_setp = (pa_proplist_setp)GetProcAddress(libpulse, "pa_proplist_setp");

			g_pa_context_new_with_proplist = (pa_context_new_with_proplist)GetProcAddress(libpulse, "pa_context_new_with_proplist");
			g_pa_context_unref = (pa_context_unref)GetProcAddress(libpulse, "pa_context_unref");
			g_pa_context_connect = (pa_context_connect)GetProcAddress(libpulse, "pa_context_connect");
			g_pa_context_disconnect = (pa_context_disconnect)GetProcAddress(libpulse, "pa_context_disconnect");
			g_pa_context_get_state = (pa_context_get_state)GetProcAddress(libpulse, "pa_context_get_state");
			g_pa_context_set_state_callback = (pa_context_set_state_callback)GetProcAddress(libpulse, "pa_context_set_state_callback");
			g_pa_context_set_event_callback = (pa_context_set_event_callback)GetProcAddress(libpulse, "pa_context_set_event_callback");

			g_pa_channel_map_init_auto = (pa_channel_map_init_auto)GetProcAddress(libpulse, "pa_channel_map_init_auto");

			g_pa_operation_unref = (pa_operation_unref)GetProcAddress(libpulse, "pa_operation_unref");

			g_pa_bytes_to_usec = (pa_bytes_to_usec)GetProcAddress(libpulse, "pa_bytes_to_usec");
			g_pa_usec_to_bytes = (pa_usec_to_bytes)GetProcAddress(libpulse, "pa_usec_to_bytes");

			void* winelib = GetProcAddress(libpulse, "foo_out_pulse_winelib_dll");

			is_using_winelib = winelib != NULL;
			console::info(is_using_winelib ? "Pulseaudio: using winelib libpulse" : "Pulseaudio: Using Windows libpulse");

			if (g_pa_strerror == NULL ||
				g_pa_threaded_mainloop_new == NULL ||
				g_pa_threaded_mainloop_free == NULL ||
				g_pa_threaded_mainloop_start == NULL ||
				g_pa_threaded_mainloop_stop == NULL ||
				g_pa_threaded_mainloop_lock == NULL ||
				g_pa_threaded_mainloop_unlock == NULL ||
				g_pa_threaded_mainloop_wait == NULL ||
				g_pa_threaded_mainloop_signal == NULL ||
				g_pa_threaded_mainloop_accept == NULL ||
				g_pa_threaded_mainloop_get_retval == NULL ||
				g_pa_threaded_mainloop_get_api == NULL ||
				g_pa_stream_new == NULL ||
				g_pa_stream_connect_playback == NULL ||
				g_pa_stream_disconnect == NULL ||
				g_pa_stream_unref == NULL ||
				g_pa_stream_write == NULL ||
				g_pa_stream_cancel_write == NULL ||
				g_pa_stream_drop == NULL ||
				g_pa_stream_writable_size == NULL ||
				g_pa_stream_drain == NULL ||
				g_pa_stream_set_write_callback == NULL ||
				g_pa_stream_set_state_callback == NULL ||
				g_pa_stream_set_started_callback == NULL ||
				g_pa_stream_set_underflow_callback == NULL ||
				g_pa_stream_cork == NULL ||
				g_pa_stream_flush == NULL ||
				g_pa_stream_update_sample_rate == NULL ||
				g_pa_stream_get_state == NULL ||
				g_pa_stream_get_sample_spec == NULL ||
				g_pa_stream_get_latency == NULL ||
				g_pa_stream_get_timing_info == NULL ||
				g_pa_stream_trigger == NULL ||
				g_pa_stream_update_timing_info == NULL ||
				g_pa_proplist_new == NULL ||
				g_pa_proplist_free == NULL ||
				g_pa_proplist_set == NULL ||
				g_pa_proplist_sets == NULL ||
				g_pa_proplist_setp == NULL ||
				g_pa_context_new_with_proplist == NULL ||
				g_pa_context_unref == NULL ||
				g_pa_context_connect == NULL ||
				g_pa_context_disconnect == NULL ||
				g_pa_context_get_state == NULL ||
				g_pa_context_set_state_callback == NULL ||
				g_pa_context_set_event_callback == NULL ||
				g_pa_channel_map_init_auto == NULL ||
				g_pa_operation_unref == NULL ||
				g_pa_bytes_to_usec == NULL ||
				g_pa_usec_to_bytes == NULL)
			{
				console::error("Could not load libpulse-0.dll");
				return false;
			}

			g_pa_is_loaded = true;
			return true;
		}
	};

	static output_factory_t<output_pulse> g_output_pulse_factory;
}