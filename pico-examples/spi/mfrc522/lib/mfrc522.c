#include "mfrc522.h"

static mfrc_config_t *mfrc;

void mfrc_config_init(mfrc_config_t *config) {
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

    mfrc_write_register(TxModeReg, 0x00);
    mfrc_write_register(RxModeReg, 0x00);
}

static void mfrc_write_register(mfrc_reg_t reg, uint8_t value) {

    uint8_t buff[] = {reg, value};

    gpio_put(mfrc->ss, false);
    spi_write_blocking(mfrc->spi, buff, 2);
    gpio_put(mfrc->ss, true);
}