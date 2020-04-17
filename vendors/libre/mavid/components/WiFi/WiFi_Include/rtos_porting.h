
#include "stdint.h"

//**HT
//#include <semaphore.h>
//#include <pthread.h>
//#include <time.h>

#include <FreeRTOS.h>

#include <timers.h>
#include <queue.h>
#include <task.h>

#ifndef INCLUDED_RTOS_PORTING_H_
#define INCLUDED_RTOS_PORTING_H_

#ifdef __cplusplus
extern "C"
{
#endif

#if 1
  
typedef   QueueHandle_t sem_t          ;
//typedef   TaskHandle_t pthread_t       ;

//typedef void*	xQueueHandle            ;
typedef void*	xEventHandle            ;

typedef void * pthread_mutex_t        ;
#if defined(__ICCARM__)
typedef TimerHandle_t timer_t          ;
#endif
#else  
  
typedef sem_t                  SemaphoreHandle  ;
typedef TaskHandle_t		xTaskHandle;
typedef void*			xQueueHandle;
typedef void*			xEventHandle;
typedef pthread_mutex_t	xMutexHandle;
typedef timer_t		xTimerHandle;

#endif

#define RTOS_LOWEST_PRIORITY 		0
#define RTOS_HIGHEST_PRIORITY 		255
#define RTOS_DEFAULT_THREAD_PRIORITY	192

#define RTOS_USE_DYNAMIC_THREAD_STACK
//#define RTOS_USE_STATIC_THREAD_STACK

typedef struct
{
	uint32_t pfnTaskEntry;
	uint16_t uwStackSize;
	char	 *pcName;
	uint8_t  usTaskPrio;
	uint16_t uwResved;

} TSK_INIT_PARAM_S;

#define TSK_ENTRY_FUNC          uint32_t

#define OS_TSK_DETACHED	        0
#define LOS_OK			0

// task ++
#define MHD_TASK_PRIO_NORMAL         10
#define MHD_TASK_DEF_STACK_SZ        OS_TSK_DEFAULT_STACK_SIZE

#define MHD_THREAD_TASK_NAME         "mhdTask"
#define MHD_SCAN_TASK_NAME           "mhdScan"
#define MHD_EASYSETUP_TASK_NAME      "mhdEasysetup"
#define MHD_STA_CONNECT_TASK_NAME    "mhdStaConnect"
#define MHD_IPERF_TASK_NAME          "mhdIperf"
#define MHD_IPERFS_TASK_NAME         "mhdIperfs"
#define MHD_WORKER_TASK_NAME         "mhdWorkerQ"

extern uint32_t mhd_thread_task_id;
extern uint32_t mhd_scan_task_id;
extern uint32_t mhd_easysetup_task_id;
extern uint32_t mhd_iperf_task_id;
extern uint32_t mhd_iperfs_task_id;


#define OS_NULL_ARG_BASE    1


#ifdef __cplusplus
}
#endif

#endif
