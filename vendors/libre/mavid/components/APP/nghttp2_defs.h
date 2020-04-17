

#ifndef _NGHTTP2_defs_H
#define _NGHTTP2_defs_H

//Dependencies
#include <nghttp2.h>

#define MAKE_NV(NAME, VALUE)                                                   \
  {                                                                            \
    (uint8_t *)NAME, (uint8_t *)VALUE, sizeof(NAME) - 1, sizeof(VALUE) - 1,    \
        NGHTTP2_NV_FLAG_NONE                                                   \
  }

#define MAKE_NV_CS(NAME, VALUE)                                                \
  {                                                                            \
    (uint8_t *)NAME, (uint8_t *)VALUE, sizeof(NAME) - 1, strlen(VALUE),        \
        NGHTTP2_NV_FLAG_NONE                                                   \
  }

struct Connection {
    nghttp2_session *session;
    /* WANT_READ if SSL/TLS connection needs more input; or WANT_WRITE
       if it needs more output; or IO_NONE. This is necessary because
       SSL/TLS re-negotiation is possible at any time. nghttp2 API
       offers similar functions like nghttp2_session_want_read() and
       nghttp2_session_want_write() but they do not take into account
       SSL/TSL connection. */
    //int want_io;
};

extern struct Connection avsHttp2Conn;

struct URI {
    const char *host;
    /* In this program, path contains query component as well. */
    const char *path;
    size_t pathlen;
    const char *hostport;
    size_t hostlen;
    size_t hostportlen;
    uint16_t port;
};


struct Request {
    char *host;
    /* In this program, path contains query component as well. */
    char *path;
    /* This is the concatenation of host and port with ":" in
       between. */
    char *hostport;
    /* Stream ID for this request. */
    int32_t stream_id;
    uint16_t port;
};



#endif
