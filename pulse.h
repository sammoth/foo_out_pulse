#pragma once
#include <stdint.h>
#define PA_CHANNELS_MAX 32U
typedef bool pa_bool_t; // check
typedef uint64_t pa_usec_t;
typedef struct pa_mainloop pa_mainloop;
typedef struct pa_operation pa_operation;
typedef struct pa_proplist pa_proplist;
typedef struct pa_mainloop_api pa_mainloop_api;
typedef struct pa_threaded_mainloop pa_threaded_mainloop;
typedef struct pa_defer_event pa_defer_event;
typedef struct pa_io_event pa_io_event;
typedef struct pa_time_event pa_time_event;
typedef struct pa_context pa_context;
typedef struct pa_stream pa_stream;
typedef enum pa_io_event_flags {
    PA_IO_EVENT_NULL = 0,     
    PA_IO_EVENT_INPUT = 1,    
    PA_IO_EVENT_OUTPUT = 2,   
    PA_IO_EVENT_HANGUP = 4,   
    PA_IO_EVENT_ERROR = 8     
} pa_io_event_flags_t;
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
typedef enum pa_channel_position {
    PA_CHANNEL_POSITION_INVALID = -1,
    PA_CHANNEL_POSITION_MONO = 0,
    PA_CHANNEL_POSITION_FRONT_LEFT,               
    PA_CHANNEL_POSITION_FRONT_RIGHT,              
    PA_CHANNEL_POSITION_FRONT_CENTER,             
    PA_CHANNEL_POSITION_LEFT = PA_CHANNEL_POSITION_FRONT_LEFT,
    PA_CHANNEL_POSITION_RIGHT = PA_CHANNEL_POSITION_FRONT_RIGHT,
    PA_CHANNEL_POSITION_CENTER = PA_CHANNEL_POSITION_FRONT_CENTER,
    PA_CHANNEL_POSITION_REAR_CENTER,              
    PA_CHANNEL_POSITION_REAR_LEFT,                
    PA_CHANNEL_POSITION_REAR_RIGHT,               
    PA_CHANNEL_POSITION_LFE,                      
    PA_CHANNEL_POSITION_SUBWOOFER = PA_CHANNEL_POSITION_LFE,
    PA_CHANNEL_POSITION_FRONT_LEFT_OF_CENTER,     
    PA_CHANNEL_POSITION_FRONT_RIGHT_OF_CENTER,    
    PA_CHANNEL_POSITION_SIDE_LEFT,                
    PA_CHANNEL_POSITION_SIDE_RIGHT,               
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
    PA_CHANNEL_POSITION_TOP_CENTER,               
    PA_CHANNEL_POSITION_TOP_FRONT_LEFT,           
    PA_CHANNEL_POSITION_TOP_FRONT_RIGHT,          
    PA_CHANNEL_POSITION_TOP_FRONT_CENTER,         
    PA_CHANNEL_POSITION_TOP_REAR_LEFT,            
    PA_CHANNEL_POSITION_TOP_REAR_RIGHT,           
    PA_CHANNEL_POSITION_TOP_REAR_CENTER,          
    PA_CHANNEL_POSITION_MAX
} pa_channel_position_t;
typedef struct pa_buffer_attr {
    uint32_t maxlength;
    uint32_t tlength;
    uint32_t prebuf;
    uint32_t minreq;
    uint32_t fragsize;
} pa_buffer_attr;
typedef struct pa_channel_map {
    uint8_t channels;
    pa_channel_position_t map[32U]; // channel labels
} pa_channel_map;
typedef const char* (__cdecl *pa_strerror)(int error);
typedef pa_operation* (__cdecl *pa_operation_ref)(pa_operation *o);
typedef void (__cdecl *pa_operation_unref)(pa_operation *o);
typedef void (__cdecl *pa_operation_cancel)(pa_operation *o);
#define PA_PROP_MEDIA_NAME                     "media.name"
#define PA_PROP_MEDIA_TITLE                    "media.title"
#define PA_PROP_MEDIA_ARTIST                   "media.artist"
#define PA_PROP_MEDIA_COPYRIGHT                "media.copyright"
#define PA_PROP_MEDIA_SOFTWARE                 "media.software"
#define PA_PROP_MEDIA_LANGUAGE                 "media.language"
#define PA_PROP_MEDIA_FILENAME                 "media.filename"
#define PA_PROP_MEDIA_ICON                     "media.icon"
#define PA_PROP_MEDIA_ICON_NAME                "media.icon_name"
#define PA_PROP_MEDIA_ROLE                     "media.role"
#define PA_PROP_FILTER_WANT                    "filter.want"
#define PA_PROP_FILTER_APPLY                   "filter.apply"
#define PA_PROP_FILTER_SUPPRESS                "filter.suppress"
#define PA_PROP_EVENT_ID                       "event.id"
#define PA_PROP_EVENT_DESCRIPTION              "event.description"
#define PA_PROP_EVENT_MOUSE_X                  "event.mouse.x"
#define PA_PROP_EVENT_MOUSE_Y                  "event.mouse.y"
#define PA_PROP_EVENT_MOUSE_HPOS               "event.mouse.hpos"
#define PA_PROP_EVENT_MOUSE_VPOS               "event.mouse.vpos"
#define PA_PROP_EVENT_MOUSE_BUTTON             "event.mouse.button"
#define PA_PROP_WINDOW_NAME                    "window.name"
#define PA_PROP_WINDOW_ID                      "window.id"
#define PA_PROP_WINDOW_ICON                    "window.icon"
#define PA_PROP_WINDOW_ICON_NAME               "window.icon_name"
#define PA_PROP_WINDOW_X                       "window.x"
#define PA_PROP_WINDOW_Y                       "window.y"
#define PA_PROP_WINDOW_WIDTH                   "window.width"
#define PA_PROP_WINDOW_HEIGHT                  "window.height"
#define PA_PROP_WINDOW_HPOS                    "window.hpos"
#define PA_PROP_WINDOW_VPOS                    "window.vpos"
#define PA_PROP_WINDOW_DESKTOP                 "window.desktop"
#define PA_PROP_WINDOW_X11_DISPLAY             "window.x11.display"
#define PA_PROP_WINDOW_X11_SCREEN              "window.x11.screen"
#define PA_PROP_WINDOW_X11_MONITOR             "window.x11.monitor"
#define PA_PROP_WINDOW_X11_XID                 "window.x11.xid"
#define PA_PROP_APPLICATION_NAME               "application.name"
#define PA_PROP_APPLICATION_ID                 "application.id"
#define PA_PROP_APPLICATION_VERSION            "application.version"
#define PA_PROP_APPLICATION_ICON               "application.icon"
#define PA_PROP_APPLICATION_ICON_NAME          "application.icon_name"
#define PA_PROP_APPLICATION_LANGUAGE           "application.language"
#define PA_PROP_APPLICATION_PROCESS_ID         "application.process.id"
#define PA_PROP_APPLICATION_PROCESS_BINARY     "application.process.binary"
#define PA_PROP_APPLICATION_PROCESS_USER       "application.process.user"
#define PA_PROP_APPLICATION_PROCESS_HOST       "application.process.host"
#define PA_PROP_APPLICATION_PROCESS_MACHINE_ID "application.process.machine_id"
#define PA_PROP_APPLICATION_PROCESS_SESSION_ID "application.process.session_id"
#define PA_PROP_DEVICE_STRING                  "device.string"
#define PA_PROP_DEVICE_API                     "device.api"
#define PA_PROP_DEVICE_DESCRIPTION             "device.description"
#define PA_PROP_DEVICE_BUS_PATH                "device.bus_path"
#define PA_PROP_DEVICE_SERIAL                  "device.serial"
#define PA_PROP_DEVICE_VENDOR_ID               "device.vendor.id"
#define PA_PROP_DEVICE_VENDOR_NAME             "device.vendor.name"
#define PA_PROP_DEVICE_PRODUCT_ID              "device.product.id"
#define PA_PROP_DEVICE_PRODUCT_NAME            "device.product.name"
#define PA_PROP_DEVICE_CLASS                   "device.class"
#define PA_PROP_DEVICE_FORM_FACTOR             "device.form_factor"
#define PA_PROP_DEVICE_BUS                     "device.bus"
#define PA_PROP_DEVICE_ICON                    "device.icon"
#define PA_PROP_DEVICE_ICON_NAME               "device.icon_name"
#define PA_PROP_DEVICE_ACCESS_MODE             "device.access_mode"
#define PA_PROP_DEVICE_MASTER_DEVICE           "device.master_device"
#define PA_PROP_DEVICE_BUFFERING_BUFFER_SIZE   "device.buffering.buffer_size"
#define PA_PROP_DEVICE_BUFFERING_FRAGMENT_SIZE "device.buffering.fragment_size"
#define PA_PROP_DEVICE_PROFILE_NAME            "device.profile.name"
#define PA_PROP_DEVICE_INTENDED_ROLES          "device.intended_roles"
#define PA_PROP_DEVICE_PROFILE_DESCRIPTION     "device.profile.description"
#define PA_PROP_MODULE_AUTHOR                  "module.author"
#define PA_PROP_MODULE_DESCRIPTION             "module.description"
#define PA_PROP_MODULE_USAGE                   "module.usage"
#define PA_PROP_MODULE_VERSION                 "module.version"
#define PA_PROP_FORMAT_SAMPLE_FORMAT           "format.sample_format"
#define PA_PROP_FORMAT_RATE                    "format.rate"
#define PA_PROP_FORMAT_CHANNELS                "format.channels"
#define PA_PROP_FORMAT_CHANNEL_MAP             "format.channel_map"
typedef pa_proplist* (__cdecl *pa_proplist_new)(void);
typedef void (__cdecl *pa_proplist_free)(pa_proplist* p);
typedef void (__cdecl *pa_proplist_sets)(pa_proplist *p, const char *key, const char *value);
typedef void (__cdecl *pa_proplist_setp)(pa_proplist *p, const char *pair);
typedef void (__cdecl *pa_proplist_set)(pa_proplist *p, const char *key, const void *data, size_t nbytes);
typedef enum pa_context_state {
    PA_CONTEXT_UNCONNECTED,    
    PA_CONTEXT_CONNECTING,     
    PA_CONTEXT_AUTHORIZING,    
    PA_CONTEXT_SETTING_NAME,   
    PA_CONTEXT_READY,          
    PA_CONTEXT_FAILED,         
    PA_CONTEXT_TERMINATED      
} pa_context_state_t;
#define PA_CONTEXT_UNCONNECTED PA_CONTEXT_UNCONNECTED
#define PA_CONTEXT_CONNECTING PA_CONTEXT_CONNECTING
#define PA_CONTEXT_AUTHORIZING PA_CONTEXT_AUTHORIZING
#define PA_CONTEXT_SETTING_NAME PA_CONTEXT_SETTING_NAME
#define PA_CONTEXT_READY PA_CONTEXT_READY
#define PA_CONTEXT_FAILED PA_CONTEXT_FAILED
#define PA_CONTEXT_TERMINATED PA_CONTEXT_TERMINATED
typedef enum pa_stream_state {
    PA_STREAM_UNCONNECTED,  
    PA_STREAM_CREATING,     
    PA_STREAM_READY,        
    PA_STREAM_FAILED,       
    PA_STREAM_TERMINATED    
} pa_stream_state_t;
typedef enum pa_operation_state {
    PA_OPERATION_RUNNING,      
    PA_OPERATION_DONE,         
    PA_OPERATION_CANCELLED     
} pa_operation_state_t;
typedef enum pa_context_flags {
    PA_CONTEXT_NOFLAGS = 0x0000U,
    PA_CONTEXT_NOAUTOSPAWN = 0x0001U,
    PA_CONTEXT_NOFAIL = 0x0002U
} pa_context_flags_t;
typedef enum pa_stream_flags {
    PA_STREAM_NOFLAGS = 0x0000U,
    PA_STREAM_START_CORKED = 0x0001U,
    PA_STREAM_INTERPOLATE_TIMING = 0x0002U,
    PA_STREAM_NOT_MONOTONIC = 0x0004U,
    PA_STREAM_AUTO_TIMING_UPDATE = 0x0008U,
    PA_STREAM_NO_REMAP_CHANNELS = 0x0010U,
    PA_STREAM_NO_REMIX_CHANNELS = 0x0020U,
    PA_STREAM_FIX_FORMAT = 0x0040U,
    PA_STREAM_FIX_RATE = 0x0080U,
    PA_STREAM_FIX_CHANNELS = 0x0100,
    PA_STREAM_DONT_MOVE = 0x0200U,
    PA_STREAM_VARIABLE_RATE = 0x0400U,
    PA_STREAM_PEAK_DETECT = 0x0800U,
    PA_STREAM_START_MUTED = 0x1000U,
    PA_STREAM_ADJUST_LATENCY = 0x2000U,
    PA_STREAM_EARLY_REQUESTS = 0x4000U,
    PA_STREAM_DONT_INHIBIT_AUTO_SUSPEND = 0x8000U,
    PA_STREAM_START_UNMUTED = 0x10000U,
    PA_STREAM_FAIL_ON_SUSPEND = 0x20000U,
    PA_STREAM_RELATIVE_VOLUME = 0x40000U,
    PA_STREAM_PASSTHROUGH = 0x80000U
} pa_stream_flags_t;
#define PA_STREAM_NOT_MONOTONOUS PA_STREAM_NOT_MONOTONIC
#define PA_STREAM_START_CORKED PA_STREAM_START_CORKED
#define PA_STREAM_INTERPOLATE_TIMING PA_STREAM_INTERPOLATE_TIMING
#define PA_STREAM_NOT_MONOTONIC PA_STREAM_NOT_MONOTONIC
#define PA_STREAM_AUTO_TIMING_UPDATE PA_STREAM_AUTO_TIMING_UPDATE
#define PA_STREAM_NO_REMAP_CHANNELS PA_STREAM_NO_REMAP_CHANNELS
#define PA_STREAM_NO_REMIX_CHANNELS PA_STREAM_NO_REMIX_CHANNELS
#define PA_STREAM_FIX_FORMAT PA_STREAM_FIX_FORMAT
#define PA_STREAM_FIX_RATE PA_STREAM_FIX_RATE
#define PA_STREAM_FIX_CHANNELS PA_STREAM_FIX_CHANNELS
#define PA_STREAM_DONT_MOVE PA_STREAM_DONT_MOVE
#define PA_STREAM_VARIABLE_RATE PA_STREAM_VARIABLE_RATE
#define PA_STREAM_PEAK_DETECT PA_STREAM_PEAK_DETECT
#define PA_STREAM_START_MUTED PA_STREAM_START_MUTED
#define PA_STREAM_ADJUST_LATENCY PA_STREAM_ADJUST_LATENCY
#define PA_STREAM_EARLY_REQUESTS PA_STREAM_EARLY_REQUESTS
#define PA_STREAM_DONT_INHIBIT_AUTO_SUSPEND PA_STREAM_DONT_INHIBIT_AUTO_SUSPEND
#define PA_STREAM_START_UNMUTED PA_STREAM_START_UNMUTED
#define PA_STREAM_FAIL_ON_SUSPEND PA_STREAM_FAIL_ON_SUSPEND
#define PA_STREAM_RELATIVE_VOLUME PA_STREAM_RELATIVE_VOLUME
#define PA_STREAM_PASSTHROUGH PA_STREAM_PASSTHROUGH
#define PA_LLIST_HEAD(t,name)                                           \
    t *name
#define PA_LLIST_FIELDS(t)                                              \
    t *next, *prev
typedef struct pa_timing_info {
    struct timeval timestamp;
    int synchronized_clocks;
    pa_usec_t sink_usec;
    pa_usec_t source_usec;
    pa_usec_t transport_usec;
    int playing;
    int write_index_corrupt;
    int64_t write_index;
    int read_index_corrupt;
    int64_t read_index;
    pa_usec_t configured_sink_usec;
    pa_usec_t configured_source_usec;
    int64_t since_underrun;
} pa_timing_info;
typedef struct pa_spawn_api {
    void (*prefork)(void);
    void (*postfork)(void);
    void (*atfork)(void);
} pa_spawn_api;
typedef enum pa_seek_mode {
    PA_SEEK_RELATIVE = 0,
    PA_SEEK_ABSOLUTE = 1,
    PA_SEEK_RELATIVE_ON_READ = 2,
    PA_SEEK_RELATIVE_END = 3
} pa_seek_mode_t;
typedef void (*pa_free_cb_t)(void *p);
typedef pa_threaded_mainloop* (__cdecl *pa_threaded_mainloop_new)(void);
typedef void (__cdecl *pa_threaded_mainloop_free)(pa_threaded_mainloop* m);
typedef int (__cdecl * pa_threaded_mainloop_start)(pa_threaded_mainloop *m);
typedef void (__cdecl *pa_threaded_mainloop_stop)(pa_threaded_mainloop *m);
typedef void (__cdecl *pa_threaded_mainloop_lock)(pa_threaded_mainloop *m);
typedef void (__cdecl *pa_threaded_mainloop_unlock)(pa_threaded_mainloop *m);
typedef void (__cdecl *pa_threaded_mainloop_wait)(pa_threaded_mainloop *m);
typedef void (__cdecl *pa_threaded_mainloop_signal)(pa_threaded_mainloop *m, int wait_for_accept);
typedef void (__cdecl *pa_threaded_mainloop_accept)(pa_threaded_mainloop *m);
typedef int (__cdecl *pa_threaded_mainloop_get_retval)(pa_threaded_mainloop *m);
typedef pa_mainloop_api* (__cdecl *pa_threaded_mainloop_get_api)(pa_threaded_mainloop*m);
typedef void (*pa_io_event_cb_t)(pa_mainloop_api*ea, pa_io_event* e, int fd, pa_io_event_flags_t events, void *userdata);
typedef void (*pa_io_event_destroy_cb_t)(pa_mainloop_api*a, pa_io_event *e, void *userdata);
typedef void (*pa_time_event_cb_t)(pa_mainloop_api*a, pa_time_event* e, const struct timeval *tv, void *userdata);
typedef void (*pa_time_event_destroy_cb_t)(pa_mainloop_api*a, pa_time_event *e, void *userdata);
typedef void (*pa_defer_event_cb_t)(pa_mainloop_api*a, pa_defer_event* e, void *userdata);
typedef void (*pa_defer_event_destroy_cb_t)(pa_mainloop_api*a, pa_defer_event *e, void *userdata);
struct pa_io_event {
    pa_mainloop *mainloop;
    pa_bool_t dead:1;
    int fd;
    pa_io_event_flags_t events;
    struct pollfd *pollfd;
    pa_io_event_cb_t callback;
    void *userdata;
    pa_io_event_destroy_cb_t destroy_callback;
    PA_LLIST_FIELDS(pa_io_event);
};
struct pa_time_event {
    pa_mainloop *mainloop;
    pa_bool_t dead:1;
    pa_bool_t enabled:1;
    pa_bool_t use_rtclock:1;
    pa_usec_t time;
    pa_time_event_cb_t callback;
    void *userdata;
    pa_time_event_destroy_cb_t destroy_callback;
    PA_LLIST_FIELDS(pa_time_event);
};
struct pa_defer_event {
    pa_mainloop *mainloop;
    pa_bool_t dead:1;
    pa_bool_t enabled:1;
    pa_defer_event_cb_t callback;
    void *userdata;
    pa_defer_event_destroy_cb_t destroy_callback;
    PA_LLIST_FIELDS(pa_defer_event);
};
struct pa_mainloop_api {
    void *userdata;
    pa_io_event* (*io_new)(pa_mainloop_api*a, int fd, pa_io_event_flags_t events, pa_io_event_cb_t cb, void *userdata);
    void (*io_enable)(pa_io_event* e, pa_io_event_flags_t events);
    void (*io_free)(pa_io_event* e);
    void (*io_set_destroy)(pa_io_event *e, pa_io_event_destroy_cb_t cb);
    pa_time_event* (*time_new)(pa_mainloop_api*a, const struct timeval *tv, pa_time_event_cb_t cb, void *userdata);
    void (*time_restart)(pa_time_event* e, const struct timeval *tv);
    void (*time_free)(pa_time_event* e);
    void (*time_set_destroy)(pa_time_event *e, pa_time_event_destroy_cb_t cb);
    pa_defer_event* (*defer_new)(pa_mainloop_api*a, pa_defer_event_cb_t cb, void *userdata);
    void (*defer_enable)(pa_defer_event* e, int b);
    void (*defer_free)(pa_defer_event* e);
    void (*defer_set_destroy)(pa_defer_event *e, pa_defer_event_destroy_cb_t cb);
    void (*quit)(pa_mainloop_api*a, int retval);
};
typedef int (*pa_poll_func)(struct pollfd *ufds, unsigned long nfds, int timeout, void*userdata);
struct pa_mainloop {
    PA_LLIST_HEAD(pa_io_event, io_events);
    PA_LLIST_HEAD(pa_time_event, time_events);
    PA_LLIST_HEAD(pa_defer_event, defer_events);
    unsigned n_enabled_defer_events, n_enabled_time_events, n_io_events;
    unsigned io_events_please_scan, time_events_please_scan, defer_events_please_scan;
    pa_bool_t rebuild_pollfds:1;
    struct pollfd *pollfds;
    unsigned max_pollfds, n_pollfds;
    pa_usec_t prepared_timeout;
    pa_time_event *cached_next_time_event;
    pa_mainloop_api api;
    int retval;
    pa_bool_t quit:1;
    pa_bool_t wakeup_requested:1;
    int wakeup_pipe[2];
    int wakeup_pipe_type;
    enum {
        STATE_PASSIVE,
        STATE_PREPARED,
        STATE_POLLING,
        STATE_POLLED,
        STATE_QUIT
    } state;
    pa_poll_func poll_func;
    void *poll_func_userdata;
    int poll_func_ret;
};
typedef void (__cdecl *pa_context_notify_cb_t)(pa_context *c, void *userdata);
typedef void (__cdecl *pa_context_success_cb_t) (pa_context *c, int success, void *userdata);
typedef void (__cdecl *pa_context_event_cb_t)(pa_context *c, const char *name, pa_proplist *p, void *userdata);
typedef pa_context* (__cdecl *pa_context_new_with_proplist)(pa_mainloop_api *mainloop, const char *name, pa_proplist *proplist);
typedef void (__cdecl *pa_context_unref)(pa_context *c);
typedef pa_context* (__cdecl *pa_context_ref)(pa_context *c);
typedef void (__cdecl *pa_context_set_state_callback)(pa_context *c, pa_context_notify_cb_t cb, void *userdata);
typedef void (__cdecl *pa_context_set_event_callback)(pa_context *p, pa_context_event_cb_t cb, void *userdata);
typedef int (__cdecl *pa_context_errno)(pa_context *c);
typedef int (__cdecl *pa_context_is_pending)(pa_context *c);
typedef pa_context_state_t (__cdecl *pa_context_get_state)(pa_context *c);
typedef int (__cdecl *pa_context_connect)(pa_context *c, const char *server, pa_context_flags_t flags, const pa_spawn_api *api);
typedef void (__cdecl *pa_context_disconnect)(pa_context *c);
typedef pa_operation* (__cdecl *pa_context_drain)(pa_context *c, pa_context_notify_cb_t cb, void *userdata);
typedef void (*pa_stream_success_cb_t) (pa_stream*s, int success, void *userdata);
typedef void (*pa_stream_request_cb_t)(pa_stream *p, size_t nbytes, void *userdata);
typedef void (*pa_stream_notify_cb_t)(pa_stream *p, void *userdata);
typedef pa_stream* (__cdecl *pa_stream_new)(
        pa_context *c                     ,
        const char *name                  ,
        const pa_sample_spec *ss          ,
        const pa_channel_map *map         );
typedef void (__cdecl *pa_stream_unref)(pa_stream *s);
typedef pa_stream_state_t (__cdecl *pa_stream_get_state)(pa_stream *p);
typedef uint32_t pa_volume_t;
typedef struct pa_cvolume {
    uint8_t channels;
    pa_volume_t values[PA_CHANNELS_MAX];
} pa_cvolume;
typedef int (__cdecl *pa_stream_connect_playback)(
        pa_stream *s                  ,
        const char *dev                ,
        const pa_buffer_attr *attr    ,
        pa_stream_flags_t flags       ,
        const pa_cvolume *volume      ,
        pa_stream *sync_stream        );
typedef int (__cdecl *pa_stream_disconnect)(pa_stream *s);
typedef int (__cdecl *pa_stream_cancel_write)(
        pa_stream *p);
typedef int (__cdecl *pa_stream_write)(
        pa_stream *p             ,
        const void *data         ,
        size_t nbytes            ,
        pa_free_cb_t free_cb     ,
        int64_t offset,          
        pa_seek_mode_t seek      );
typedef int (__cdecl *pa_stream_drop)(pa_stream *p);
typedef size_t (__cdecl *pa_stream_writable_size)(pa_stream *p);
typedef const pa_buffer_attr* (__cdecl *pa_stream_get_buffer_attr)(pa_stream *s);
typedef pa_operation* (__cdecl *pa_stream_drain)(pa_stream *s, pa_stream_success_cb_t cb, void *userdata);
typedef void (__cdecl *pa_stream_set_state_callback)(pa_stream *s, pa_stream_notify_cb_t cb, void *userdata);
typedef void (__cdecl *pa_stream_set_write_callback)(pa_stream *p, pa_stream_request_cb_t cb, void *userdata);
typedef void (__cdecl *pa_stream_set_underflow_callback)(pa_stream *p, pa_stream_notify_cb_t cb, void *userdata);
typedef void (__cdecl *pa_stream_set_started_callback)(pa_stream *p, pa_stream_notify_cb_t cb, void *userdata);
typedef pa_operation* (__cdecl *pa_stream_cork)(pa_stream *s, int b, pa_stream_success_cb_t cb, void *userdata);
typedef int (__cdecl *pa_stream_is_corked)(pa_stream *s);
typedef pa_operation* (__cdecl *pa_stream_flush)(pa_stream *s, pa_stream_success_cb_t cb, void *userdata);
typedef int (__cdecl *pa_stream_get_latency)(pa_stream *s, pa_usec_t *r_usec, int *negative);
typedef pa_operation* (__cdecl *pa_stream_update_timing_info)(pa_stream *p, pa_stream_success_cb_t cb, void *userdata);
typedef const pa_timing_info* (__cdecl *pa_stream_get_timing_info)(pa_stream *s);
typedef const pa_sample_spec* (__cdecl *pa_stream_get_sample_spec)(pa_stream *s);
typedef pa_operation* (__cdecl* pa_stream_trigger)(pa_stream* p, pa_stream_success_cb_t cb, void* userdata);
typedef pa_operation* (__cdecl *pa_stream_update_sample_rate)(pa_stream *s, uint32_t rate, pa_stream_success_cb_t cb, void *userdata);
typedef pa_usec_t (__cdecl *pa_bytes_to_usec)(uint64_t length, const pa_sample_spec *spec);
typedef size_t (__cdecl *pa_usec_to_bytes)(pa_usec_t t, const pa_sample_spec *spec);
#define PA_CHANNEL_POSITION_INVALID PA_CHANNEL_POSITION_INVALID
#define PA_CHANNEL_POSITION_MONO PA_CHANNEL_POSITION_MONO
#define PA_CHANNEL_POSITION_LEFT PA_CHANNEL_POSITION_LEFT
#define PA_CHANNEL_POSITION_RIGHT PA_CHANNEL_POSITION_RIGHT
#define PA_CHANNEL_POSITION_CENTER PA_CHANNEL_POSITION_CENTER
#define PA_CHANNEL_POSITION_FRONT_LEFT PA_CHANNEL_POSITION_FRONT_LEFT
#define PA_CHANNEL_POSITION_FRONT_RIGHT PA_CHANNEL_POSITION_FRONT_RIGHT
#define PA_CHANNEL_POSITION_FRONT_CENTER PA_CHANNEL_POSITION_FRONT_CENTER
#define PA_CHANNEL_POSITION_REAR_CENTER PA_CHANNEL_POSITION_REAR_CENTER
#define PA_CHANNEL_POSITION_REAR_LEFT PA_CHANNEL_POSITION_REAR_LEFT
#define PA_CHANNEL_POSITION_REAR_RIGHT PA_CHANNEL_POSITION_REAR_RIGHT
#define PA_CHANNEL_POSITION_LFE PA_CHANNEL_POSITION_LFE
#define PA_CHANNEL_POSITION_SUBWOOFER PA_CHANNEL_POSITION_SUBWOOFER
#define PA_CHANNEL_POSITION_FRONT_LEFT_OF_CENTER PA_CHANNEL_POSITION_FRONT_LEFT_OF_CENTER
#define PA_CHANNEL_POSITION_FRONT_RIGHT_OF_CENTER PA_CHANNEL_POSITION_FRONT_RIGHT_OF_CENTER
#define PA_CHANNEL_POSITION_SIDE_LEFT PA_CHANNEL_POSITION_SIDE_LEFT
#define PA_CHANNEL_POSITION_SIDE_RIGHT PA_CHANNEL_POSITION_SIDE_RIGHT
#define PA_CHANNEL_POSITION_AUX0 PA_CHANNEL_POSITION_AUX0
#define PA_CHANNEL_POSITION_AUX1 PA_CHANNEL_POSITION_AUX1
#define PA_CHANNEL_POSITION_AUX2 PA_CHANNEL_POSITION_AUX2
#define PA_CHANNEL_POSITION_AUX3 PA_CHANNEL_POSITION_AUX3
#define PA_CHANNEL_POSITION_AUX4 PA_CHANNEL_POSITION_AUX4
#define PA_CHANNEL_POSITION_AUX5 PA_CHANNEL_POSITION_AUX5
#define PA_CHANNEL_POSITION_AUX6 PA_CHANNEL_POSITION_AUX6
#define PA_CHANNEL_POSITION_AUX7 PA_CHANNEL_POSITION_AUX7
#define PA_CHANNEL_POSITION_AUX8 PA_CHANNEL_POSITION_AUX8
#define PA_CHANNEL_POSITION_AUX9 PA_CHANNEL_POSITION_AUX9
#define PA_CHANNEL_POSITION_AUX10 PA_CHANNEL_POSITION_AUX10
#define PA_CHANNEL_POSITION_AUX11 PA_CHANNEL_POSITION_AUX11
#define PA_CHANNEL_POSITION_AUX12 PA_CHANNEL_POSITION_AUX12
#define PA_CHANNEL_POSITION_AUX13 PA_CHANNEL_POSITION_AUX13
#define PA_CHANNEL_POSITION_AUX14 PA_CHANNEL_POSITION_AUX14
#define PA_CHANNEL_POSITION_AUX15 PA_CHANNEL_POSITION_AUX15
#define PA_CHANNEL_POSITION_AUX16 PA_CHANNEL_POSITION_AUX16
#define PA_CHANNEL_POSITION_AUX17 PA_CHANNEL_POSITION_AUX17
#define PA_CHANNEL_POSITION_AUX18 PA_CHANNEL_POSITION_AUX18
#define PA_CHANNEL_POSITION_AUX19 PA_CHANNEL_POSITION_AUX19
#define PA_CHANNEL_POSITION_AUX20 PA_CHANNEL_POSITION_AUX20
#define PA_CHANNEL_POSITION_AUX21 PA_CHANNEL_POSITION_AUX21
#define PA_CHANNEL_POSITION_AUX22 PA_CHANNEL_POSITION_AUX22
#define PA_CHANNEL_POSITION_AUX23 PA_CHANNEL_POSITION_AUX23
#define PA_CHANNEL_POSITION_AUX24 PA_CHANNEL_POSITION_AUX24
#define PA_CHANNEL_POSITION_AUX25 PA_CHANNEL_POSITION_AUX25
#define PA_CHANNEL_POSITION_AUX26 PA_CHANNEL_POSITION_AUX26
#define PA_CHANNEL_POSITION_AUX27 PA_CHANNEL_POSITION_AUX27
#define PA_CHANNEL_POSITION_AUX28 PA_CHANNEL_POSITION_AUX28
#define PA_CHANNEL_POSITION_AUX29 PA_CHANNEL_POSITION_AUX29
#define PA_CHANNEL_POSITION_AUX30 PA_CHANNEL_POSITION_AUX30
#define PA_CHANNEL_POSITION_AUX31 PA_CHANNEL_POSITION_AUX31
#define PA_CHANNEL_POSITION_TOP_CENTER PA_CHANNEL_POSITION_TOP_CENTER
#define PA_CHANNEL_POSITION_TOP_FRONT_LEFT PA_CHANNEL_POSITION_TOP_FRONT_LEFT
#define PA_CHANNEL_POSITION_TOP_FRONT_RIGHT PA_CHANNEL_POSITION_TOP_FRONT_RIGHT
#define PA_CHANNEL_POSITION_TOP_FRONT_CENTER PA_CHANNEL_POSITION_TOP_FRONT_CENTER
#define PA_CHANNEL_POSITION_TOP_REAR_LEFT PA_CHANNEL_POSITION_TOP_REAR_LEFT
#define PA_CHANNEL_POSITION_TOP_REAR_RIGHT PA_CHANNEL_POSITION_TOP_REAR_RIGHT
#define PA_CHANNEL_POSITION_TOP_REAR_CENTER PA_CHANNEL_POSITION_TOP_REAR_CENTER
#define PA_CHANNEL_POSITION_MAX PA_CHANNEL_POSITION_MAX
typedef uint64_t pa_channel_position_mask_t;
#define PA_CHANNEL_POSITION_MASK(f) ((pa_channel_position_mask_t) (1ULL << (f)))
typedef enum pa_channel_map_def {
    PA_CHANNEL_MAP_AIFF,
    PA_CHANNEL_MAP_ALSA,
    PA_CHANNEL_MAP_AUX,
    PA_CHANNEL_MAP_WAVEEX,
    PA_CHANNEL_MAP_OSS,
    PA_CHANNEL_MAP_DEF_MAX,
    PA_CHANNEL_MAP_DEFAULT = PA_CHANNEL_MAP_AIFF
} pa_channel_map_def_t;
#define PA_CHANNEL_MAP_AIFF PA_CHANNEL_MAP_AIFF
#define PA_CHANNEL_MAP_ALSA PA_CHANNEL_MAP_ALSA
#define PA_CHANNEL_MAP_AUX PA_CHANNEL_MAP_AUX
#define PA_CHANNEL_MAP_WAVEEX PA_CHANNEL_MAP_WAVEEX
#define PA_CHANNEL_MAP_OSS PA_CHANNEL_MAP_OSS
#define PA_CHANNEL_MAP_DEF_MAX PA_CHANNEL_MAP_DEF_MAX
#define PA_CHANNEL_MAP_DEFAULT PA_CHANNEL_MAP_DEFAULT
typedef pa_channel_map* (__cdecl *pa_channel_map_init_auto)(pa_channel_map *m, unsigned channels, pa_channel_map_def_t def);
typedef pa_operation_state_t (__cdecl *pa_operation_get_state)(pa_operation *o);

typedef uint32_t (__cdecl *pa_stream_get_index)(pa_stream *s); 
typedef pa_volume_t (__cdecl *pa_sw_volume_from_dB)(double f);
typedef double(__cdecl* pa_sw_volume_to_dB)(pa_volume_t v);
typedef pa_operation* (__cdecl *pa_context_set_sink_input_volume)(pa_context *c, uint32_t idx, const pa_cvolume *volume, pa_context_success_cb_t cb, void *userdata);
typedef pa_cvolume* (__cdecl *pa_cvolume_init)(pa_cvolume *a);
typedef pa_cvolume* (__cdecl *pa_cvolume_set)(pa_cvolume *a, unsigned channels, pa_volume_t v);
typedef void (__cdecl *pa_context_set_event_callback)(pa_context *p, pa_context_event_cb_t cb, void *userdata);

typedef int(__cdecl* pa_cvolume_valid)(const pa_cvolume* v);
typedef int(__cdecl* pa_cvolume_equal)(const pa_cvolume* a, const pa_cvolume* b);

typedef enum pa_encoding {
    PA_ENCODING_ANY,
    PA_ENCODING_PCM,
    PA_ENCODING_AC3_IEC61937,
    PA_ENCODING_EAC3_IEC61937,
    PA_ENCODING_MPEG_IEC61937,
    PA_ENCODING_DTS_IEC61937,
    PA_ENCODING_MAX,
    PA_ENCODING_INVALID = -1,
} pa_encoding_t;

typedef struct pa_format_info {
    pa_encoding_t encoding;
    pa_proplist *plist;
} pa_format_info;

typedef struct pa_sink_input_info {
    uint32_t index;
    const char *name;
    uint32_t owner_module;
    uint32_t client;
    uint32_t sink;
    pa_sample_spec sample_spec;
    pa_channel_map channel_map;
    pa_cvolume volume;
    pa_usec_t buffer_usec;
    pa_usec_t sink_usec;
    const char *resample_method;
    const char *driver;
    int mute;
    pa_proplist *proplist;
    int corked;
    int has_volume;
    int volume_writable;
    pa_format_info *format;
} pa_sink_input_info;

typedef void (*pa_sink_input_info_cb_t) (pa_context *c, const pa_sink_input_info *i, int eol, void *userdata);
typedef pa_operation* (__cdecl *pa_context_get_sink_input_info)(pa_context *c, uint32_t idx, pa_sink_input_info_cb_t cb, void *userdata);

typedef enum pa_subscription_mask {
    PA_SUBSCRIPTION_MASK_NULL = 0x0000U,
    PA_SUBSCRIPTION_MASK_SINK = 0x0001U,
    PA_SUBSCRIPTION_MASK_SOURCE = 0x0002U,
    PA_SUBSCRIPTION_MASK_SINK_INPUT = 0x0004U,
    PA_SUBSCRIPTION_MASK_SOURCE_OUTPUT = 0x0008U,
    PA_SUBSCRIPTION_MASK_MODULE = 0x0010U,
    PA_SUBSCRIPTION_MASK_CLIENT = 0x0020U,
    PA_SUBSCRIPTION_MASK_SAMPLE_CACHE = 0x0040U,
    PA_SUBSCRIPTION_MASK_SERVER = 0x0080U,
    PA_SUBSCRIPTION_MASK_AUTOLOAD = 0x0100U,
    PA_SUBSCRIPTION_MASK_CARD = 0x0200U,
    PA_SUBSCRIPTION_MASK_ALL = 0x02ffU
} pa_subscription_mask_t;

typedef enum pa_subscription_event_type {
    PA_SUBSCRIPTION_EVENT_SINK = 0x0000U,
    PA_SUBSCRIPTION_EVENT_SOURCE = 0x0001U,
    PA_SUBSCRIPTION_EVENT_SINK_INPUT = 0x0002U,
    PA_SUBSCRIPTION_EVENT_SOURCE_OUTPUT = 0x0003U,
    PA_SUBSCRIPTION_EVENT_MODULE = 0x0004U,
    PA_SUBSCRIPTION_EVENT_CLIENT = 0x0005U,
    PA_SUBSCRIPTION_EVENT_SAMPLE_CACHE = 0x0006U,
    PA_SUBSCRIPTION_EVENT_SERVER = 0x0007U,
    PA_SUBSCRIPTION_EVENT_AUTOLOAD = 0x0008U,
    PA_SUBSCRIPTION_EVENT_CARD = 0x0009U,
    PA_SUBSCRIPTION_EVENT_FACILITY_MASK = 0x000FU,
    PA_SUBSCRIPTION_EVENT_NEW = 0x0000U,
    PA_SUBSCRIPTION_EVENT_CHANGE = 0x0010U,
    PA_SUBSCRIPTION_EVENT_REMOVE = 0x0020U,
    PA_SUBSCRIPTION_EVENT_TYPE_MASK = 0x0030U
} pa_subscription_event_type_t;

#define pa_subscription_match_flags(m, t) (!!((m) & (1 << ((t) & PA_SUBSCRIPTION_EVENT_FACILITY_MASK))))

#define PA_SUBSCRIPTION_MASK_NULL PA_SUBSCRIPTION_MASK_NULL
#define PA_SUBSCRIPTION_MASK_SINK PA_SUBSCRIPTION_MASK_SINK
#define PA_SUBSCRIPTION_MASK_SOURCE PA_SUBSCRIPTION_MASK_SOURCE
#define PA_SUBSCRIPTION_MASK_SINK_INPUT PA_SUBSCRIPTION_MASK_SINK_INPUT
#define PA_SUBSCRIPTION_MASK_SOURCE_OUTPUT PA_SUBSCRIPTION_MASK_SOURCE_OUTPUT
#define PA_SUBSCRIPTION_MASK_MODULE PA_SUBSCRIPTION_MASK_MODULE
#define PA_SUBSCRIPTION_MASK_CLIENT PA_SUBSCRIPTION_MASK_CLIENT
#define PA_SUBSCRIPTION_MASK_SAMPLE_CACHE PA_SUBSCRIPTION_MASK_SAMPLE_CACHE
#define PA_SUBSCRIPTION_MASK_SERVER PA_SUBSCRIPTION_MASK_SERVER
#define PA_SUBSCRIPTION_MASK_AUTOLOAD PA_SUBSCRIPTION_MASK_AUTOLOAD
#define PA_SUBSCRIPTION_MASK_CARD PA_SUBSCRIPTION_MASK_CARD
#define PA_SUBSCRIPTION_MASK_ALL PA_SUBSCRIPTION_MASK_ALL
#define PA_SUBSCRIPTION_EVENT_SINK PA_SUBSCRIPTION_EVENT_SINK
#define PA_SUBSCRIPTION_EVENT_SOURCE PA_SUBSCRIPTION_EVENT_SOURCE
#define PA_SUBSCRIPTION_EVENT_SINK_INPUT PA_SUBSCRIPTION_EVENT_SINK_INPUT
#define PA_SUBSCRIPTION_EVENT_SOURCE_OUTPUT PA_SUBSCRIPTION_EVENT_SOURCE_OUTPUT
#define PA_SUBSCRIPTION_EVENT_MODULE PA_SUBSCRIPTION_EVENT_MODULE
#define PA_SUBSCRIPTION_EVENT_CLIENT PA_SUBSCRIPTION_EVENT_CLIENT
#define PA_SUBSCRIPTION_EVENT_SAMPLE_CACHE PA_SUBSCRIPTION_EVENT_SAMPLE_CACHE
#define PA_SUBSCRIPTION_EVENT_SERVER PA_SUBSCRIPTION_EVENT_SERVER
#define PA_SUBSCRIPTION_EVENT_AUTOLOAD PA_SUBSCRIPTION_EVENT_AUTOLOAD
#define PA_SUBSCRIPTION_EVENT_CARD PA_SUBSCRIPTION_EVENT_CARD
#define PA_SUBSCRIPTION_EVENT_FACILITY_MASK PA_SUBSCRIPTION_EVENT_FACILITY_MASK
#define PA_SUBSCRIPTION_EVENT_NEW PA_SUBSCRIPTION_EVENT_NEW
#define PA_SUBSCRIPTION_EVENT_CHANGE PA_SUBSCRIPTION_EVENT_CHANGE
#define PA_SUBSCRIPTION_EVENT_REMOVE PA_SUBSCRIPTION_EVENT_REMOVE
#define PA_SUBSCRIPTION_EVENT_TYPE_MASK PA_SUBSCRIPTION_EVENT_TYPE_MASK

typedef void (*pa_context_subscribe_cb_t)(pa_context *c, pa_subscription_event_type_t t, uint32_t idx, void *userdata);
typedef pa_operation* (__cdecl *pa_context_subscribe)(pa_context *c, pa_subscription_mask_t m, pa_context_success_cb_t cb, void *userdata);
typedef void (__cdecl *pa_context_set_subscribe_callback)(pa_context *c, pa_context_subscribe_cb_t cb, void *userdata);
