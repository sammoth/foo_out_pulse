#pragma once

#include <stdint.h>

typedef int pa_simple;
typedef uint64_t pa_usec_t;

typedef enum pa_stream_direction {
    PA_STREAM_NODIRECTION,
    PA_STREAM_PLAYBACK,
    PA_STREAM_RECORD,
    PA_STREAM_UPLOAD
} pa_stream_direction_t;

typedef enum pa_sample_format {
    PA_SAMPLE_U8,
    PA_SAMPLE_ALAW,
    PA_SAMPLE_ULAW,
    PA_SAMPLE_S16LE,
    PA_SAMPLE_S16BE,
    PA_SAMPLE_FLOAT32LE,
    PA_SAMPLE_FLOAT32BE,
    PA_SAMPLE_S32LE,
    PA_SAMPLE_S32BE,
    PA_SAMPLE_S24LE,
    PA_SAMPLE_S24BE,
    PA_SAMPLE_S24_32LE,
    PA_SAMPLE_S24_32BE,
    PA_SAMPLE_MAX,
    PA_SAMPLE_INVALID = -1
} pa_sample_format_t;

typedef struct pa_sample_spec {
    pa_sample_format_t format;
    uint32_t rate;                 // sample rate eg. 44100
    uint8_t channels;
} pa_sample_spec;


// todo if problem: check cond fulldocs in pulse source
typedef enum pa_channel_position {
    PA_CHANNEL_POSITION_INVALID = -1,
    PA_CHANNEL_POSITION_MONO = 0,

    PA_CHANNEL_POSITION_FRONT_LEFT,               /**< Apple, Dolby call this 'Left' */
    PA_CHANNEL_POSITION_FRONT_RIGHT,              /**< Apple, Dolby call this 'Right' */
    PA_CHANNEL_POSITION_FRONT_CENTER,             /**< Apple, Dolby call this 'Center' */

    PA_CHANNEL_POSITION_LEFT = PA_CHANNEL_POSITION_FRONT_LEFT,
    PA_CHANNEL_POSITION_RIGHT = PA_CHANNEL_POSITION_FRONT_RIGHT,
    PA_CHANNEL_POSITION_CENTER = PA_CHANNEL_POSITION_FRONT_CENTER,

    PA_CHANNEL_POSITION_REAR_CENTER,              /**< Microsoft calls this 'Back Center', Apple calls this 'Center Surround', Dolby calls this 'Surround Rear Center' */
    PA_CHANNEL_POSITION_REAR_LEFT,                /**< Microsoft calls this 'Back Left', Apple calls this 'Left Surround' (!), Dolby calls this 'Surround Rear Left'  */
    PA_CHANNEL_POSITION_REAR_RIGHT,               /**< Microsoft calls this 'Back Right', Apple calls this 'Right Surround' (!), Dolby calls this 'Surround Rear Right'  */

    PA_CHANNEL_POSITION_LFE,                      /**< Microsoft calls this 'Low Frequency', Apple calls this 'LFEScreen' */
    PA_CHANNEL_POSITION_SUBWOOFER = PA_CHANNEL_POSITION_LFE,

    PA_CHANNEL_POSITION_FRONT_LEFT_OF_CENTER,     /**< Apple, Dolby call this 'Left Center' */
    PA_CHANNEL_POSITION_FRONT_RIGHT_OF_CENTER,    /**< Apple, Dolby call this 'Right Center */

    PA_CHANNEL_POSITION_SIDE_LEFT,                /**< Apple calls this 'Left Surround Direct', Dolby calls this 'Surround Left' (!) */
    PA_CHANNEL_POSITION_SIDE_RIGHT,               /**< Apple calls this 'Right Surround Direct', Dolby calls this 'Surround Right' (!) */

    PA_CHANNEL_POSITION_AUX0,
    PA_CHANNEL_POSITION_AUX1,
    PA_CHANNEL_POSITION_AUX2,
    PA_CHANNEL_POSITION_AUX3,
    PA_CHANNEL_POSITION_AUX4,
    PA_CHANNEL_POSITION_AUX5,
    PA_CHANNEL_POSITION_AUX6,
    PA_CHANNEL_POSITION_AUX7,
    PA_CHANNEL_POSITION_AUX8,
    PA_CHANNEL_POSITION_AUX9,
    PA_CHANNEL_POSITION_AUX10,
    PA_CHANNEL_POSITION_AUX11,
    PA_CHANNEL_POSITION_AUX12,
    PA_CHANNEL_POSITION_AUX13,
    PA_CHANNEL_POSITION_AUX14,
    PA_CHANNEL_POSITION_AUX15,
    PA_CHANNEL_POSITION_AUX16,
    PA_CHANNEL_POSITION_AUX17,
    PA_CHANNEL_POSITION_AUX18,
    PA_CHANNEL_POSITION_AUX19,
    PA_CHANNEL_POSITION_AUX20,
    PA_CHANNEL_POSITION_AUX21,
    PA_CHANNEL_POSITION_AUX22,
    PA_CHANNEL_POSITION_AUX23,
    PA_CHANNEL_POSITION_AUX24,
    PA_CHANNEL_POSITION_AUX25,
    PA_CHANNEL_POSITION_AUX26,
    PA_CHANNEL_POSITION_AUX27,
    PA_CHANNEL_POSITION_AUX28,
    PA_CHANNEL_POSITION_AUX29,
    PA_CHANNEL_POSITION_AUX30,
    PA_CHANNEL_POSITION_AUX31,

    PA_CHANNEL_POSITION_TOP_CENTER,               /**< Apple calls this 'Top Center Surround' */

    PA_CHANNEL_POSITION_TOP_FRONT_LEFT,           /**< Apple calls this 'Vertical Height Left' */
    PA_CHANNEL_POSITION_TOP_FRONT_RIGHT,          /**< Apple calls this 'Vertical Height Right' */
    PA_CHANNEL_POSITION_TOP_FRONT_CENTER,         /**< Apple calls this 'Vertical Height Center' */

    PA_CHANNEL_POSITION_TOP_REAR_LEFT,            /**< Microsoft and Apple call this 'Top Back Left' */
    PA_CHANNEL_POSITION_TOP_REAR_RIGHT,           /**< Microsoft and Apple call this 'Top Back Right' */
    PA_CHANNEL_POSITION_TOP_REAR_CENTER,          /**< Microsoft and Apple call this 'Top Back Center' */

    PA_CHANNEL_POSITION_MAX
} pa_channel_position_t;

typedef struct pa_buffer_attr {
    uint32_t maxlength;
    /**< Maximum length of the buffer. Setting this to (uint32_t) -1
     * will initialize this to the maximum value supported by server,
     * which is recommended. */

    uint32_t tlength;
    /**< Playback only: target length of the buffer. The server tries
     * to assure that at least tlength bytes are always available in
     * the per-stream server-side playback buffer. It is recommended
     * to set this to (uint32_t) -1, which will initialize this to a
     * value that is deemed sensible by the server. However, this
     * value will default to something like 2s, i.e. for applications
     * that have specific latency requirements this value should be
     * set to the maximum latency that the application can deal
     * with. When PA_STREAM_ADJUST_LATENCY is not set this value will
     * influence only the per-stream playback buffer size. When
     * PA_STREAM_ADJUST_LATENCY is set the overall latency of the sink
     * plus the playback buffer size is configured to this value. Set
     * PA_STREAM_ADJUST_LATENCY if you are interested in adjusting the
     * overall latency. Don't set it if you are interested in
     * configuring the server-side per-stream playback buffer
     * size. */

    uint32_t prebuf;
    /**< Playback only: pre-buffering. The server does not start with
     * playback before at least prebuf bytes are available in the
     * buffer. It is recommended to set this to (uint32_t) -1, which
     * will initialize this to the same value as tlength, whatever
     * that may be. Initialize to 0 to enable manual start/stop
     * control of the stream. This means that playback will not stop
     * on underrun and playback will not start automatically. Instead
     * pa_stream_cork() needs to be called explicitly. If you set
     * this value to 0 you should also set PA_STREAM_START_CORKED. */

    uint32_t minreq;
    /**< Playback only: minimum request. The server does not request
     * less than minreq bytes from the client, instead waits until the
     * buffer is free enough to request more bytes at once. It is
     * recommended to set this to (uint32_t) -1, which will initialize
     * this to a value that is deemed sensible by the server. This
     * should be set to a value that gives PulseAudio enough time to
     * move the data from the per-stream playback buffer into the
     * hardware playback buffer. */

    uint32_t fragsize;
    /**< Recording only: fragment size. The server sends data in
     * blocks of fragsize bytes size. Large values diminish
     * interactivity with other operations on the connection context
     * but decrease control overhead. It is recommended to set this to
     * (uint32_t) -1, which will initialize this to a value that is
     * deemed sensible by the server. However, this value will default
     * to something like 2s, i.e. for applications that have specific
     * latency requirements this value should be set to the maximum
     * latency that the application can deal with. If
     * PA_STREAM_ADJUST_LATENCY is set the overall source latency will
     * be adjusted according to this value. If it is not set the
     * source latency is left unmodified. */

} pa_buffer_attr;

typedef struct pa_channel_map {
    uint8_t channels;
    pa_channel_position_t map[32U]; // channel labels
} pa_channel_map;

typedef pa_simple*(__cdecl* pa_simple_new)(
    const char * server_name,
    const char * name,
    pa_stream_direction_t direction,
    const char * sink_name,
    const char * client_name,
    const pa_sample_spec * sample_type,
    const pa_channel_map * channel_map,
    const pa_buffer_attr * buffering_attr,
    int * return_error);
typedef void (__cdecl* pa_simple_free)(pa_simple* connection);
typedef int (__cdecl* pa_simple_write)(pa_simple * connection,
    const void* data,
    size_t bytes,
    int * return_error);
typedef int (__cdecl* pa_simple_drain)(pa_simple * connection,
    int * return_error);
typedef int (__cdecl* pa_simple_read)(pa_simple *s,
    void*data,
    size_t bytes,
    int *error);
typedef pa_usec_t (__cdecl* pa_simple_get_latency)(pa_simple *s,
    int *error);
typedef int (__cdecl* pa_simple_flush)(pa_simple *s,
    int *error);
typedef const char* (__cdecl* pa_strerror)(int error);
