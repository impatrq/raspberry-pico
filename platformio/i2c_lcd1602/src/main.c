#include "hardware/gpio.h"
#include "hardware/i2c.h"
#include "lcd_i2c.h"

#define GPIO_SDA  2
#define GPIO_SCL  3

int main(void) {

  _i2c_init(i2c1, 100000UL);

  gpio_set_function(GPIO_SDA, GPIO_FUNC_I2C);
  gpio_set_function(GPIO_SCL, GPIO_FUNC_I2C);

  gpio_pull_up(GPIO_SDA);
  gpio_pull_up(GPIO_SCL);

  lcd_init(i2c1);

  while(true) {

    lcd_clear();
    lcd_string("Hello world!");
    sleep_ms(500);
  }
}