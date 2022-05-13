/* Fade an LED between low and high brightness. */

/* Output PWM signals on pin 25 */
#define PICO_DEFAULT_LED_PIN    25

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

int main() {

    gpio_set_function(PICO_DEFAULT_LED_PIN, GPIO_FUNC_PWM);

    uint slice_num = pwm_gpio_to_slice_num(PICO_DEFAULT_LED_PIN);

    /* Default config:
     * - top = 0xffff
     * - clkdiv = 1 
     */
    pwm_config config = pwm_get_default_config();
    /* Set clkdiv to 4 */
    pwm_config_set_clkdiv(&config, 4.f);
    pwm_init(slice_num, &config, true);

    int fade = 0;
    bool going_up = true;

    while(1) {
        
        if (going_up) {
            ++fade;
            if (fade > 255) {
                fade = 255;
                going_up = false;
            }
        } else {
            --fade;
            if (fade < 0) {
                fade = 0;
                going_up = true;
            }
        }
        pwm_set_gpio_level(PICO_DEFAULT_LED_PIN, fade * fade);
        sleep_ms(5);
    }
}