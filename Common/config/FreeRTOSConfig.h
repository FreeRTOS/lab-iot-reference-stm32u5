/*
 * Portion Copyright (C) 2021 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 * Portion Copyright (C) 2019 StMicroelectronics, Inc.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "logging.h"

/*-----------------------------------------------------------
* Application specific definitions.
*
* These definitions should be adjusted for your particular hardware and
* application requirements.
*
* These parameters and more are described within the 'configuration' section of the
* FreeRTOS API documentation available on the FreeRTOS.org web site.
*
* See http://www.freertos.org/a00110.html
*----------------------------------------------------------*/


/* Ensure definitions are only used by the compiler, and not by the assembler. */
#if defined( __ICCARM__ ) || defined( __CC_ARM ) || defined( __GNUC__ )
#include <stdint.h>
extern uint32_t SystemCoreClock;
#endif

#ifndef CMSIS_device_header
#define CMSIS_device_header    "stm32u5xx.h"
#endif /* CMSIS_device_header */

#include CMSIS_device_header

/*-------------------- STM32L5 specific defines -------------------*/
#define configENABLE_TRUSTZONE                     0
#define configRUN_FREERTOS_SECURE_ONLY             0
#define configENABLE_FPU                           1
#define configENABLE_MPU                           0

#define configUSE_PREEMPTION                       1
#define configSUPPORT_STATIC_ALLOCATION            1
#define configSUPPORT_DYNAMIC_ALLOCATION           1
#define configUSE_IDLE_HOOK                        0
#define configUSE_TICK_HOOK                        0
#define configCPU_CLOCK_HZ                         ( SystemCoreClock )
#define configTICK_RATE_HZ                         ( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES                       ( 56 )
#define configMINIMAL_STACK_SIZE                   ( ( uint16_t ) 1024 )
#define configTOTAL_HEAP_SIZE                      ( ( size_t ) 300 * 1024 )
#define configMAX_TASK_NAME_LEN                    ( 32 )
#define configUSE_TRACE_FACILITY                   1
#define configUSE_16_BIT_TICKS                     0
#define configUSE_MUTEXES                          1
#define configQUEUE_REGISTRY_SIZE                  8
#define configUSE_RECURSIVE_MUTEXES                1
#define configUSE_COUNTING_SEMAPHORES              1
#define configENABLE_BACKWARD_COMPATIBILITY        0
#define configNUM_THREAD_LOCAL_STORAGE_POINTERS    5
#define configUSE_PORT_OPTIMISED_TASK_SELECTION    0
#define configCHECK_FOR_STACK_OVERFLOW             2
#define configRECORD_STACK_HIGH_ADDRESS            1
#define configMESSAGE_BUFFER_LENGTH_TYPE           size_t


#define configGENERATE_RUN_TIME_STATS              1

/* For lwip errno support */
#define configUSE_NEWLIB_REENTRANT                 1

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES                      0
#define configMAX_CO_ROUTINE_PRIORITIES            ( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS                           1
#define configTIMER_TASK_PRIORITY                  ( 24 )
#define configTIMER_QUEUE_LENGTH                   10
#define configTIMER_TASK_STACK_DEPTH               2048


#define configTASK_NOTIFICATION_ARRAY_ENTRIES      8

/* CMSIS-RTOS V2 flags */
#define configUSE_OS2_THREAD_SUSPEND_RESUME        1
#define configUSE_OS2_THREAD_ENUMERATE             1
#define configUSE_OS2_EVENTFLAGS_FROM_ISR          1
#define configUSE_OS2_THREAD_FLAGS                 1
#define configUSE_OS2_TIMER                        1
#define configUSE_OS2_MUTEX                        1

/* Set the following definitions to 1 to include the API function, or zero
 * to exclude the API function. */
#define INCLUDE_vTaskPrioritySet                   1
#define INCLUDE_uxTaskPriorityGet                  1
#define INCLUDE_vTaskDelete                        1
#define INCLUDE_vTaskCleanUpResources              1
#define INCLUDE_vTaskSuspend                       1
#define INCLUDE_vTaskDelayUntil                    1
#define INCLUDE_xTaskAbortDelay                    1
#define INCLUDE_vTaskDelay                         1
#define INCLUDE_xTaskGetSchedulerState             1
#define INCLUDE_xTaskResumeFromISR                 0
#define INCLUDE_xTaskGetHandle                     1

#define INCLUDE_xTimerPendFunctionCall             1
#define INCLUDE_xQueueGetMutexHolder               1
#define INCLUDE_uxTaskGetStackHighWaterMark        1
#define INCLUDE_xTaskGetCurrentTaskHandle          1
#define INCLUDE_eTaskGetState                      1

/*#define configPRINTF( ... )                  SdkLog( LOG_INFO, __VA_ARGS__ ) */

/*
 * The CMSIS-RTOS V2 FreeRTOS wrapper is dependent on the heap implementation used
 * by the application thus the correct define need to be enabled below
 */
#define USE_FreeRTOS_HEAP_4

/* Cortex-M specific definitions. */
/* __BVIC_PRIO_BITS will be specified when CMSIS is being used. */
#ifdef __NVIC_PRIO_BITS
#define configPRIO_BITS    __NVIC_PRIO_BITS
#else
#define configPRIO_BITS    3
#endif

/* The lowest interrupt priority that can be used in a call to a "set priority"
 * function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         7

/* The highest interrupt priority that can be used by any interrupt service
 * routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
 * INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
 * PRIORITY THAN THIS! (higher priorities are lower numeric values. */
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5

/* Interrupt priorities used by the kernel port layer itself.  These are generic
* to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY                 ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )

/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
 * See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY            ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << ( 8 - configPRIO_BITS ) )

#define configASSERT( x )                     \
    do {                                      \
        if( ( x ) == 0 ) {                    \
            vDyingGasp();                     \
            LogAssert( "Assertion failed." ); \
            vDyingGasp();                     \
            while( 1 ) {                      \
                __NOP();                      \
            }                                 \
        }                                     \
    } while( 0 )


#define configASSERT_CONTINUE( x )                      \
    do {                                                \
        if( ( x ) == 0 ) {                              \
            LogAssert( "Non-fatal assertion failed." ); \
        }                                               \
    } while( 0 )

#include "stack_macros.h"

#define configAPPLICATION_PROVIDES_cOutputBuffer    1
#define configCOMMAND_INT_MAX_OUTPUT_SIZE           128

#include "hw_defs.h"
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()
#define portGET_RUN_TIME_COUNTER_VALUE()    ( timer_get_count( pxHndlTim5 ) )



#endif /* FREERTOS_CONFIG_H */
