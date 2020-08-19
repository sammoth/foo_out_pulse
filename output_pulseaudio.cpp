#include "stdafx.h"
#include "SDK/output.h"
#include "SDK/core_api.h"
#include <iostream>
#include <sstream>
#include <mutex>
#include <windows.h>
#include <pathcch.h>
#include "pulse.h"

namespace {

	//static const GUID guid_pulseaudio_branch = { 0x18564ced, 0x4abf, 0x4f0c, { 0xa4, 0x43, 0x98, 0xda, 0x88, 0xe2, 0xcd, 0x39 } };
	//static const GUID guid_pulseaudio_cfg_destination_port = { 0xe7598963, 0xed60, 0x4084, { 0xa8, 0x5d, 0xd1, 0xcd, 0xc5, 0x51, 0x22, 0xca } };

	//static advconfig_branch_factory g_pulseaudio_output_branch("Pulseaudio Output", guid_pulseaudio_branch, advconfig_branch::guid_branch_playback, 0);
	//static advconfig_integer_factory cfg_pulseaudio_destination_port("Destination port", guid_pulseaudio_cfg_destination_port, guid_pulseaudio_branch, 0, 4010, 0, 65535, 0);

	typedef HRESULT(CALLBACK* LPFNDLLFUNC1)(DWORD, UINT*);

	class output_pulse : public output_impl
	{
	private:
		HMODULE libpulse;
		HMODULE libpulse_simple;

		pa_simple_new pa_simple_new_ptr;
		pa_simple_free pa_simple_free_ptr;
		pa_simple_drain pa_simple_drain_ptr;
		pa_simple_flush pa_simple_flush_ptr;
		pa_simple_get_latency pa_simple_get_latency_ptr;
		pa_simple_read pa_simple_read_ptr;
		pa_simple_write pa_simple_write_ptr;
		pa_strerror pa_strerror_ptr;

		std::mutex mutex;

		pa_simple* connection = NULL;

		t_samplespec spec;
	public:
		output_pulse(const GUID& p_device, double p_buffer_length, bool p_dither, t_uint32 p_bitdepth)
		{
			pfc::string_formatter path = core_api::get_my_full_path();
			path.truncate(path.scan_filename());
			std::wstringstream wpath_simple;
			wpath_simple << path << "pulse\\libpulse-simple-0.dll";
			std::wstringstream wpath_libpulse;
			wpath_libpulse << path << "pulse\\libpulse-0.dll";
			libpulse_simple = LoadLibraryExW(wpath_simple.str().c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
			if (libpulse_simple == NULL)
			{
				std::stringstream error;
				error << "Could not load libpulse-simple-0.dll: code " << GetLastError();
				console::error(error.str().c_str());
				throw exception_output_device_not_found();
			}
			libpulse = LoadLibraryExW(wpath_libpulse.str().c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
			if (libpulse == NULL)
			{
				std::stringstream error;
				error << "Could not load libpulse-0.dll: code " << GetLastError();
				console::error(error.str().c_str());
				throw exception_output_device_not_found();
			}

			pa_simple_new_ptr = (pa_simple_new)GetProcAddress(libpulse_simple, "pa_simple_new");
			pa_simple_free_ptr = (pa_simple_free)GetProcAddress(libpulse_simple, "pa_simple_free");
			pa_simple_drain_ptr = (pa_simple_drain)GetProcAddress(libpulse_simple, "pa_simple_drain");
			pa_simple_flush_ptr = (pa_simple_flush)GetProcAddress(libpulse_simple, "pa_simple_flush");
			pa_simple_get_latency_ptr = (pa_simple_get_latency)GetProcAddress(libpulse_simple, "pa_simple_get_latency");
			pa_simple_read_ptr = (pa_simple_read)GetProcAddress(libpulse_simple, "pa_simple_read");
			pa_simple_write_ptr = (pa_simple_write)GetProcAddress(libpulse_simple, "pa_simple_write");
			pa_strerror_ptr = (pa_strerror)GetProcAddress(libpulse, "pa_strerror");

			if (pa_simple_new_ptr == NULL ||
				pa_simple_free_ptr == NULL ||
				pa_simple_drain_ptr == NULL ||
				pa_simple_flush_ptr == NULL ||
				pa_simple_get_latency_ptr == NULL ||
				pa_simple_read_ptr == NULL ||
				pa_simple_write_ptr == NULL)
			{
				console::error("Could not load symbols from PulseAudio dll");
				throw exception_output_device_not_found();
			}

			//int error = 0;
			//pa_sample_spec ss;
			//ss.channels = 2;
			//ss.rate = 44100;
			//ss.format = PA_SAMPLE_FLOAT32LE;
			//(pa_simple_new_addr)("192.168.1.68", "my client", PA_STREAM_PLAYBACK,
			//	NULL, "my stream name", &ss, NULL, NULL, &error);
			//const char* error_str = (pa_strerror_addr)(error);
			//console::error(error_str);
		}
		~output_pulse()
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (connection != NULL)
			{
				(pa_simple_free_ptr)(connection);
			}

			//if (libpulse != NULL) FreeLibrary(libpulse);
			//if (libpulse_simple != NULL) FreeLibrary(libpulse_simple);
		}

		static void g_enum_devices(output_device_enum_callback& p_callback) {
			const GUID device = { 0x2205583, 0xa73a, 0x1ca7, { 0xaa, 0xbb, 0x5f, 0x91, 0x8b, 0x1, 0x15, 0xd0 } };
			p_callback.on_device(device, "Pulseaudio Native", 17);
		}
		static GUID g_get_guid() {
			//This is our GUID. Generate your own one when reusing this code.
			static const GUID guid = { 0x410910c, 0x13bf, 0x3591, { 0x68, 0x19, 0x70, 0x1a, 0x9b, 0xa3, 0x48, 0x82 } };
			return guid;
		}
		static bool g_advanced_settings_query() { return false; }
		static bool g_needs_bitdepth_config() { return true; }
		static bool g_needs_dither_config() { return true; }
		static bool g_needs_device_list_prefixes() { return false; }
		static bool g_supports_multiple_streams() { return false; }
		static bool g_is_high_latency() { return false; }
		static uint32_t g_extra_flags() {
			return 0;
		}
		static void g_advanced_settings_popup(HWND p_parent, POINT p_menupoint) {}
		static const char* g_get_name() { return "PulseAudio Output"; }

		// Inherited via output_impl
		void on_update() override
		{
		}
		void write(const audio_chunk& p_data) override
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (connection != NULL)
			{
				int error = 0;
				(pa_simple_write_ptr)(connection,
					p_data.get_data(),
					p_data.get_used_size() * sizeof(audio_sample),
					&error);
				if (error > 0)
				{
					const char* error_str = (pa_strerror_ptr)(error);
					console::error(error_str);
				}
			}
		}
		t_size can_write_samples() override
		{
			return 10000;
		}
		t_size get_latency_samples() override
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (connection == NULL)
				return 0;

			int error = 0;
			pa_usec_t latency = (pa_simple_get_latency_ptr)(connection, &error);

			if (error > 0)
			{
				const char* error_str = (pa_strerror_ptr)(error);
				console::error(error_str);
				return 0;
			}

			return audio_math::time_to_samples(0.000001 * latency, spec.m_sample_rate);
		}
		void on_flush() override
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (connection != NULL)
			{
				int error = 0;
				(pa_simple_flush_ptr)(connection, &error);
				if (error > 0)
				{
					const char* error_str = (pa_strerror_ptr)(error);
					console::error(error_str);
				}
			}
		}
		void on_flush_changing_track() override
		{
			on_flush();
		}
		void open(t_samplespec const& p_spec) override
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (connection != NULL)
			{
				(pa_simple_free_ptr)(connection);
			}

			int error = 0;
			pa_sample_spec ss = {};
			ss.rate = p_spec.m_sample_rate;
			ss.channels = p_spec.m_channels;
			ss.format = PA_SAMPLE_FLOAT32LE;
			connection = (pa_simple_new_ptr)("192.168.1.68", "my client", PA_STREAM_PLAYBACK,
				NULL, "my stream name", &ss, NULL, NULL, &error);
			if (error > 0)
			{
				connection = NULL;
				const char* error_str = (pa_strerror_ptr)(error);
				console::error(error_str);
			}

			spec = p_spec;
		}
		void pause(bool p_state) override
		{
		}
		void force_play() override
		{
			std::lock_guard<std::mutex> lock(mutex);
			if (connection != NULL)
			{
				int error = 0;
				(pa_simple_drain_ptr)(connection, &error);
				(pa_simple_flush_ptr)(connection, &error);
				if (error > 0)
				{
					const char* error_str = (pa_strerror_ptr)(error);
					console::error(error_str);
				}
			}
		}
		void volume_set(double p_val) override
		{
		}
	};

	static output_factory_t<output_pulse> g_output_sample_factory;
}