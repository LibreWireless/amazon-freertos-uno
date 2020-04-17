
#include "debug.h"
#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "lib.h"
#include "lwip/sockets.h"
#include "stm32f7xx.h"
#include "stm32f7xx_hal.h"

/**
 * @brief Display the contents of an array
 * @param[in] stream Pointer to a FILE object that identifies an output stream
 * @param[in] prepend String to prepend to the left of each line
 * @param[in] data Pointer to the data array
 * @param[in] length Number of bytes to display
 **/

#if 0
void debugDisplayArray(FILE *stream,
                       const char_t *prepend, const void *data, size_t length)
{
    uint_t i;

    for(i = 0; i < length; i++)
    {
        //Beginning of a new line?
        if((i % 16) == 0)
            fprintf(stream, "%s", prepend);
        //Display current data byte
        fprintf(stream, "%02" PRIX8 " ", *((uint8_t *) data + i));
        //End of current line?
        if((i % 16) == 15 || i == (length - 1))
            fprintf(stream, "\r\n");
    }
}
#endif


int assert_happened=0;
int get_assert_state()
{
    return assert_happened;
}

void fatal(char *msg)
{
    printf("\n\n^^^FATAL:  %s.. exiting...^^^\n",msg);
#ifndef __GNUC__
    //show_mem_usage_free_info("fatal");
#endif
    assert_happened=1;
    /* LED indication is useless without logs.
       Hence removing LED indication */
	//SetLedFeature(DEVICE_STATE_FATAL_ERROR);
    NVIC_SystemReset();
    while(1);
}


void *safe_malloc(int len, int assert_on_fail)
{
    void* ptr;
    ptr=malloc(len);
    if(ptr==NULL)
    {
        if(assert_on_fail==1)
        {
            printf("safe_malloc of %d bytes failed...",len);
            fatal("safe_malloc failed... ");
        }
        else
        {
            printf("XXX: safe_malloc failed... still continuing...-----------------------\n\n");
        }
    }
    return ptr;
}

/*
 * Returns copy of string |s| with the length |len|. The returned
 * string is NULL-terminated.
 */
char *strcopy(const char *s, size_t len) {
    char *dst;
    dst = safe_malloc((len + 1),1);
    memcpy(dst, s, len);
    dst[len] = '\0';
    return dst;
}

char *
stristr (const char *haystack,size_t haylen, const char *needle)
{
   char *pptr  = (char *) needle;   /* Pattern to search for    */
   char *start = (char *) haystack; /* Start with a bowl of hay */
   char *sptr;                      /* Substring pointer        */
   int   slen  = haylen;            /* Total size of haystack   */
   int   plen  = strlen (needle);   /* Length of our needle     */

   /* while string length not shorter than pattern length */
   for (; slen >= plen; start++, slen--)
   {
      /* find start of pattern in string */
      while (toupper (*start) != toupper (*needle))
      {
         start++;
         slen--;
         /* if pattern longer than string */
         if (slen < plen)
         {
            return NULL;
         }
      }

      sptr = start;
      pptr = (char *) needle;
      while (toupper (*sptr) == toupper (*pptr))
      {
         sptr++;
         pptr++;
         /* if end of pattern then pattern was found */
         if ('\0' == *pptr)
         {
            return start;
         }
      }
   }

   return NULL;
}

void print_ch_arr(char *buf,int n)
{
    int i;
    for(i=0; i<n; i++)
        printf("%c",buf[i]);
}

void print_hdr(char* description,
               unsigned char *name, size_t namelen,
               unsigned char *value, size_t valuelen,
               int stream_id)
{
    printf("%s:STREAM=%d. name={%.*s}, value={%.*s}",
            (description)?description:"-",stream_id,namelen,name,valuelen,value);
#if 0
    print_ch_arr((char*)name, namelen);
    printf("-:-");
    print_ch_arr((char*)value, valuelen);
    printf("-");
#endif
}

#ifndef IFLYOS_ENABLED
#define BOUNDARY_DEF_STR  "boundary="
#else
#define BOUNDARY_DEF_STR  "\""
#endif
void extract_boundary_from_avs_reply(char *msg, char *boundary, int max_boundary_len)
{
    char *ptr=NULL, *ptr1=NULL;
    int len;
    ptr=strstr(msg, BOUNDARY_DEF_STR);
    if(ptr==NULL)
    {
        fatal("no boundary def found..");
    }
    ptr+=strlen(BOUNDARY_DEF_STR);
#ifndef IFLYOS_ENABLED
    ptr1=strstr(ptr,";");
#else
      ptr1=strstr(ptr,BOUNDARY_DEF_STR);
#endif
    if(ptr1==NULL)
    {
        fatal("no boundary termination def found..");
    }

    len=ptr1-ptr;
    if((len+2) > max_boundary_len)
    {
        fatal("extract_boundary_from_avs_reply: boundary len too much");
    }
    boundary[0]='-';
    boundary[1]='-';

    memcpy(&boundary[2], ptr, len);
    boundary[len+2]='\0';
}


void hexDump (char *desc, void *addr, int len) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    // Output description if given.
    if (desc != NULL)
        printf ("%s:\n", desc);

    if (len == 0) {
        printf("  ZERO LENGTH\n");
        return;
    }
    if (len < 0) {
        printf("  NEGATIVE LENGTH: %i\n",len);
        return;
    }

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf ("  %s\n", buff);

            // Output the offset.
            printf ("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf (" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e))
            buff[i % 16] = '.';
        else
            buff[i % 16] = pc[i];
        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf ("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf ("  %s\n", buff);
}


#ifdef NETWORK_FAILURE_RECOVERY
int is_sock_data_available_for_read(int sd, int secs, int usecs, int enable_prints)
{
  // Descriptor set
  fd_set fd;
  
  int ret,len;
  int numfds=sd;
  struct timeval tv;
  
  FD_ZERO(&fd);
  FD_SET(sd, &fd);
  
  
  tv.tv_sec = secs;
  tv.tv_usec = usecs;
  
  // waiting for events
  ret = select(numfds+1, &fd, NULL, NULL, &tv);
  
  if (ret < 0) {
    printf("select failed\n");
    ret = -1;
  }
  else if (ret > 0)
  {
    if (FD_ISSET(sd, &fd))
      ret = 1;
    else
      ret = 0;
  }
  return ret;
}


int is_non_blocking_sock(int fd)
{
    int retval = fcntl(fd, F_GETFL, 0);
    if(O_NONBLOCK&retval)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int  create_loopbacksocket_pair(int listport, int socket[])
{
  int socket_fd;
  struct sockaddr_in ra;  
  /* Creates an UDP socket (SOCK_DGRAM) with Internet Protocol Family (PF_INET).
  * Protocol family and Address family related. For example PF_INET Protocol Family and AF_INET family are coupled.
  */
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  
  if ( socket_fd < 0 )
  {
    fatal("loopback1 socket() failed");
  }
  memset(&ra, 0, sizeof(struct sockaddr_in));
  ra.sin_family = AF_INET;
  ra.sin_addr.s_addr = inet_addr(LOOPBACK_IP_ADDR);
  ra.sin_port = htons(listport);
  /* Bind the UDP socket to the port RECEIVER_PORT_NUM and to the current
  * machines IP address (Its defined by RECEIVER_PORT_NUM).
  * Once bind is successful for UDP sockets application can operate
  * on the socket descriptor for sending or receiving data.
  */
  if (bind(socket_fd, (struct sockaddr *)&ra, sizeof(struct sockaddr_in)) == -1)
  {
    close(socket_fd);
    fatal("stream_listner sock Bind");
  }
  socket[0] = socket_fd;
  socket_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if ( socket_fd < 0 )
  {
    fatal("loopback2 socket() failed");
  }
  socket[1] = socket_fd;
  return 0;
}



#ifdef NET_CHECK_WITH_PING
int network_down_check_with_ping(int *fail_times_ptr, int *ping_fails_ptr,
        char *srvr_addr, char *fail_type)
{
    int ping_result;
    int fail=0;
    int fail_times=*fail_times_ptr;
    int ping_fails=*ping_fails_ptr;

    if(fail_times > 5)
    {
        ping_result=ping_remotehost(srvr_addr,1,0,0);
        if(ping_result!=ERR_OK)
        {
            ping_fails++;
        }
        else
        {
            ping_fails=0;
        }
        *ping_fails_ptr=ping_fails;

        if(NULL == fail_type)
        {
            fatal("give details.");
        }
        else
        {
            printf("\n%s=%d, Ping_status=%s, continuous ping fail time=%d",
                    fail_type,fail_times, ping_status_get(ping_result),ping_fails);
        }

        if(ping_fails > 5)
        {
            // continuous 10 fails(ping started at 5th fail),
            // and continuous 5 ping fails
            fail = 1;
            printf("\n[%s]: net_and_ping_down. returning Fail.. caller=%s",__FUNCTION__,fail_type);
        }
    }
    else
    {
        printf("\n%s=%d",fail_type,fail_times);
    }

    if(fail_times > 30)
    {
        // continuous 30 fails, but ping happening..
        fail = 1;
        printf("\n[%s]: net_down_ping_up. returning Fail.. caller=%s",__FUNCTION__,fail_type);
    }

    return fail;
}
#endif /* NET_CHECK_WITH_PING */

#endif /* NETWORK_FAILURE_RECOVERY */


#if 0
void show_thread_priorities()
{
    char* task_info;
    task_info=(char*)safe_malloc(2500,1);
    osThreadList(task_info);
    free(task_info);
    TRACE_INFO("\n---task_list---\n%s----task_list----\n",task_info);
}
#else
void show_thread_priorities()
{
}
#endif

