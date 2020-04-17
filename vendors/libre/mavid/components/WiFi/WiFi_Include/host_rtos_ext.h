#pragma once

#include "host_rtos_common.h"
#include "host_result.h"
//#include "platform/mhd_platform_interface.h"
#include "mhd_platform_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************
 * @cond            Enumerations
 ******************************************************/
 
/******************************************************
 *             Structures
 ******************************************************/

typedef mhd_thread_arg_t host_thread_arg_t;

//typedef void (*host_thread_function_t)( uint32_t arg );
typedef void (*host_thread_function_t)( void );

/******************************************************
 *             Function declarations
 * @endcond
 ******************************************************/

/*****************************************************************************/
/** @addtogroup rtostmr       RTOS timers
 *  @ingroup rtos
 *
 * RTOS timer management functions
 * These timers are based on the RTOS time-slice scheduling, so are not
 * highly accurate. They are also affected by high loading on the processor.
 *
 *
 *  @{
 */
/*****************************************************************************/

/** Initialises a RTOS timer
 *
 * Initialises a RTOS timer
 * Timer does not start running until @ref host_rtos_start_timer is called
 *
 * @param timer    : a pointer to the timer handle to be initialised
 * @param time_ms  : Timer period in milliseconds
 * @param function : the callback handler function that is called each
 *                   time the timer expires
 * @param arg      : an argument that will be passed to the callback
 *                   function
 *
 * @return    HOST_SUCCESS : on success.
 * @return    HOST_ERROR   : if an error occurred
 */
host_result_t host_rtos_init_timer( host_timer_t* timer, uint32_t time_ms, timer_handler_t function, void* arg );


/** Starts a RTOS timer running
 *
 * Starts a RTOS timer running. Timer must have been previously
 * initialised with @ref host_rtos_init_timer
 *
 * @param timer    : a pointer to the timer handle to start
 *
 * @return    HOST_SUCCESS : on success.
 * @return    HOST_ERROR   : if an error occurred
 */
host_result_t host_rtos_start_timer( host_timer_t* timer );


/** Stops a running RTOS timer
 *
 * Stops a running RTOS timer. Timer must have been previously
 * started with @ref host_rtos_start_timer
 *
 * @param timer    : a pointer to the timer handle to stop
 *
 * @return    HOST_SUCCESS : on success.
 * @return    HOST_ERROR   : if an error occurred
 */
host_result_t host_rtos_stop_timer( host_timer_t* timer );


/** De-initialise a RTOS timer
 *
 * Deletes a RTOS timer created with @ref host_rtos_init_timer
 *
 * @param timer : a pointer to the RTOS timer handle
 *
 * @return    HOST_SUCCESS : on success.
 * @return    HOST_ERROR   : if an error occurred
 */
host_result_t host_rtos_deinit_timer( host_timer_t* timer );


/** Check if an RTOS timer is running
 *
 * @param timer : a pointer to the RTOS timer handle
 *
 * @return    HOST_SUCCESS : if running.
 * @return    HOST_ERROR   : if not running
 */
host_result_t host_rtos_is_timer_running( host_timer_t* timer );

/** @} */

/*****************************************************************************/
/** @addtogroup events       Events
 *  @ingroup rtos
 *
 * Event management functions
 *
 *
 *  @{
 */
/*****************************************************************************/

/** Requests a function be called at a regular interval
 *
 * This function registers a function that will be called at a regular
 * interval. Since this is based on the RTOS time-slice scheduling, the
 * accuracy is not high, and is affected by processor load.
 *
 * @param event_object  : pointer to a event handle which will be initialised
 * @param worker_thread : pointer to the worker thread in whose context the
 *                        callback function runs on
 * @param function      : the callback function that is to be called regularly
 * @param time_ms       : the time period between function calls in milliseconds
 * @param arg           : an argument that will be supplied to the function when
 *                        it is called
 *
 * @return    HOST_SUCCESS : on success.
 * @return    HOST_ERROR   : if an error occurred
 */
host_result_t host_rtos_register_timed_event( host_timed_event_t* event_object, host_worker_thread_t* worker_thread, event_handler_t function, uint32_t time_ms, void* arg );


/** Removes a request for a regular function execution
 *
 * This function de-registers a function that has previously been set-up
 * with @ref host_rtos_register_timed_event.
 *
 * @param event_object : the event handle used with @ref host_rtos_register_timed_event
 *
 * @return    HOST_SUCCESS : on success.
 * @return    HOST_ERROR   : if an error occurred
 */
host_result_t host_rtos_deregister_timed_event( host_timed_event_t* event_object );


/** Sends an asynchronous event to the associated worker thread
 *
 * Sends an asynchronous event to the associated worker thread
 *
 * @param worker_thread :the worker thread in which context the callback should execute from
 * @param function      : the callback function to be called from the worker thread
 * @param arg           : the argument to be passed to the callback function
 *
 * @return    HOST_SUCCESS : on success.
 * @return    HOST_ERROR   : if an error occurred
 */
host_result_t host_rtos_send_asynchronous_event( host_worker_thread_t* worker_thread, event_handler_t function, void* arg );

/** @} */
/*****************************************************************************/
/** @addtogroup worker       Worker Threads
 *  @ingroup rtos
 *
 * Worker thread management functions
 *
 *
 *  @{
 */
/*****************************************************************************/

/** Creates a worker thread
 *
 * Creates a worker thread
 * A worker thread is a thread in whose context timed and asynchronous events
 * execute.
 *
 * @param worker_thread    : a pointer to the worker thread to be created
 * @param priority         : thread priority
 * @param stack_size       : thread's stack size in number of bytes
 * @param event_queue_size : number of events can be pushed into the queue
 *
 * @return    WICED_SUCCESS : on success.
 * @return    WICED_ERROR   : if an error occurred
 */
host_result_t host_rtos_create_worker_thread( host_worker_thread_t* worker_thread, uint8_t priority, uint32_t stack_size, uint32_t event_queue_size );


/** Deletes a worker thread
 *
 * Deletes a worker thread
 *
 * @param worker_thread : a pointer to the worker thread to be created
 *
 * @return    WICED_SUCCESS : on success.
 * @return    WICED_ERROR   : if an error occurred
 */
host_result_t host_rtos_delete_worker_thread( host_worker_thread_t* worker_thread );


/** @} */

#ifdef __cplusplus
} /*extern "C" */
#endif
