#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>

#define configUSE_PREEMPTION                    1

#define configCPU_CLOCK_HZ                      ( 72000000UL )
#define configTICK_RATE_HZ                      ( 1000UL )

#define configMAX_PRIORITIES                     5
#define configMINIMAL_STACK_SIZE                 128
#define configTOTAL_HEAP_SIZE                    ( 8 * 1024 )

#define configMAX_TASK_NAME_LEN                  16

#define INCLUDE_vTaskDelay                      1

#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     0

#define configUSE_16_BIT_TICKS                  0

#define configUSE_MUTEXES                       1
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_COUNTING_SEMAPHORES            1

#define configSUPPORT_DYNAMIC_ALLOCATION        1
#define configSUPPORT_STATIC_ALLOCATION         0

#define configKERNEL_INTERRUPT_PRIORITY         255

/* STM32F103 implements 4 priority bits.
 * 0xB0 = 176 = valid priority value.
 */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    0xB0

#define configSYSTICK_CLOCK_HZ                  ( configCPU_CLOCK_HZ )

#define configASSERT( x )                       \
    if( ( x ) == 0 )                            \
    {                                           \
        taskDISABLE_INTERRUPTS();              \
        for( ;; );                              \
    }

#endif
