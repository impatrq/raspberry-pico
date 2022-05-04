#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/adc.h"

const float conversion_factor = 3.3f / (1 << 12);

typedef struct sensor {
    uint16_t raw;
    float voltage;
    float temperature;
} sensor_data_t;

sensor_data_t data;

void core1_main() {

    while(1) {
        
        uint16_t raw = adc_read();
        float voltage = raw * conversion_factor;
        float temperature = 27 - (voltage - 0.706) / 0.001721;

        data.raw = raw;
        data.voltage = voltage;
        data.temperature = temperature;

        multicore_fifo_push_blocking(true);
        sleep_ms(500);
    }
}

int main() {
    stdio_init_all();
    sleep_ms(1000);
    printf("ADC multicore!\r\n");

    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    multicore_launch_core1(core1_main);

    while(1) {

        if(multicore_fifo_pop_blocking()) {
            

            printf("Raw value: 0x%03x\r\n", data.raw);
            printf("Voltage value: %.2f\r\n", data.voltage);
            printf("Temperature vlaue: %.2f\r\n\n", data.temperature);
        }
    }
}