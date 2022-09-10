#ifndef MFRC522_H_
#define MFRC522_H

#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "mfrc522_reg.h"
#include "mfrc522_cmd.h"

#define SPI0_DEFAULT_MISO   16
#define SPI0_DEFAULT_SS     17
#define SPI0_DEFAULT_SCK    18
#define SPI0_DEFAULT_MOSI   19

#define MFRC_DEFAULT_FREQUENCY      500000       

/**
 * @brief Configuration struct for the MFRC module.
 */
typedef struct {
    spi_inst_t *spi;    // SPI to use (spi0 or spi1)
    uint32_t freq;      // Desired frequency in Hz
    uint8_t mosi;       // MOSI GPIO
    uint8_t miso;       // MISO GPIO
    uint8_t sck;        // SDK GPIO
    uint8_t ss;         // SS GPIO
    uint8_t rst;        // Reset GPIO
} mfrc_config_t;

void mfrc_config_init(mfrc_config_t *config);
static void mfrc_write_register(mfrc_reg_t reg, uint8_t value);
static uint8_t mfrc_read_register(mfrc_reg_t reg);
static void mfrc_write(mfrc_reg_t reg, uint8_t *buff, uint8_t len);
static void mfrc_read(mfrc_reg_t reg, uint8_t *buff, uint8_t len);
static void mfrc_set_antenna_on(bool on);
static void mfrc_do_soft_reset(void);

/**
 * @brief Gets the MFRC default configuration.
 * 
 * @return mfrc_config_t Struct with the default values.
 */
static inline mfrc_config_t mfrc_get_default_config(void) {
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

/**
 * @brief Clears the given bits on a register.
 * 
 * @param reg Register to write.
 * @param mask Bit mask.
 */
static inline void mfrc_clear_register_mask(mfrc_reg_t reg, uint8_t mask) {
    /* Get register value */
    uint8_t tmp = mfrc_read_register(reg);
    /* Clear indicated bits and write */
    mfrc_write_register(reg, tmp & ~mask);
}

/**
 * @brief Sets the given bits on a register.
 * 
 * @param reg Register to write.
 * @param mask Bit mask.
 */
static inline void mfrc_set_register_mask(mfrc_reg_t reg, uint8_t mask) {
    /* Get register value */
    uint8_t tmp = mfrc_read_register(reg);
    /* Set indicated bits and write */
    mfrc_write_register(reg, tmp | mask);
}

#endif  /* MFRC522_H */