#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"

/* LED task that toggles pin every 500 ms */
void led_task(void *params) {

    /* Assign LED GPIO to toggle (GPIO25) */
    const uint LED_PIN = PICO_DEFAULT_LED_PIN;
    /* Get the number of ticks to do a 500 ms delay */
    const uint DELAY = pdMS_TO_TICKS(500);
    
    /* Init LED GPIO */
    gpio_init(LED_PIN);
    /* Set GPIO to OUTPUT */
    gpio_set_dir(LED_PIN, GPIO_OUT);

    /* Inifite task loop */
    while(1) {
        /* Get GPIO state */
        bool state = gpio_get(LED_PIN);
        /* Negate state and set GPIO to that value */
        gpio_put(LED_PIN, !state);
        /* Block task for specified delay time */
        vTaskDelay(DELAY);
    }
}

int main() {
    /* Initialize Pico stdio functions */
    stdio_init_all();

    /* Create a new task to run */
    xTaskCreate(
        led_task,       /* Task to call */
        "LED Task",     /* Name of the task */
        256,            /* Stack size (in words) */
        NULL,           /* Task parameters */
        1,              /* Task priority */
        NULL            /* Task handler */
    );

    /* Start FreeRTOS Scheduler */
    vTaskStartScheduler();

    /* Infinite loop, won't get here because of Scheduler */
    while(1);
}