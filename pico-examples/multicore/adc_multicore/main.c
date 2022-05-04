#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/multicore.h"

void core1_main() {

    while(1) {
        
        uint16_t raw = adc_read();
        multicore_fifo_push_blocking(raw);
    }
}

int main() {
    stdio_init_all();
    printf("ADC multicore!\r\n");

    adc_init();
    adc_set_temp_sensor_enabled(true);
    adc_select_input(4);

    multicore_launch_core1(core1_main);

    while(1) {

        if(multicore_fifo_rvalid()) {
            uint32_t raw = multicore_fifo_pop_blocking();
            printf("Raw value: 0x%3x\r\n");
        }
    }
}