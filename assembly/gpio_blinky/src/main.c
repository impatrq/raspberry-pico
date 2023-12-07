#include "pico/stdlib.h"

// Funciones externas de assembler
extern void asm_led_init();
extern void asm_led_blink();
extern void asm_delay();

int main(void) {  
    // Llamo al init de assembler
    asm_led_init();

    while(true) {
        // Llamo al blink de assembler
        asm_led_blink();
        // Llamo al delay de assembler 500 ms
        asm_delay();
    }
}
