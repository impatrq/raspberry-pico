#include "hardware/gpio.h"

#define LED_GPIO 25

int main(void) {

  _gpio_init(LED_GPIO);
  gpio_set_dir(LED_GPIO, true);

  while(true) {

    gpio_put(LED_GPIO, !gpio_get(LED_GPIO));
    sleep_ms(500);
  }
  return 0;
}