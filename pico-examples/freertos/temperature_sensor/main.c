#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"

/* Struct to send via queue */
typedef struct {
    uint raw;
    float voltage;
    float temperature;
} temperature_sensor_t;

/* Queue Handler */
QueueHandle_t queue;

/* Task that reads the internal temperature sensor every second and updates a queue */
void adc_task(void *params) {

    /* Struct to store data and send it to the queue */
    temperature_sensor_t data;

    /* ADC temperature sensor channel to read is 4 */
    const uint CHANNEL = 4;
    /* Conversion factor to get voltage value */
    const float conversion_factor = 3.3 / (1 << 12);
    /* Get the number of ticks to do a 1000 ms delay */
    const uint DELAY = pdMS_TO_TICKS(1000);

    /* Enable ADC */
    adc_init();
    /* Enable temperature sensor */
    adc_set_temp_sensor_enabled(true);
    /* Select input to be read */
    adc_select_input(CHANNEL);

    /* Task infinite loop */
    while(1) {
        /* Reads the temperature sensor value */
        uint raw = adc_read();
        /* Calculates the voltage level */
        float voltage = raw * conversion_factor;
        /* Get the actual core temperature */
        float temp = 27 - (voltage - 0.706) / 0.001721;

        /* Set data to the struct */
        data.raw = raw;
        data.voltage = voltage;
        data.temperature = temp;

        /* Send data to queue */
        xQueueSendToBack(queue, &data, portMAX_DELAY);

        /* Block task for specified delay time */
        vTaskDelay(DELAY);
    }
}

/* Task that waits for data in the queue to be available and prints it */
void print_task(void *params) {

    /* Struct to store data from the queue */
    temperature_sensor_t data;

    /* Task inifite loop */
    while(1) {
        /* Gets the data from the queue */
        xQueueReceive(queue, &data, portMAX_DELAY);
        /* Prints the data to the terminal */
        printf(
            "Raw: 0x%03x, Voltage: %.2f, Temperature: %.2f\n", 
            data.raw, 
            data.voltage, 
            data.temperature
        );
    }
}


int main() {
    /* Initialize Pico stdio functions */
    stdio_init_all();

    /* Create a ADC task to run */
    xTaskCreate(
        adc_task,       /* Task to call */
        "ADC Task",     /* Name of the task */
        256,            /* Stack size (in words) */
        NULL,           /* Task parameters */
        1,              /* Task priority */
        NULL            /* Task handler */
    );

    /* Create print task to run */
    xTaskCreate(
        print_task,     /* Task to call */
        "Print Task",   /* Name of the task */
        256,            /* Stack size (in words) */
        NULL,           /* Task parameters */
        1,              /* Task priority */
        NULL            /* Task handler */
    );

    /* Create a queue to hold one element of temperature_sensor_t */
    queue = xQueueCreate(1, sizeof(temperature_sensor_t));

    /* Start FreeRTOS Scheduler */
    vTaskStartScheduler();

    /* Infinite loop, won't get here because of Scheduler */
    while(1);
}