/**
Libre Wireless Technologies
 **/

#ifndef _OS_PORT_CONFIG_H
#define _OS_PORT_CONFIG_H

//Select underlying RTOS
#if defined(_WIN32)
#define strlwr _strlwr
#define strcasecmp _stricmp
#define strncasecmp _strnicmp
#define snprintf _snprintf
#define strtok_r(str, delim, p) strtok(str, delim)
#else
#define USE_FREERTOS
#endif

#endif
