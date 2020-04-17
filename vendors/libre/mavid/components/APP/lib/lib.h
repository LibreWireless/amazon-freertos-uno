
#ifndef __LIB_H_

#define __LIB_H_


#include "debug.h"

#define BOUNDARY_STR "libre-mavid-boundary"

#define BOUNDARY_STR_MAX_LEN 100

#define LOOPBACK_IP_ADDR "127.0.0.1"   // loopback ip



extern int linkStatus;

void dieee(char *msg);

char *strcopy(const char *s, size_t len);

void print_hdr(char* description,
               unsigned char *name, size_t namelen,
               unsigned char *value, size_t valuelen,
               int stream_id);

void print_ch_arr(char *buf,int n);

void extract_boundary_from_avs_reply(char *msg, char *boundary,
                                     int max_boundary_len);

void fatal(char *msg);

void hexDump (char *desc, void *addr, int len);

void *safe_malloc(int len, int assert_on_fail);

void show_thread_priorities();

int is_sock_data_available_for_read(int sd, int secs, int usecs, int enable_prints);

int is_non_blocking_sock(int fd);
char * stristr (const char *haystack, size_t haylen, const char *needle);
int  create_loopbacksocket_pair(int listport, int socket[]);

#endif /* __LIB_H_ */
