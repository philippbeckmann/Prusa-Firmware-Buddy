// http_client.h
// author: Migi

#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include "lwip/tcp.h"
#include "wui_err.h"
#include "wui_helper_funcs.h"

#include <stdbool.h>

#define MAX_STATUS_MSG_SIZE 100 // maximal size of status message handling errors - httpc_cmd_status_str_t
#define MAX_EVENT_NAME_SIZE 20  // maximal size of event name - httpc_con_event_str_t

#ifdef __cplusplus
extern "C" {
#endif

// HTTP client request type
typedef enum {
    REQ_TELEMETRY, // Telemetry request
    REQ_EVENT,
} HTTPC_REQ_TYPE;

typedef enum {
    EVENT_ACCEPTED,
    EVENT_REJECTED,
    EVENT_FINISHED,
    EVENT_STATE_CHANGED,
    EVENT_INFO,
} CONNECT_EVENT_TYPE;

typedef enum {
    TYPE_INVALID,
    TYPE_JSON,
    TYPE_GCODE
} HTTPC_CONTENT_TYPE;

typedef enum {
    CMD_REJT_GEN,
    CMD_REJT_SIZE,        // The response data size is larger than supported
    CMD_REJT_CONT_LEN,    // The response Content-Length doesn't match its real value
    CMD_REJT_CMD_STRUCT,  // error in the command structure
    CMD_REJT_CMD_ID,      // error with Command-Id
    CMD_REJT_CONT_TYPE,   // error with Content-Type
    CMD_REJT_GCODES_LIMI, // number of gcodes in x-gcode request exceeded
    CMD_REJT_NO_SPACE,    // not enough space in osPool for request transfer to WUI
    CMD_INFO_REQ,         // special request - SEND_INFO
    CMD_STATUS_UNKNOWN,
    CMD_ACCEPTED,
} HTTPC_COMMAND_STATUS;

typedef struct {
    const char name[MAX_STATUS_MSG_SIZE];
    HTTPC_COMMAND_STATUS status_code;
} httpc_cmd_status_str_t;

typedef struct {
    const char name[MAX_EVENT_NAME_SIZE];
    CONNECT_EVENT_TYPE event_code;
} httpc_con_event_str_t;

typedef struct {
    uint32_t command_id;
    uint32_t content_lenght;
    HTTPC_CONTENT_TYPE content_type;
    bool valid_request;
} httpc_header_info;

typedef struct {
    HTTPC_REQ_TYPE req_type;
    CONNECT_EVENT_TYPE connect_event_type;
    uint32_t cmd_id;
    HTTPC_COMMAND_STATUS cmd_status;
} httpc_req_t;

/*!*************************************************************************************************
* \brief Sends telemetry periodicaly and other requests evoked from printer
***************************************************************************************************/
void buddy_httpc_handler(void);

/*!*************************************************************************************************
* \brief Inicialization of HTTP client handler
***************************************************************************************************/
void buddy_httpc_handler_init(void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif //HTTP_CLIENT_H