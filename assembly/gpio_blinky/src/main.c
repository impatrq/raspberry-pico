#include "pico/stdlib.h"

// Funciones externas de assembler
extern void init();
extern void blink();

int main(void) {  
    // Llamo al init de assembler
    init();
    // Llamo al blink de assembler
    blink();
}
