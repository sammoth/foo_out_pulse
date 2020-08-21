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
// todo if problem: check cond fulldocs in pulse source
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

//// -- from operation.h
typedef pa_operation* (__cdecl *pa_operation_ref)(pa_operation *o);
typedef void (__cdecl *pa_operation_unref)(pa_operation *o);
typedef void (__cdecl *pa_operation_cancel)(pa_operation *o);
//typedef pa_operation_state_t (__cdecl *pa_operation_get_state)(pa_operation *o);

//
// -- from proplist.h
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
//typedef void (__cdecl *pa_proplist_setf)(pa_proplist *p, const char *key, const char *format, ...) PA_GCC_PRINTF_ATTR(3,4);
typedef void (__cdecl *pa_proplist_set)(pa_proplist *p, const char *key, const void *data, size_t nbytes);
//const char *pa_proplist_gets(pa_proplist *p, const char *key);
//int pa_proplist_get(pa_proplist *p, const char *key, const void **data, size_t *nbytes);
//typedef enum pa_update_mode {
//    PA_UPDATE_SET
//    ,
//    PA_UPDATE_MERGE
//    ,
//    PA_UPDATE_REPLACE
//    
//} pa_update_mode_t;
//#define PA_UPDATE_SET PA_UPDATE_SET
//#define PA_UPDATE_MERGE PA_UPDATE_MERGE
//#define PA_UPDATE_REPLACE PA_UPDATE_REPLACE
//
//void pa_proplist_update(pa_proplist *p, pa_update_mode_t mode, pa_proplist *other);
//int pa_proplist_unset(pa_proplist *p, const char *key);
//int pa_proplist_unset_many(pa_proplist *p, const char * const keys[]);
//const char *pa_proplist_iterate(pa_proplist *p, void **state);
//char *pa_proplist_to_string(pa_proplist *p);
//char *pa_proplist_to_string_sep(pa_proplist *p, const char *sep);
//pa_proplist *pa_proplist_from_string(const char *str);
//int pa_proplist_contains(pa_proplist *p, const char *key);
//void pa_proplist_clear(pa_proplist *p);
//pa_proplist* pa_proplist_copy(pa_proplist *t);
//unsigned pa_proplist_size(pa_proplist *t);
//int pa_proplist_isempty(pa_proplist *t);
//int pa_proplist_equal(pa_proplist *a, pa_proplist *b);
//// -- from def.h
typedef enum pa_context_state {
    PA_CONTEXT_UNCONNECTED,    
    PA_CONTEXT_CONNECTING,     
    PA_CONTEXT_AUTHORIZING,    
    PA_CONTEXT_SETTING_NAME,   
    PA_CONTEXT_READY,          
    PA_CONTEXT_FAILED,         
    PA_CONTEXT_TERMINATED      
} pa_context_state_t;
//static inline int PA_CONTEXT_IS_GOOD(pa_context_state_t x) {
//    return
//        x == PA_CONTEXT_CONNECTING ||
//        x == PA_CONTEXT_AUTHORIZING ||
//        x == PA_CONTEXT_SETTING_NAME ||
//        x == PA_CONTEXT_READY;
//}
#define PA_CONTEXT_UNCONNECTED PA_CONTEXT_UNCONNECTED
#define PA_CONTEXT_CONNECTING PA_CONTEXT_CONNECTING
#define PA_CONTEXT_AUTHORIZING PA_CONTEXT_AUTHORIZING
#define PA_CONTEXT_SETTING_NAME PA_CONTEXT_SETTING_NAME
#define PA_CONTEXT_READY PA_CONTEXT_READY
#define PA_CONTEXT_FAILED PA_CONTEXT_FAILED
#define PA_CONTEXT_TERMINATED PA_CONTEXT_TERMINATED
//
typedef enum pa_stream_state {
    PA_STREAM_UNCONNECTED,  
    PA_STREAM_CREATING,     
    PA_STREAM_READY,        
    PA_STREAM_FAILED,       
    PA_STREAM_TERMINATED    
} pa_stream_state_t;
//static inline int PA_STREAM_IS_GOOD(pa_stream_state_t x) {
//    return
//        x == PA_STREAM_CREATING ||
//        x == PA_STREAM_READY;
//}
//#define PA_STREAM_UNCONNECTED PA_STREAM_UNCONNECTED
//#define PA_STREAM_CREATING PA_STREAM_CREATING
//#define PA_STREAM_READY PA_STREAM_READY
//#define PA_STREAM_FAILED PA_STREAM_FAILED
//#define PA_STREAM_TERMINATED PA_STREAM_TERMINATED
//#define PA_STREAM_IS_GOOD PA_STREAM_IS_GOOD
//
typedef enum pa_operation_state {
    PA_OPERATION_RUNNING,      
    PA_OPERATION_DONE,         
    PA_OPERATION_CANCELLED     
} pa_operation_state_t;
//#define PA_OPERATION_RUNNING PA_OPERATION_RUNNING
//#define PA_OPERATION_DONE PA_OPERATION_DONE
//#define PA_OPERATION_CANCELED PA_OPERATION_CANCELLED
//#define PA_OPERATION_CANCELLED PA_OPERATION_CANCELLED
//
//#define PA_INVALID_INDEX ((uint32_t) -1)
typedef enum pa_context_flags {
    PA_CONTEXT_NOFLAGS = 0x0000U,
    PA_CONTEXT_NOAUTOSPAWN = 0x0001U,
    PA_CONTEXT_NOFAIL = 0x0002U
} pa_context_flags_t;
//
//#define PA_CONTEXT_NOAUTOSPAWN PA_CONTEXT_NOAUTOSPAWN
//#define PA_CONTEXT_NOFAIL PA_CONTEXT_NOFAIL
//
//typedef enum pa_device_type {
//    PA_DEVICE_TYPE_SINK,     
//    PA_DEVICE_TYPE_SOURCE    
//} pa_device_type_t;
//#define PA_DEVICE_TYPE_SINK PA_DEVICE_TYPE_SINK
//#define PA_DEVICE_TYPE_SOURCE PA_DEVICE_TYPE_SOURCE
//
//#define PA_STREAM_NODIRECTION PA_STREAM_NODIRECTION
//#define PA_STREAM_PLAYBACK PA_STREAM_PLAYBACK
//#define PA_STREAM_RECORD PA_STREAM_RECORD
//#define PA_STREAM_UPLOAD PA_STREAM_UPLOAD
//
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
//
//typedef struct pa_buffer_attr {
//    uint32_t maxlength;
//    
//    uint32_t tlength;
//    
//    uint32_t prebuf;
//    
//    uint32_t minreq;
//    
//    uint32_t fragsize;
//    
//} pa_buffer_attr;
//enum {
//    PA_OK = 0,                     
//    PA_ERR_ACCESS,                 
//    PA_ERR_COMMAND,                
//    PA_ERR_INVALID,                
//    PA_ERR_EXIST,                  
//    PA_ERR_NOENTITY,               
//    PA_ERR_CONNECTIONREFUSED,      
//    PA_ERR_PROTOCOL,               
//    PA_ERR_TIMEOUT,                
//    PA_ERR_AUTHKEY,                
//    PA_ERR_INTERNAL,               
//    PA_ERR_CONNECTIONTERMINATED,   
//    PA_ERR_KILLED,                 
//    PA_ERR_INVALIDSERVER,          
//    PA_ERR_MODINITFAILED,          
//    PA_ERR_BADSTATE,               
//    PA_ERR_NODATA,                 
//    PA_ERR_VERSION,                
//    PA_ERR_TOOLARGE,               
//    PA_ERR_NOTSUPPORTED,           
//    PA_ERR_UNKNOWN,                
//    PA_ERR_NOEXTENSION,            
//    PA_ERR_OBSOLETE,               
//    PA_ERR_NOTIMPLEMENTED,         
//    PA_ERR_FORKED,                 
//    PA_ERR_IO,                     
//    PA_ERR_BUSY,                   
//    PA_ERR_MAX                     
//};
//#define PA_OK PA_OK
//#define PA_ERR_ACCESS PA_ERR_ACCESS
//#define PA_ERR_COMMAND PA_ERR_COMMAND
//#define PA_ERR_INVALID PA_ERR_INVALID
//#define PA_ERR_EXIST PA_ERR_EXIST
//#define PA_ERR_NOENTITY PA_ERR_NOENTITY
//#define PA_ERR_CONNECTIONREFUSED PA_ERR_CONNECTIONREFUSED
//#define PA_ERR_PROTOCOL PA_ERR_PROTOCOL
//#define PA_ERR_TIMEOUT PA_ERR_TIMEOUT
//#define PA_ERR_AUTHKEY PA_ERR_AUTHKEY
//#define PA_ERR_INTERNAL PA_ERR_INTERNAL
//#define PA_ERR_CONNECTIONTERMINATED PA_ERR_CONNECTIONTERMINATED
//#define PA_ERR_KILLED PA_ERR_KILLED
//#define PA_ERR_INVALIDSERVER PA_ERR_INVALIDSERVER
//#define PA_ERR_MODINITFAILED PA_ERR_MODINITFAILED
//#define PA_ERR_BADSTATE PA_ERR_BADSTATE
//#define PA_ERR_NODATA PA_ERR_NODATA
//#define PA_ERR_VERSION PA_ERR_VERSION
//#define PA_ERR_TOOLARGE PA_ERR_TOOLARGE
//#define PA_ERR_NOTSUPPORTED PA_ERR_NOTSUPPORTED
//#define PA_ERR_UNKNOWN PA_ERR_UNKNOWN
//#define PA_ERR_NOEXTENSION PA_ERR_NOEXTENSION
//#define PA_ERR_OBSOLETE PA_ERR_OBSOLETE
//#define PA_ERR_NOTIMPLEMENTED PA_ERR_NOTIMPLEMENTED
//#define PA_ERR_FORKED PA_ERR_FORKED
//#define PA_ERR_MAX PA_ERR_MAX
//
//typedef enum pa_subscription_mask {
//    PA_SUBSCRIPTION_MASK_NULL = 0x0000U,
//    
//    PA_SUBSCRIPTION_MASK_SINK = 0x0001U,
//    
//    PA_SUBSCRIPTION_MASK_SOURCE = 0x0002U,
//    
//    PA_SUBSCRIPTION_MASK_SINK_INPUT = 0x0004U,
//    
//    PA_SUBSCRIPTION_MASK_SOURCE_OUTPUT = 0x0008U,
//    
//    PA_SUBSCRIPTION_MASK_MODULE = 0x0010U,
//    
//    PA_SUBSCRIPTION_MASK_CLIENT = 0x0020U,
//    
//    PA_SUBSCRIPTION_MASK_SAMPLE_CACHE = 0x0040U,
//    
//    PA_SUBSCRIPTION_MASK_SERVER = 0x0080U,
//    
//    PA_SUBSCRIPTION_MASK_AUTOLOAD = 0x0100U,
//    
//    PA_SUBSCRIPTION_MASK_CARD = 0x0200U,
//    
//    PA_SUBSCRIPTION_MASK_ALL = 0x02ffU
//    
//} pa_subscription_mask_t;
//typedef enum pa_subscription_event_type {
//    PA_SUBSCRIPTION_EVENT_SINK = 0x0000U,
//    
//    PA_SUBSCRIPTION_EVENT_SOURCE = 0x0001U,
//    
//    PA_SUBSCRIPTION_EVENT_SINK_INPUT = 0x0002U,
//    
//    PA_SUBSCRIPTION_EVENT_SOURCE_OUTPUT = 0x0003U,
//    
//    PA_SUBSCRIPTION_EVENT_MODULE = 0x0004U,
//    
//    PA_SUBSCRIPTION_EVENT_CLIENT = 0x0005U,
//    
//    PA_SUBSCRIPTION_EVENT_SAMPLE_CACHE = 0x0006U,
//    
//    PA_SUBSCRIPTION_EVENT_SERVER = 0x0007U,
//    
//    PA_SUBSCRIPTION_EVENT_AUTOLOAD = 0x0008U,
//    
//    PA_SUBSCRIPTION_EVENT_CARD = 0x0009U,
//    
//    PA_SUBSCRIPTION_EVENT_FACILITY_MASK = 0x000FU,
//    
//    PA_SUBSCRIPTION_EVENT_NEW = 0x0000U,
//    
//    PA_SUBSCRIPTION_EVENT_CHANGE = 0x0010U,
//    
//    PA_SUBSCRIPTION_EVENT_REMOVE = 0x0020U,
//    
//    PA_SUBSCRIPTION_EVENT_TYPE_MASK = 0x0030U
//    
//} pa_subscription_event_type_t;
//#define pa_subscription_match_flags(m, t) (!!((m) & (1 << ((t) & PA_SUBSCRIPTION_EVENT_FACILITY_MASK))))
//#define PA_SUBSCRIPTION_MASK_NULL PA_SUBSCRIPTION_MASK_NULL
//#define PA_SUBSCRIPTION_MASK_SINK PA_SUBSCRIPTION_MASK_SINK
//#define PA_SUBSCRIPTION_MASK_SOURCE PA_SUBSCRIPTION_MASK_SOURCE
//#define PA_SUBSCRIPTION_MASK_SINK_INPUT PA_SUBSCRIPTION_MASK_SINK_INPUT
//#define PA_SUBSCRIPTION_MASK_SOURCE_OUTPUT PA_SUBSCRIPTION_MASK_SOURCE_OUTPUT
//#define PA_SUBSCRIPTION_MASK_MODULE PA_SUBSCRIPTION_MASK_MODULE
//#define PA_SUBSCRIPTION_MASK_CLIENT PA_SUBSCRIPTION_MASK_CLIENT
//#define PA_SUBSCRIPTION_MASK_SAMPLE_CACHE PA_SUBSCRIPTION_MASK_SAMPLE_CACHE
//#define PA_SUBSCRIPTION_MASK_SERVER PA_SUBSCRIPTION_MASK_SERVER
//#define PA_SUBSCRIPTION_MASK_AUTOLOAD PA_SUBSCRIPTION_MASK_AUTOLOAD
//#define PA_SUBSCRIPTION_MASK_CARD PA_SUBSCRIPTION_MASK_CARD
//#define PA_SUBSCRIPTION_MASK_ALL PA_SUBSCRIPTION_MASK_ALL
//#define PA_SUBSCRIPTION_EVENT_SINK PA_SUBSCRIPTION_EVENT_SINK
//#define PA_SUBSCRIPTION_EVENT_SOURCE PA_SUBSCRIPTION_EVENT_SOURCE
//#define PA_SUBSCRIPTION_EVENT_SINK_INPUT PA_SUBSCRIPTION_EVENT_SINK_INPUT
//#define PA_SUBSCRIPTION_EVENT_SOURCE_OUTPUT PA_SUBSCRIPTION_EVENT_SOURCE_OUTPUT
//#define PA_SUBSCRIPTION_EVENT_MODULE PA_SUBSCRIPTION_EVENT_MODULE
//#define PA_SUBSCRIPTION_EVENT_CLIENT PA_SUBSCRIPTION_EVENT_CLIENT
//#define PA_SUBSCRIPTION_EVENT_SAMPLE_CACHE PA_SUBSCRIPTION_EVENT_SAMPLE_CACHE
//#define PA_SUBSCRIPTION_EVENT_SERVER PA_SUBSCRIPTION_EVENT_SERVER
//#define PA_SUBSCRIPTION_EVENT_AUTOLOAD PA_SUBSCRIPTION_EVENT_AUTOLOAD
//#define PA_SUBSCRIPTION_EVENT_CARD PA_SUBSCRIPTION_EVENT_CARD
//#define PA_SUBSCRIPTION_EVENT_FACILITY_MASK PA_SUBSCRIPTION_EVENT_FACILITY_MASK
//#define PA_SUBSCRIPTION_EVENT_NEW PA_SUBSCRIPTION_EVENT_NEW
//#define PA_SUBSCRIPTION_EVENT_CHANGE PA_SUBSCRIPTION_EVENT_CHANGE
//#define PA_SUBSCRIPTION_EVENT_REMOVE PA_SUBSCRIPTION_EVENT_REMOVE
//#define PA_SUBSCRIPTION_EVENT_TYPE_MASK PA_SUBSCRIPTION_EVENT_TYPE_MASK
//
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
//#define PA_SEEK_RELATIVE PA_SEEK_RELATIVE
//#define PA_SEEK_ABSOLUTE PA_SEEK_ABSOLUTE
//#define PA_SEEK_RELATIVE_ON_READ PA_SEEK_RELATIVE_ON_READ
//#define PA_SEEK_RELATIVE_END PA_SEEK_RELATIVE_END
//
//typedef enum pa_sink_flags {
//    PA_SINK_NOFLAGS = 0x0000U,
//    
//    PA_SINK_HW_VOLUME_CTRL = 0x0001U,
//    
//    PA_SINK_LATENCY = 0x0002U,
//    
//    PA_SINK_HARDWARE = 0x0004U,
//    
//    PA_SINK_NETWORK = 0x0008U,
//    
//    PA_SINK_HW_MUTE_CTRL = 0x0010U,
//    
//    PA_SINK_DECIBEL_VOLUME = 0x0020U,
//    
//    PA_SINK_FLAT_VOLUME = 0x0040U,
//    
//    PA_SINK_DYNAMIC_LATENCY = 0x0080U,
//    
//    PA_SINK_SET_FORMATS = 0x0100U,
//    
//#ifdef __INCLUDED_FROM_PULSE_AUDIO
//    
//    PA_SINK_SHARE_VOLUME_WITH_MASTER = 0x1000000U,
//    
//    PA_SINK_DEFERRED_VOLUME = 0x2000000U,
//    
//#endif
//} pa_sink_flags_t;
//#define PA_SINK_HW_VOLUME_CTRL PA_SINK_HW_VOLUME_CTRL
//#define PA_SINK_LATENCY PA_SINK_LATENCY
//#define PA_SINK_HARDWARE PA_SINK_HARDWARE
//#define PA_SINK_NETWORK PA_SINK_NETWORK
//#define PA_SINK_HW_MUTE_CTRL PA_SINK_HW_MUTE_CTRL
//#define PA_SINK_DECIBEL_VOLUME PA_SINK_DECIBEL_VOLUME
//#define PA_SINK_FLAT_VOLUME PA_SINK_FLAT_VOLUME
//#define PA_SINK_DYNAMIC_LATENCY PA_SINK_DYNAMIC_LATENCY
//#define PA_SINK_SET_FORMATS PA_SINK_SET_FORMATS
//#ifdef __INCLUDED_FROM_PULSE_AUDIO
//#define PA_SINK_CLIENT_FLAGS_MASK 0xFFFFFF
//#endif
//
//typedef enum pa_sink_state { 
//    PA_SINK_INVALID_STATE = -1,
//    
//    PA_SINK_RUNNING = 0,
//    
//    PA_SINK_IDLE = 1,
//    
//    PA_SINK_SUSPENDED = 2,
//    
//    
//    PA_SINK_INIT = -2,
//    
//    PA_SINK_UNLINKED = -3
//    
//} pa_sink_state_t;
//static inline int PA_SINK_IS_OPENED(pa_sink_state_t x) {
//    return x == PA_SINK_RUNNING || x == PA_SINK_IDLE;
//}
//#define PA_SINK_INVALID_STATE PA_SINK_INVALID_STATE
//#define PA_SINK_RUNNING PA_SINK_RUNNING
//#define PA_SINK_IDLE PA_SINK_IDLE
//#define PA_SINK_SUSPENDED PA_SINK_SUSPENDED
//#define PA_SINK_INIT PA_SINK_INIT
//#define PA_SINK_UNLINKED PA_SINK_UNLINKED
//#define PA_SINK_IS_OPENED PA_SINK_IS_OPENED
//
//typedef enum pa_source_flags {
//    PA_SOURCE_NOFLAGS = 0x0000U,
//    
//    PA_SOURCE_HW_VOLUME_CTRL = 0x0001U,
//    
//    PA_SOURCE_LATENCY = 0x0002U,
//    
//    PA_SOURCE_HARDWARE = 0x0004U,
//    
//    PA_SOURCE_NETWORK = 0x0008U,
//    
//    PA_SOURCE_HW_MUTE_CTRL = 0x0010U,
//    
//    PA_SOURCE_DECIBEL_VOLUME = 0x0020U,
//    
//    PA_SOURCE_DYNAMIC_LATENCY = 0x0040U,
//    
//    PA_SOURCE_FLAT_VOLUME = 0x0080U,
//    
//#ifdef __INCLUDED_FROM_PULSE_AUDIO
//    
//    PA_SOURCE_SHARE_VOLUME_WITH_MASTER = 0x1000000U,
//    
//    PA_SOURCE_DEFERRED_VOLUME = 0x2000000U,
//    
//#endif
//} pa_source_flags_t;
//#define PA_SOURCE_HW_VOLUME_CTRL PA_SOURCE_HW_VOLUME_CTRL
//#define PA_SOURCE_LATENCY PA_SOURCE_LATENCY
//#define PA_SOURCE_HARDWARE PA_SOURCE_HARDWARE
//#define PA_SOURCE_NETWORK PA_SOURCE_NETWORK
//#define PA_SOURCE_HW_MUTE_CTRL PA_SOURCE_HW_MUTE_CTRL
//#define PA_SOURCE_DECIBEL_VOLUME PA_SOURCE_DECIBEL_VOLUME
//#define PA_SOURCE_DYNAMIC_LATENCY PA_SOURCE_DYNAMIC_LATENCY
//#define PA_SOURCE_FLAT_VOLUME PA_SOURCE_FLAT_VOLUME
//#ifdef __INCLUDED_FROM_PULSE_AUDIO
//#define PA_SOURCE_CLIENT_FLAGS_MASK 0xFFFFFF
//#endif
//
//typedef enum pa_source_state {
//    PA_SOURCE_INVALID_STATE = -1,
//    
//    PA_SOURCE_RUNNING = 0,
//    
//    PA_SOURCE_IDLE = 1,
//    
//    PA_SOURCE_SUSPENDED = 2,
//    
//    
//    PA_SOURCE_INIT = -2,
//    
//    PA_SOURCE_UNLINKED = -3
//    
//} pa_source_state_t;
//static inline int PA_SOURCE_IS_OPENED(pa_source_state_t x) {
//    return x == PA_SOURCE_RUNNING || x == PA_SOURCE_IDLE;
//}
//#define PA_SOURCE_INVALID_STATE PA_SOURCE_INVALID_STATE
//#define PA_SOURCE_RUNNING PA_SOURCE_RUNNING
//#define PA_SOURCE_IDLE PA_SOURCE_IDLE
//#define PA_SOURCE_SUSPENDED PA_SOURCE_SUSPENDED
//#define PA_SOURCE_INIT PA_SOURCE_INIT
//#define PA_SOURCE_UNLINKED PA_SOURCE_UNLINKED
//#define PA_SOURCE_IS_OPENED PA_SOURCE_IS_OPENED
//
typedef void (*pa_free_cb_t)(void *p);
//#define PA_STREAM_EVENT_REQUEST_CORK "request-cork"
//#define PA_STREAM_EVENT_REQUEST_UNCORK "request-uncork"
//#define PA_STREAM_EVENT_FORMAT_LOST "format-lost"
// -- threaded main loop . h


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
//typedef int (__cdecl *pa_threaded_mainloop_in_thread)(pa_threaded_mainloop *m);

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

//void pa_mainloop_api_once(pa_mainloop_api*m, void (*callback)(pa_mainloop_api*m, void *userdata), void *userdata);
//// --- from context.h
//// cdecl?
typedef void (__cdecl *pa_context_notify_cb_t)(pa_context *c, void *userdata);
typedef void (__cdecl *pa_context_success_cb_t) (pa_context *c, int success, void *userdata);
typedef void (__cdecl *pa_context_event_cb_t)(pa_context *c, const char *name, pa_proplist *p, void *userdata);
//pa_context *pa_context_new(pa_mainloop_api *mainloop, const char *name);
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
//pa_operation* pa_context_exit_daemon(pa_context *c, pa_context_success_cb_t cb, void *userdata);
//pa_operation* pa_context_set_default_sink(pa_context *c, const char *name, pa_context_success_cb_t cb, void *userdata);
//pa_operation* pa_context_set_default_source(pa_context *c, const char *name, pa_context_success_cb_t cb, void *userdata);
//int pa_context_is_local(pa_context *c);
//pa_operation* pa_context_set_name(pa_context *c, const char *name, pa_context_success_cb_t cb, void *userdata);
//const char* pa_context_get_server(pa_context *c);
//uint32_t pa_context_get_protocol_version(pa_context *c);
//uint32_t pa_context_get_server_protocol_version(pa_context *c);
//pa_operation *pa_context_proplist_update(pa_context *c, pa_update_mode_t mode, pa_proplist *p, pa_context_success_cb_t cb, void *userdata);
//pa_operation *pa_context_proplist_remove(pa_context *c, const char *const keys[], pa_context_success_cb_t cb, void *userdata);
//uint32_t pa_context_get_index(pa_context *s);
//pa_time_event* pa_context_rttime_new(pa_context *c, pa_usec_t usec, pa_time_event_cb_t cb, void *userdata);
//void pa_context_rttime_restart(pa_context *c, pa_time_event *e, pa_usec_t usec);
//size_t pa_context_get_tile_size(pa_context *c, const pa_sample_spec *ss);
//// -- from stream.h
typedef void (*pa_stream_success_cb_t) (pa_stream*s, int success, void *userdata);
typedef void (*pa_stream_request_cb_t)(pa_stream *p, size_t nbytes, void *userdata);
typedef void (*pa_stream_notify_cb_t)(pa_stream *p, void *userdata);
//typedef void (*pa_stream_event_cb_t)(pa_stream *p, const char *name, pa_proplist *pl, void *userdata);
typedef pa_stream* (__cdecl *pa_stream_new)(
        pa_context *c                     ,
        const char *name                  ,
        const pa_sample_spec *ss          ,
        const pa_channel_map *map         );
//pa_stream* pa_stream_new_with_proplist(
//        pa_context *c                     ,
//        const char *name                  ,
//        const pa_sample_spec *ss          ,
//        const pa_channel_map *map         ,
//        pa_proplist *p                    );
//pa_stream *pa_stream_new_extended(
//        pa_context *c                     ,
//        const char *name                  ,
//        pa_format_info * const * formats  ,
//        unsigned int n_formats            ,
//        pa_proplist *p                    );
typedef void (__cdecl *pa_stream_unref)(pa_stream *s);
//pa_stream *pa_stream_ref(pa_stream *s);
typedef pa_stream_state_t (__cdecl *pa_stream_get_state)(pa_stream *p);
//pa_context* pa_stream_get_context(pa_stream *p);
//uint32_t pa_stream_get_index(pa_stream *s);
//uint32_t pa_stream_get_device_index(pa_stream *s);
//const char *pa_stream_get_device_name(pa_stream *s);
//int pa_stream_is_suspended(pa_stream *s);
//int pa_stream_is_corked(pa_stream *s);
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
//int pa_stream_connect_record(
//        pa_stream *s                   ,
//        const char *dev               ,
//        const pa_buffer_attr *attr    ,
//        pa_stream_flags_t flags       );
typedef int (__cdecl *pa_stream_disconnect)(pa_stream *s);
//int pa_stream_begin_write(
//        pa_stream *p,
//        void **data,
//        size_t *nbytes);
typedef int (__cdecl *pa_stream_cancel_write)(
        pa_stream *p);
typedef int (__cdecl *pa_stream_write)(
        pa_stream *p             ,
        const void *data         ,
        size_t nbytes            ,
        pa_free_cb_t free_cb     ,
        int64_t offset,          
        pa_seek_mode_t seek      );
//int pa_stream_peek(
//        pa_stream *p                 ,
//        const void **data            ,
//        size_t *nbytes               );
typedef int (__cdecl *pa_stream_drop)(pa_stream *p);
typedef size_t (__cdecl *pa_stream_writable_size)(pa_stream *p);
//typedef size_t (__cdecl *pa_stream_readable_size)(pa_stream *p);
typedef pa_operation* (__cdecl *pa_stream_drain)(pa_stream *s, pa_stream_success_cb_t cb, void *userdata);
//pa_operation* pa_stream_update_timing_info(pa_stream *p, pa_stream_success_cb_t cb, void *userdata);
typedef void (__cdecl *pa_stream_set_state_callback)(pa_stream *s, pa_stream_notify_cb_t cb, void *userdata);
typedef void (__cdecl *pa_stream_set_write_callback)(pa_stream *p, pa_stream_request_cb_t cb, void *userdata);
//void pa_stream_set_read_callback(pa_stream *p, pa_stream_request_cb_t cb, void *userdata);
//void pa_stream_set_overflow_callback(pa_stream *p, pa_stream_notify_cb_t cb, void *userdata);
//int64_t pa_stream_get_underflow_index(pa_stream *p);
typedef void (__cdecl *pa_stream_set_underflow_callback)(pa_stream *p, pa_stream_notify_cb_t cb, void *userdata);
typedef void (__cdecl *pa_stream_set_started_callback)(pa_stream *p, pa_stream_notify_cb_t cb, void *userdata);
//void pa_stream_set_latency_update_callback(pa_stream *p, pa_stream_notify_cb_t cb, void *userdata);
//void pa_stream_set_moved_callback(pa_stream *p, pa_stream_notify_cb_t cb, void *userdata);
//void pa_stream_set_suspended_callback(pa_stream *p, pa_stream_notify_cb_t cb, void *userdata);
//void pa_stream_set_event_callback(pa_stream *p, pa_stream_event_cb_t cb, void *userdata);
//void pa_stream_set_buffer_attr_callback(pa_stream *p, pa_stream_notify_cb_t cb, void *userdata);
typedef pa_operation* (__cdecl *pa_stream_cork)(pa_stream *s, int b, pa_stream_success_cb_t cb, void *userdata);
typedef pa_operation* (__cdecl *pa_stream_flush)(pa_stream *s, pa_stream_success_cb_t cb, void *userdata);
//pa_operation* pa_stream_prebuf(pa_stream *s, pa_stream_success_cb_t cb, void *userdata);
//pa_operation* pa_stream_trigger(pa_stream *s, pa_stream_success_cb_t cb, void *userdata);
//pa_operation* pa_stream_set_name(pa_stream *s, const char *name, pa_stream_success_cb_t cb, void *userdata);
//int pa_stream_get_time(pa_stream *s, pa_usec_t *r_usec);
typedef int (__cdecl *pa_stream_get_latency)(pa_stream *s, pa_usec_t *r_usec, int *negative);
typedef const pa_timing_info* (__cdecl *pa_stream_get_timing_info)(pa_stream *s);
typedef const pa_sample_spec* (__cdecl *pa_stream_get_sample_spec)(pa_stream *s);
//const pa_channel_map* pa_stream_get_channel_map(pa_stream *s);
//const pa_format_info* pa_stream_get_format_info(pa_stream *s);
//const pa_buffer_attr* pa_stream_get_buffer_attr(pa_stream *s);
//pa_operation *pa_stream_set_buffer_attr(pa_stream *s, const pa_buffer_attr *attr, pa_stream_success_cb_t cb, void *userdata);
typedef pa_operation* (__cdecl *pa_stream_update_sample_rate)(pa_stream *s, uint32_t rate, pa_stream_success_cb_t cb, void *userdata);
//pa_operation *pa_stream_proplist_update(pa_stream *s, pa_update_mode_t mode, pa_proplist *p, pa_stream_success_cb_t cb, void *userdata);
//pa_operation *pa_stream_proplist_remove(pa_stream *s, const char *const keys[], pa_stream_success_cb_t cb, void *userdata);
//int pa_stream_set_monitor_stream(pa_stream *s, uint32_t sink_input_idx);
//uint32_t pa_stream_get_monitor_stream(pa_stream *s);
typedef pa_usec_t (__cdecl *pa_bytes_to_usec)(uint64_t length, const pa_sample_spec *spec);

/** Calculates the number of bytes that are required for the specified
 * time. The return value will always be rounded down for non-integral
 * return values. \since 0.9 */
typedef size_t (__cdecl *pa_usec_to_bytes)(pa_usec_t t, const pa_sample_spec *spec);
//// -- from mainloop.h
//pa_mainloop *pa_mainloop_new(void);
//void pa_mainloop_free(pa_mainloop* m);
//int pa_mainloop_prepare(pa_mainloop *m, int timeout);
//int pa_mainloop_poll(pa_mainloop *m);
//int pa_mainloop_dispatch(pa_mainloop *m);
//int pa_mainloop_get_retval(pa_mainloop *m);
//int pa_mainloop_iterate(pa_mainloop *m, int block, int *retval);
//int pa_mainloop_run(pa_mainloop *m, int *retval);
//pa_mainloop_api* pa_mainloop_get_api(pa_mainloop*m);
//void pa_mainloop_quit(pa_mainloop *m, int r);
//void pa_mainloop_wakeup(pa_mainloop *m);
//void pa_mainloop_set_poll_func(pa_mainloop *m, pa_poll_func poll_func, void *userdata);



/** \cond fulldocs */
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
/** \endcond */

/** A mask of channel positions. \since 0.9.16 */
typedef uint64_t pa_channel_position_mask_t;

/** Makes a bit mask from a channel position. \since 0.9.16 */
#define PA_CHANNEL_POSITION_MASK(f) ((pa_channel_position_mask_t) (1ULL << (f)))

/** A list of channel mapping definitions for pa_channel_map_init_auto() */
typedef enum pa_channel_map_def {
    PA_CHANNEL_MAP_AIFF,
    /**< The mapping from RFC3551, which is based on AIFF-C */

/** \cond fulldocs */
    PA_CHANNEL_MAP_ALSA,
    /**< The default mapping used by ALSA. This mapping is probably
     * not too useful since ALSA's default channel mapping depends on
     * the device string used. */
/** \endcond */

    PA_CHANNEL_MAP_AUX,
    /**< Only aux channels */

    PA_CHANNEL_MAP_WAVEEX,
    /**< Microsoft's WAVEFORMATEXTENSIBLE mapping. This mapping works
     * as if all LSBs of dwChannelMask are set.  */

/** \cond fulldocs */
    PA_CHANNEL_MAP_OSS,
    /**< The default channel mapping used by OSS as defined in the OSS
     * 4.0 API specs. This mapping is probably not too useful since
     * the OSS API has changed in this respect and no longer knows a
     * default channel mapping based on the number of channels. */
/** \endcond */

    /**< Upper limit of valid channel mapping definitions */
    PA_CHANNEL_MAP_DEF_MAX,

    PA_CHANNEL_MAP_DEFAULT = PA_CHANNEL_MAP_AIFF
    /**< The default channel map */
} pa_channel_map_def_t;

/** \cond fulldocs */
#define PA_CHANNEL_MAP_AIFF PA_CHANNEL_MAP_AIFF
#define PA_CHANNEL_MAP_ALSA PA_CHANNEL_MAP_ALSA
#define PA_CHANNEL_MAP_AUX PA_CHANNEL_MAP_AUX
#define PA_CHANNEL_MAP_WAVEEX PA_CHANNEL_MAP_WAVEEX
#define PA_CHANNEL_MAP_OSS PA_CHANNEL_MAP_OSS
#define PA_CHANNEL_MAP_DEF_MAX PA_CHANNEL_MAP_DEF_MAX
#define PA_CHANNEL_MAP_DEFAULT PA_CHANNEL_MAP_DEFAULT
/** \endcond */

/** A channel map which can be used to attach labels to specific
 * channels of a stream. These values are relevant for conversion and
 * mixing of streams */

/** Initialize the specified channel map and return a pointer to
 * it. The channel map will have a defined state but
 * pa_channel_map_valid() will fail for it. */
typedef pa_channel_map* (__cdecl *pa_channel_map_init)(pa_channel_map *m);

/** Initialize the specified channel map for monaural audio and return a pointer to it */
typedef pa_channel_map* (__cdecl *pa_channel_map_init_mono)(pa_channel_map *m);

/** Initialize the specified channel map for stereophonic audio and return a pointer to it */
typedef pa_channel_map* (__cdecl *pa_channel_map_init_stereo)(pa_channel_map *m);

/** Initialize the specified channel map for the specified number of
 * channels using default labels and return a pointer to it. This call
 * will fail (return NULL) if there is no default channel map known for this
 * specific number of channels and mapping. */
typedef pa_channel_map* (__cdecl *pa_channel_map_init_auto)(pa_channel_map *m, unsigned channels, pa_channel_map_def_t def);

