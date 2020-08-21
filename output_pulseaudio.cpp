#include "stdafx.h"
#include "SDK/output.h"
#include "SDK/core_api.h"
#include <sstream>
#include <windows.h>
#include <pathcch.h>
#include <mutex>
#include "pulse.h"

//static const GUID guid_pulseaudio_branch = { 0x18564ced, 0x4abf, 0x4f0c, { 0xa4, 0x43, 0x98, 0xda, 0x88, 0xe2, 0xcd, 0x39 } };
//static const GUID guid_pulseaudio_cfg_destination_port = { 0xe7598963, 0xed60, 0x4084, { 0xa8, 0x5d, 0xd1, 0xcd, 0xc5, 0x51, 0x22, 0xca } };

//static advconfig_branch_factory g_pulseaudio_output_branch("Pulseaudio Output", guid_pulseaudio_branch, advconfig_branch::guid_branch_playback, 0);
//static advconfig_integer_factory cfg_pulseaudio_destination_port("Destination port", guid_pulseaudio_cfg_destination_port, guid_pulseaudio_branch, 0, 4010, 0, 65535, 0);

// todo: check every operation is unreferenced
// implement cookies
// ip configuraion GUI
// try compiling pulseaudio 1.1 and modify with syscall assembly
// investigate dynamically loading the linux .so

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
	static bool g_pa_is_loaded = false;

	class output_pulse : public output_v4
	{
	private:

		void load_pulse_dll()
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
				throw exception_output_device_not_found();
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

			g_pa_operation_unref = (pa_operation_unref)GetProcAddress(libpulse, "pa_operation_unref");

			g_pa_bytes_to_usec = (pa_bytes_to_usec)GetProcAddress(libpulse, "pa_bytes_to_usec");
			g_pa_usec_to_bytes = (pa_usec_to_bytes)GetProcAddress(libpulse, "pa_usec_to_bytes");

			g_pa_is_loaded = true;
		}

		pa_context* context = NULL;
		pa_threaded_mainloop* mainloop = NULL;
		pa_stream* stream = NULL;

		pfc::array_t<audio_sample, pfc::alloc_fast_aggressive> m_incoming;
		t_size m_incoming_ptr;
		t_samplespec m_incoming_spec, m_active_spec;

		double buffer_length;

		bool progressing;
	public:
		output_pulse(const GUID& p_device, double p_buffer_length, bool p_dither, t_uint32 p_bitdepth)
			: buffer_length(p_buffer_length), m_incoming_ptr(0), progressing(false)
		{
			if (!g_pa_is_loaded)
			{
				load_pulse_dll();
			}

			mainloop = g_pa_threaded_mainloop_new();
			if (g_pa_threaded_mainloop_start(mainloop) < 0)
			{
				g_pa_threaded_mainloop_free(mainloop);
				console::error("PulseAudio: failed to start playback thread");
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

			g_pa_context_set_state_callback(context, context_state_cb, mainloop);

			if (g_pa_context_connect(context, "127.0.0.1", (pa_context_flags_t)0, NULL) < 0
				|| context_wait(context, mainloop))
			{
				g_pa_context_unref(context);
				g_pa_threaded_mainloop_unlock(mainloop);
				g_pa_threaded_mainloop_stop(mainloop);
				g_pa_threaded_mainloop_free(mainloop);

				console::error("PulseAudio: failed to connect");
				throw exception_output_invalidated();
			}

			g_pa_threaded_mainloop_unlock(mainloop);
		}
		~output_pulse()
		{
			close_stream();

			g_pa_threaded_mainloop_lock(mainloop);
			g_pa_context_disconnect(context);
			g_pa_context_set_state_callback(context, NULL, NULL);
			g_pa_context_unref(context);
			g_pa_threaded_mainloop_unlock(mainloop);
			g_pa_threaded_mainloop_stop(mainloop);
			g_pa_threaded_mainloop_free(mainloop);
		}

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
			pa_threaded_mainloop* ml = (pa_threaded_mainloop*)userdata;

			switch (g_pa_context_get_state(ctx))
			{
			case PA_CONTEXT_READY:
			case PA_CONTEXT_FAILED:
			case PA_CONTEXT_TERMINATED:
				g_pa_threaded_mainloop_signal(ml, 0);
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
		}

		static void g_enum_devices(output_device_enum_callback& p_callback) {
			const GUID device = { 0x2205583, 0xa73a, 0x1ca7, { 0xaa, 0xbb, 0x5f, 0x91, 0x8b, 0x1, 0x15, 0xd0 } };
			p_callback.on_device(device, "Pulseaudio (localhost)", 22);
		}
		static GUID g_get_guid() {
			//This is our GUID. Generate your own one when reusing this code.
			static const GUID guid = { 0x410910c, 0x13bf, 0x3591, { 0x68, 0x19, 0x70, 0x1a, 0x9b, 0xa3, 0x48, 0x82 } };
			return guid;
		}
		static bool g_advanced_settings_query() { return false; }
		static bool g_needs_bitdepth_config() { return false; }
		static bool g_needs_dither_config() { return false; }
		static bool g_needs_device_list_prefixes() { return false; }
		static bool g_supports_multiple_streams() { return false; }
		static bool g_is_high_latency() { return false; }
		static uint32_t g_extra_flags() {
			return 0;
		}
		static void g_advanced_settings_popup(HWND p_parent, POINT p_menupoint) {}
		static const char* g_get_name() { return "PulseAudio Output"; }

		void write(const audio_chunk& p_data)
		{
			g_pa_threaded_mainloop_lock(mainloop);
			if (g_pa_stream_write(stream, p_data.get_data(), p_data.get_used_size() * 4, NULL, 0, PA_SEEK_RELATIVE) < 0)
			{
				console::error("Pulseaudio: error writing to stream");
			}
			g_pa_threaded_mainloop_unlock(mainloop);
		}
		t_size can_write_samples()
		{
			if (stream == NULL)
			{
				return 0;
			}

			const pa_sample_spec* ss = g_pa_stream_get_sample_spec(stream);
			size_t bytes = g_pa_stream_writable_size(stream);
			return bytes / 4 / ss->channels;
		}
		bool is_empty()
		{
			if (stream == NULL)
				return true;

			const pa_timing_info* info = g_pa_stream_get_timing_info(stream);
			return !info->write_index_corrupt && !info->read_index_corrupt
				&& info->read_index == info->write_index;
		}
		void on_flush()
		{
			if (stream == NULL)
				return;

			g_pa_threaded_mainloop_lock(mainloop);
			pa_operation* op = g_pa_stream_flush(stream, NULL, NULL);
			if (op != NULL)
			{
				g_pa_operation_unref(op);
			}
			g_pa_threaded_mainloop_unlock(mainloop);
		}
		void on_flush_changing_track()
		{
			if (stream == NULL)
				return;

			g_pa_threaded_mainloop_lock(mainloop);
			pa_operation* op = g_pa_stream_flush(stream, NULL, NULL);
			if (op != NULL)
			{
				g_pa_operation_unref(op);
			}
			g_pa_threaded_mainloop_unlock(mainloop);
		}
		void close_stream()
		{
			if (stream != NULL)
			{
				g_pa_threaded_mainloop_lock(mainloop);
				g_pa_stream_set_state_callback(stream, NULL, NULL);
				g_pa_stream_set_started_callback(stream, NULL, NULL);
				g_pa_stream_disconnect(stream);
				g_pa_stream_unref(stream);
				stream = NULL;
				progressing = false;
				g_pa_threaded_mainloop_unlock(mainloop);
			}
		}
		void open(t_samplespec const& p_spec)
		{
			pa_sample_spec ss;
			ss.channels = p_spec.m_channels;
			ss.rate = p_spec.m_sample_rate;
			ss.format = PA_SAMPLE_FLOAT32LE;

			pa_stream_flags_t flags =
				(pa_stream_flags_t)(PA_STREAM_INTERPOLATE_TIMING | PA_STREAM_AUTO_TIMING_UPDATE
					| PA_STREAM_ADJUST_LATENCY | PA_STREAM_NOT_MONOTONIC);

			struct pa_buffer_attr attr;
			attr.maxlength = ceil(p_spec.time_to_samples(buffer_length) * p_spec.m_channels * 4);
			attr.fragsize = 0;
			attr.minreq = (uint32_t)-1;
			attr.prebuf = (uint32_t)-1;
			attr.tlength = (uint32_t)-1;

			close_stream();

			g_pa_threaded_mainloop_lock(mainloop);
			stream = g_pa_stream_new(context, "Audio", &ss, NULL);
			progressing = false;
			if (stream == NULL) {
				g_pa_threaded_mainloop_unlock(mainloop);
				console::error("PulseAudio: failed to create stream");
				throw exception_output_invalidated();
			}

			g_pa_stream_set_state_callback(stream, stream_state_cb, mainloop);
			if (g_pa_stream_connect_playback(stream, NULL, &attr,
				flags, NULL, NULL) < 0 || stream_wait(stream, mainloop))
			{
				g_pa_threaded_mainloop_unlock(mainloop);
				console::error("PulseAudio: failed to connect stream");
				throw exception_output_invalidated();
			}

			g_pa_stream_set_started_callback(stream, stream_started_cb, this);
			g_pa_stream_set_underflow_callback(stream, stream_underflow_cb, this);

			g_pa_threaded_mainloop_unlock(mainloop);
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
		void force_play() override
		{
			g_pa_threaded_mainloop_lock(mainloop);
			pa_operation* op = g_pa_stream_drain(stream, NULL, NULL);
			if (op != NULL)
			{
				g_pa_operation_unref(op);
			}
			g_pa_threaded_mainloop_unlock(mainloop);
		}

		void volume_set(double p_val) override
		{
		}

		void flush() {
			m_incoming_ptr = 0;
			m_incoming.set_size(0);
			on_flush();
		}
		void flush_changing_track() {
			m_incoming_ptr = 0;
			m_incoming.set_size(0);
			on_flush_changing_track();
		}

		void update(bool& p_ready) {
			p_ready = update_v2() > 0;
		}
		size_t update_v2() {
			if (m_incoming_spec != m_active_spec && m_incoming_ptr < m_incoming.get_size()) {
				if (is_empty()) {
					open(m_incoming_spec);
					m_active_spec = m_incoming_spec;
				}
				else {
					force_play();
				}
			}
			size_t retCanWriteSamples = 0;
			if (m_incoming_spec == m_active_spec && m_incoming_ptr < m_incoming.get_size()) {
				t_size cw = can_write_samples() * m_incoming_spec.m_channels;
				t_size delta = pfc::min_t(m_incoming.get_size() - m_incoming_ptr, cw);
				if (delta > 0) {
					write(audio_chunk_temp_impl(m_incoming.get_ptr() + m_incoming_ptr, delta / m_incoming_spec.m_channels, m_incoming_spec.m_sample_rate, m_incoming_spec.m_channels, m_incoming_spec.m_channel_config));
					m_incoming_ptr += delta;
				}
				retCanWriteSamples = (cw - delta) / m_incoming_spec.m_channels;
			}
			else if (m_incoming_ptr == m_incoming.get_size()) {
				retCanWriteSamples = SIZE_MAX;
			}
			return retCanWriteSamples;
		}

		double get_latency() {
			double ret = 0;
			if (m_incoming_spec.is_valid()) {
				ret += audio_math::samples_to_time((m_incoming.get_size() - m_incoming_ptr) / m_incoming_spec.m_channels, m_incoming_spec.m_sample_rate);
			}
			if (m_active_spec.is_valid()) {
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
			t_size length = p_chunk.get_used_size();
			m_incoming.set_data_fromptr(p_chunk.get_data(), length);
			m_incoming_ptr = 0;
		}
		bool is_progressing()
		{
			return progressing;
		}
	};

	static output_factory_t<output_pulse> g_output_sample_factory;
}