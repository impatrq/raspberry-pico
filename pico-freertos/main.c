#include <FreeRTOS.h>
#include <task.h>
#include <stdio.h>
#include "pico/stdlib.h"

/* Generic Task prototype */
void genericTask(void *params) {

    /* Constants, local variables and initializations */

    /* Inifite task loop */
    while(1) {
        /* Whatever the task has to do */
    }
}

int main() {
    /* Initialize Pico stdio functions */
    stdio_init_all();

    /* Create a new task to run */
    xTaskCreate(
        genericTask,        /* Task to call */
        "Generic Task",     /* Name of the task */
        256,                /* Stack size (in words) */
        NULL,               /* Task parameters */
        1,                  /* Task priority */
        NULL                /* Task handler */
    );

    /* Start FreeRTOS Scheduler */
    vTaskStartScheduler();

    /* Infinite loop, won't get here because of Scheduler */
    while(1);
}