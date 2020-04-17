/**
Libre Wireless Technologies
 **/

#ifndef _OS_PORT_H
#define _OS_PORT_H

//Dependencies
#include "os_port_config.h"
#include "compiler_port.h"

//Compilation flags used to enable/disable features
#define ENABLED  1
#define DISABLED 0

#define PTR_OFFSET(addr, offset) ((void *) ((uint8_t *) (addr) + (offset)))

#define timeCompare(t1, t2) ((int32_t) ((t1) - (t2)))

//Miscellaneous macros
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef LSB
#define LSB(x) ((x) & 0xFF)
#endif

#ifndef MSB
#define MSB(x) (((x) >> 8) & 0xFF)
#endif

#ifndef MIN
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef arraysize
#define arraysize(a) (sizeof(a) / sizeof(a[0]))
#endif

//Infinite delay
#define INFINITE_DELAY ((uint_t) -1)
//Maximum delay
#define MAX_DELAY (INFINITE_DELAY / 2)

//Invalid handle value
#define OS_INVALID_HANDLE NULL

//No RTOS?
#if defined(USE_NO_RTOS)
#include "os_port_none.h"
//ChibiOS/RT port?
#elif defined(USE_CHIBIOS)
#include "os_port_chibios.h"
//CMSIS-RTOS port?
#elif defined(USE_CMSIS_RTOS)
#include "os_port_cmsis_rtos.h"
//CMSIS-RTOS2 port?
#elif defined(USE_CMSIS_RTOS2)
#include "os_port_cmsis_rtos2.h"
//FreeRTOS port?
#elif defined(USE_FREERTOS)
#include "os_port_freertos.h" 
//Keil RTX port?
#elif defined(USE_RTX)
#include "os_port_rtx.h"
//Micrium uC/OS-II port?
#elif defined(USE_UCOS2)
#include "os_port_ucos2.h"
//Micrium uC/OS-III port?
#elif defined(USE_UCOS3)
#include "os_port_ucos3.h"
//Nut/OS port?
#elif defined(USE_NUTOS)
#include "os_port_nutos.h"
//Segger embOS port?
#elif defined(USE_EMBOS)
#include "os_port_embos.h"
//TI SYS/BIOS port?
#elif defined(USE_SYS_BIOS)
#include "os_port_sys_bios.h"
//Windows port?
#elif defined(_WIN32)
#include "os_port_windows.h"
#endif

//Delay routines
#if !defined(usleep) && !defined(__GNUC__)
#define usleep(delay) {volatile uint32_t n = delay * 4; while(n > 0) n--;}
#endif

#if !defined(sleep) && !defined(__GNUC__)
#define sleep(delay) {volatile uint32_t n = delay * 4000; while(n > 0) n--;}
#endif

#endif
