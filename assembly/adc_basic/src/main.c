#include "pico/stdlib.h"

extern void asm_led_init();
extern void asm_led_off();
extern void asm_led_on();
extern void asm_adc_init();
extern void asm_adc_read();
extern void asm_temperature_compare();
extern void asm_delay();

int main(void)
{  
    asm_adc_init();
    asm_led_init();

    while (true)
    {
        // El resultado queda en el registro r0
        asm_adc_read();

        asm_temperature_compare();

        asm_delay();
    }
}
