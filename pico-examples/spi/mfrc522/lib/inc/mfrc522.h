#ifndef MFRC522_H_
#define MFRC522_H

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "mfrc522_reg.h"

#define SPI0_DEFAULT_MISO   16
#define SPI0_DEFAULT_SS     17
#define SPI0_DEFAULT_SCK    18
#define SPI0_DEFAULT_MOSI   19

#define MFRC_DEFAULT_FREQUENCY      500000       

typedef struct {
    spi_inst_t *spi;
    uint32_t freq;
    uint8_t mosi;
    uint8_t miso;
    uint8_t sck;
    uint8_t ss;
    uint8_t rst;
} mfrc_config_t;

void mfrc522_config_init(mfrc_config_t *config);

static inline mfrc_config_t mfrc522_get_default_config(void) {
    return (mfrc_config_t) {
        spi0,
        MFRC_DEFAULT_FREQUENCY,
        SPI0_DEFAULT_MOSI, 
        SPI0_DEFAULT_MISO, 
        SPI0_DEFAULT_SCK, 
        SPI0_DEFAULT_SS, 
        -1 
    };
}

#endif  /* MFRC522_H */