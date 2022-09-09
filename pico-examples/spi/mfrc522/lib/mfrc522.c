#include "mfrc522.h"

static mfrc_config_t *mfrc;

void mfrc522_config_init(mfrc_config_t *config) {
    /* Save configuration struct */
    mfrc = config;
    /* Initialize SPI */
    spi_init(config->spi, config->freq);
    /* Configure MOSI, MISO and SCK pins */
    gpio_set_function(config->mosi, GPIO_FUNC_SPI);
    gpio_set_function(config->miso, GPIO_FUNC_SPI);
    gpio_set_function(config->sck, GPIO_FUNC_SPI);
    /* Configure SS as output */
    gpio_init(config->ss);
    gpio_set_dir(config->ss, true);
    gpio_put(config->ss, true);
    /* Configure RST pin, if available */
    if(config->rst > -1) { 
        gpio_init(config->rst);
        gpio_set_dir(config->rst, true); 
    }
}