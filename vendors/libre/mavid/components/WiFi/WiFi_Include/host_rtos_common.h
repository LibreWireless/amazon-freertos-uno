/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */
#pragma once

#include "host_result.h"
#include "rtos_porting.h"
#include "mhd_rtos.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 *                      Macros
 ******************************************************/

#define HOST_HARDWARE_IO_WORKER_THREAD             ((host_worker_thread_t*)&host_hardware_io_worker_thread)
#define HOST_NETWORKING_WORKER_THREAD              ((host_worker_thread_t*)&host_networking_worker_thread )
#define LOWER_THAN_PRIORITY_OF( thread )            ((thread).handle.tx_thread_priority - 1)
#define HIGHER_THAN_PRIORITY_OF( thread )           ((thread).handle.tx_thread_priority + 1)

#define HOST_PRIORITY_TO_NATIVE_PRIORITY(priority) (uint8_t)(RTOS_HIGHEST_PRIORITY - priority)

#define HOST_END_OF_THREAD( thread )               malloc_leak_check(thread, LEAK_CHECK_THREAD); vTaskDelete(thread)
#define HOST_END_OF_CURRENT_THREAD( )              malloc_leak_check(NULL, LEAK_CHECK_THREAD); vTaskDelete(NULL)
#define HOST_END_OF_CURRENT_THREAD_NO_LEAK_CHECK( )   vTaskDelete(NULL)

#define HOST_TO_MALLOC_THREAD( x )                 ((malloc_thread_handle) *(x) )

#define HOST_GET_THREAD_HANDLE( thread )           ( thread )

#define HOST_GET_QUEUE_HANDLE( queue )             ( queue )

/******************************************************
 *                    Constants
 ******************************************************/

/* Configuration of Built-in Worker Threads
 *
 * 1. host_hardware_io_worker_thread is designed to handle deferred execution of quick, non-blocking hardware I/O operations.
 *    - priority         : higher than that of host_networking_worker_thread
 *    - stack size       : small. Consequently, no printf is allowed here.
 *    - event queue size : the events are quick; therefore, large queue isn't required.
 *
 * 2. host_networking_worker_thread is designed to handle deferred execution of networking operations
 *    - priority         : lower to allow host_hardware_io_worker_thread to preempt and run
 *    - stack size       : considerably larger than that of host_hardware_io_worker_thread because of the networking functions.
 *    - event queue size : larger than that of host_hardware_io_worker_thread because networking operation may block
 */

#ifndef HARDWARE_IO_WORKER_THREAD_STACK_SIZE
#define HARDWARE_IO_WORKER_THREAD_STACK_SIZE                                   (512)
#endif
#define HARDWARE_IO_WORKER_THREAD_QUEUE_SIZE                                    (10)
#define HARDWARE_IO_WORKER_THREAD_PRIORITY       (HOST_PRIORITY_TO_NATIVE_PRIORITY(HOST_DEFAULT_LIBRARY_PRIORITY))
#define NETWORKING_WORKER_THREAD_STACK_SIZE                               (7 * 1024)
#define NETWORKING_WORKER_THREAD_QUEUE_SIZE                                     (15)
#define NETWORKING_WORKER_THREAD_PRIORITY        (HOST_PRIORITY_TO_NATIVE_PRIORITY(HOST_NETWORK_WORKER_PRIORITY))


/******************************************************
 *                   Enumerations
 ******************************************************/

/******************************************************
 *                 Type Definitions
 ******************************************************/

/******************************************************
 *                    Structures
 ******************************************************/

typedef xEventHandle  host_event_flags_t;

//typedef xSemaphoreHandle host_semaphore_t;
//typedef xSemaphoreHandle host_mutex_t;

typedef void (*timer_handler_t)( void* arg );

typedef struct
{
    xTimerHandle    handle;
    timer_handler_t function;
    void*           arg;
}host_timer_t;

typedef xTaskHandle host_thread_t;

typedef xQueueHandle host_queue_t;

typedef struct
{
    host_thread_t thread;
    host_queue_t  event_queue;
} host_worker_thread_t;

typedef host_result_t (*event_handler_t)( void* arg );

typedef struct
{
    event_handler_t        function;
    void*                  arg;
    host_timer_t          timer;
    host_worker_thread_t* thread;
} host_timed_event_t;

/******************************************************
 *                 Global Variables
 ******************************************************/

/******************************************************
 *               Function Declarations
 ******************************************************/

#ifdef __cplusplus
} /* extern "C" */
#endif
