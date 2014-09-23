#pragma once
//------------------------------------------------------------------------------
/**
    @file Core/Trace.h
    @brief Oryol's trace macros
*/

#if defined(__EMSCRIPTEN__) && defined(__EMSCRIPTEN_TRACING__)

#include <emscripten/trace.h>

#define ORYOL_TRACE_CONFIGURE(collector_url, application) \
    emscripten_trace_configure(collector_url, application)
#define ORYOL_TRACE_SET_ENABLED(enabled) \
    emscripten_trace_set_enabled(enabled)
#define ORYOL_TRACE_SET_SESSION_USERNAME(username) \
    emscripten_trace_set_session_username(username)
#define ORYOL_TRACE_RECORD_FRAME_START() \
    emscripten_trace_record_frame_start()
#define ORYOL_TRACE_RECORD_FRAME_END() \
    emscripten_trace_record_frame_end()
#define ORYOL_TRACE_LOG_MESSAGE(channel, message) \
    emscripten_trace_log_message(channel, message)
#define ORYOL_TRACE_REPORT_ERROR(error) \
    emscripten_trace_report_error(error)
#define ORYOL_TRACE_RECORD_ALLOCATION(address, size) \
    emscripten_trace_record_allocation(address, size)
#define ORYOL_TRACE_RECORD_REALLOCATION(old_address, new_address, size) \
    emscripten_trace_record_reallocation(old_address, new_address, size)
#define ORYOL_TRACE_RECORD_FREE(address) \
    emscripten_trace_record_free(address)
#define ORYOL_TRACE_ANNOTATE_ADDRESS_TYPE(address, type) \
    emscripten_trace_annotate_address_type(address, type)
#define ORYOL_TRACE_REPORT_MEMORY_LAYOUT() \
    emscripten_trace_report_memory_layout()
#define ORYOL_TRACE_REPORT_OFF_HEAP_DATA() \
    emscripten_trace_report_off_heap_data()
#define ORYOL_TRACE_ENTER_CONTEXT(name) \
    emscripten_trace_enter_context(name)
#define ORYOL_TRACE_EXIT_CONTEXT() \
    emscripten_trace_exit_context()
#define ORYOL_TRACE_CLOSE() \
    emscripten_trace_close()

namespace Oryol {

class TraceContext {
public:
    TraceContext(const char *context_name) {
      ORYOL_TRACE_ENTER_CONTEXT(context_name);
    };
    ~TraceContext() {
      ORYOL_TRACE_EXIT_CONTEXT();
    };
};

class TraceFrame {
public:
    TraceFrame() {
      ORYOL_TRACE_RECORD_FRAME_START();
    };
    ~TraceFrame() {
      ORYOL_TRACE_RECORD_FRAME_END();
    };
};

} // namespace Oryol

#define ORYOL_TRACE_CONTEXT(name) Oryol::TraceContext trace_context_ ## __LINE__ (name)
#define ORYOL_TRACE_FRAME() Oryol::TraceFrame trace_frame_ ## __LINE__

#else

#define ORYOL_TRACE_CONFIGURE(collector_url, application)
#define ORYOL_TRACE_SET_ENABLED(enabled)
#define ORYOL_TRACE_SET_SESSION_USERNAME(username)
#define ORYOL_TRACE_RECORD_FRAME_START()
#define ORYOL_TRACE_RECORD_FRAME_END()
#define ORYOL_TRACE_LOG_MESSAGE(channel, message)
#define ORYOL_TRACE_REPORT_ERROR(error)
#define ORYOL_TRACE_RECORD_ALLOCATION(address, size)
#define ORYOL_TRACE_RECORD_REALLOCATION(old_address, new_address, size)
#define ORYOL_TRACE_RECORD_FREE(address)
#define ORYOL_TRACE_ANNOTATE_ADDRESS_TYPE(address, type)
#define ORYOL_TRACE_REPORT_MEMORY_LAYOUT()
#define ORYOL_TRACE_REPORT_OFF_HEAP_DATA()
#define ORYOL_TRACE_ENTER_CONTEXT(name)
#define ORYOL_TRACE_EXIT_CONTEXT()
#define ORYOL_TRACE_CLOSE()

#define ORYOL_TRACE_CONTEXT(name)
#define ORYOL_TRACE_FRAME()

#endif
