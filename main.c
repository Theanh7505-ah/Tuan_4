#include <stdint.h>

#include "FreeRTOS.h"
#include "task.h"

/* =========================================================
 * STM32F103 GPIO
 * ========================================================= */

#define RCC_BASE        0x40021000UL
#define RCC_APB2ENR     (*(volatile uint32_t *)(RCC_BASE + 0x18UL))

#define GPIOA_BASE      0x40010800UL
#define GPIOA_CRL       (*(volatile uint32_t *)(GPIOA_BASE + 0x00UL))
#define GPIOA_ODR       (*(volatile uint32_t *)(GPIOA_BASE + 0x0CUL))


/* =========================================================
 * LED functions
 * ========================================================= */

static void GPIO_Init(void)
{
    /* Enable clock GPIOA */
    RCC_APB2ENR |= (1UL << 2);

    /*
     * PA0, PA1, PA2:
     * Output push-pull
     * Maximum speed 2 MHz
     *
     * CNF = 00
     * MODE = 10
     *
     * Configuration value = 0b0010 = 0x2
     */

    GPIOA_CRL &= ~0x00000FFFUL;
    GPIOA_CRL |=  0x00000222UL;

    /* Turn LEDs off initially */
    GPIOA_ODR &= ~((1UL << 0) |
                   (1UL << 1) |
                   (1UL << 2));
}


/* =========================================================
 * Task 1 - 0.1 Hz
 * PA0
 * ========================================================= */

static void Task_LED_01Hz(void *argument)
{
    (void)argument;

    while (1)
    {
        GPIOA_ODR ^= (1UL << 0);

        /*
         * 0.1 Hz
         * Period = 10 seconds
         * Toggle every 5 seconds
         */
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}


/* =========================================================
 * Task 2 - 1 Hz
 * PA1
 * ========================================================= */

static void Task_LED_1Hz(void *argument)
{
    (void)argument;

    while (1)
    {
        GPIOA_ODR ^= (1UL << 1);

        /*
         * 1 Hz
         * Period = 1 second
         * Toggle every 500 ms
         */
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}


/* =========================================================
 * Task 3 - 10 Hz
 * PA2
 * ========================================================= */

static void Task_LED_10Hz(void *argument)
{
    (void)argument;

    while (1)
    {
        GPIOA_ODR ^= (1UL << 2);

        /*
         * 10 Hz
         * Period = 100 ms
         * Toggle every 50 ms
         */
        vTaskDelay(pdMS_TO_TICKS(50));
    }
}


/* =========================================================
 * main
 * ========================================================= */

int main(void)
{
    GPIO_Init();

    xTaskCreate(
        Task_LED_01Hz,
        "LED_01Hz",
        128,
        NULL,
        1,
        NULL
    );

    xTaskCreate(
        Task_LED_1Hz,
        "LED_1Hz",
        128,
        NULL,
        1,
        NULL
    );

    xTaskCreate(
        Task_LED_10Hz,
        "LED_10Hz",
        128,
        NULL,
        1,
        NULL
    );

    /*
     * Start FreeRTOS scheduler
     */
    vTaskStartScheduler();

    /*
     * Normally never reaches here.
     */
    while (1)
    {
    }
}
