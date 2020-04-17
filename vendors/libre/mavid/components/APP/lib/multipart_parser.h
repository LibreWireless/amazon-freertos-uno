/* Based on node-formidable by Felix Geisendörfer
 * Igor Afonov - afonov@gmail.com - 2012
 * MIT License - http://www.opensource.org/licenses/mit-license.php
 */
#ifndef _multipart_parser_h
#define _multipart_parser_h

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdlib.h>
#include <ctype.h>
#include "jansson.h"

//#define DEBUG_MULTIPART

typedef struct multipart_parser multipart_parser;
typedef struct multipart_parser_settings multipart_parser_settings;
typedef struct multipart_parser_state multipart_parser_state;

typedef int (*multipart_data_cb) (multipart_parser*, char *at, size_t length);
typedef int (*multipart_notify_cb) (multipart_parser*);

struct multipart_parser_settings {
    multipart_data_cb on_header_field;
    multipart_data_cb on_header_value;
    multipart_data_cb on_part_data;

    multipart_notify_cb on_part_data_begin;
    multipart_notify_cb on_headers_complete;
    multipart_notify_cb on_part_data_end;
    multipart_notify_cb on_body_end;
};

multipart_parser* multipart_parser_init
(char *boundary, multipart_parser_settings* settings);

void multipart_parser_free(multipart_parser* p);

size_t multipart_parser_execute(multipart_parser* p, char *buf, size_t len);

void multipart_parser_set_data(multipart_parser* p, void* data);
void * multipart_parser_get_data(multipart_parser* p);
char* extract_json_data(char* msg, int offset, int len);
void check_for_complete_multipart_data(char* msg,
                                       char* boundary, int msgLen,
                                       int* json_offset, int* json_len,
                                       int* octect_offset, int *octect_len);

void parse_directive(char* msg, char* boundary, int msgLen,
                     char **json_begin);


#ifdef NEW_MULTIPART_PARSER
enum
{
    MULTIPART_MSG_TYPE_JSON=0,
    MULTIPART_MSG_TYPE_OCTECT_DATA,
    MULTIPART_MSG_MULTIPART_MSG_END
};

int extract_multipart_body(char* msg, int msgLen,
                           char* boundary,
                           int stream_id, char* rx_buffer,
                           int *extra_recv, int* extra_recv_sizes,
                           char **multipart_msg, json_t ** root,
                           int *msg_start_offset, int *msg_length);
#endif

#define MULTIPART_MAX_RECVS 500

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
