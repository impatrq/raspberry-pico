#include "hardware/gpio.h"

// Numero de GPIO para el LED
#define LED_GPIO        25
// Mascara de GPIO de LED para registros
#define LED_GPIO_MASK   (1 << LED_GPIO)

/**
 *  @brief Programa principal  
 */
int main(void) {
    // Seteo el GPIO25 como salida
    sio_hw->gpio_oe_set |= LED_GPIO_MASK;
    // Apago el GPIO25
    sio_hw->gpio_clr |= LED_GPIO_MASK;
    // Configuro para que funcione con el SIO
    iobank0_hw->io[LED_GPIO].ctrl = GPIO_FUNC_SIO;

    while(1) {
        // Conmuto LED
        sio_hw->gpio_togl |= LED_GPIO_MASK;
        // Demora
        for(uint32_t i = 0; i < 10000000; i++);
    }

    return 0;
}