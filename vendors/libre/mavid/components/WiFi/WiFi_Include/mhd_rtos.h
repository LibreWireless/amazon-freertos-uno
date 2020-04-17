/*
 * Copyright 2014, Broadcom Corporation
 * All Rights Reserved.
 *
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Broadcom Corporation;
 * the contents of this file may not be disclosed to third parties, copied
 * or duplicated in any form, in whole or in part, without the prior
 * written permission of Broadcom Corporation.
 */

/** @file
 *  Definitions for the ThreadX implementation of the Host RTOS
 *  abstraction layer.
 *
 */

#ifndef INCLUDED_MHD_RTOS_H_
#define INCLUDED_MHD_RTOS_H_

#include "cmsis_os.h"   
#include "rtos_porting.h"

#ifdef __cplusplus
extern "C"
{
#endif

void mhd_thread_func( uint32_t /*@unused@*/thread_input ) /*@globals killed mhd_transceive_semaphore@*/ /*@modifies mhd_wlan_status, mhd_bus_interrupt, mhd_thread_quit_flag@*/;
  
  
  
#define RTOS_HIGHER_PRIORTIY_THAN(x)     ((x) < RTOS_HIGHEST_PRIORITY ? (x)-1 : RTOS_HIGHEST_PRIORITY)
#define RTOS_LOWER_PRIORTIY_THAN(x)      ((x) > RTOS_LOWEST_PRIORITY  ? (x)+1 : RTOS_LOWEST_PRIORITY )

#ifdef MHD_DEBUG
#define MHD_THREAD_STACK_SIZE        (632)   /* Stack checking requires a larger stack */
#else /* ifdef MHD_DEBUG */
#define MHD_THREAD_STACK_SIZE        (4096)//(544) 
#endif /* ifdef MHD_DEBUG */

/*
 * The number of system ticks per second
 */
#define SYSTICK_FREQUENCY  (1000)

/******************************************************
 *             Structures
 ******************************************************/

#if 1

typedef osSemaphoreId host_semaphore_type_t; /** OS definition of a semaphore */
typedef xTaskHandle host_thread_type_t;    /** OS definition of a thread handle */
typedef xQueueHandle host_queue_type_t;     /** OS definition of a message queue */
typedef xEventHandle host_event_type_t;    /** OS definition of an event */

typedef pthread_mutex_t host_mutex_type_t;    /** OS definition of a mutex */
  
#else  

typedef xSemaphoreHandle host_semaphore_type_t; /** OS definition of a semaphore */
typedef xTaskHandle host_thread_type_t;    /** OS definition of a thread handle */
typedef xQueueHandle host_queue_type_t;     /** OS definition of a message queue */
typedef xEventHandle host_event_type_t;    /** OS definition of an event */
typedef xMutexHandle host_mutex_type_t;    /** OS definition of a mutex */

#endif


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* ifndef INCLUDED_MHD_RTOS_H_ */
