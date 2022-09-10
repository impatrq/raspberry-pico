#include "mfrc522.h"

/**
 * @brief MFRC struct to keep track of GPIO and SPI used.
 */
static mfrc_config_t *mfrc;

/**
 * @brief Initializes the MFRC module with given configuration.
 * 
 * @param config Pointer to the configuration struct.
 */
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
    /* Reset baud rates */
    mfrc_write_register(TxModeReg, 0x00);
    mfrc_write_register(RxModeReg, 0x00);
    /* Reset ModWidthReg */
    mfrc_write_register(ModWidthReg, 0x26);

    /* 
     * When communicating with a PICC we need a timeout if something goes wrong
	 * f_timer = 13.56 MHz / (2*TPreScaler+1) where TPreScaler = [TPrescaler_Hi:TPrescaler_Lo]
	 * TPrescaler_Hi are the four low bits in TModeReg. TPrescaler_Lo is TPrescalerReg. 
     */
    /* TAuto=1; timer starts automatically at the end of the transmission in all communication modes at all speeds */
	mfrc_write_register(TModeReg, 0x80);
    /* TPreScaler = TModeReg[3..0]:TPrescalerReg, ie 0x0A9 = 169 => f_timer=40kHz, ie a timer period of 25μs */
	mfrc_write_register(TPrescalerReg, 0xA9);
    /* Reload timer with 0x3E8 = 1000, ie 25ms before timeout */
	mfrc_write_register(TReloadRegH, 0x03);
	mfrc_write_register(TReloadRegL, 0xE8);
	/* Default 0x00. Force a 100 % ASK modulation independent of the ModGsPReg register setting */
	mfrc_write_register(TxASKReg, 0x40);
    /* Default 0x3F. Set the preset value for the CRC coprocessor for the CalcCRC command to 0x6363 */
	mfrc_write_register(ModeReg, 0x3D);
    /* Enable the antenna driver pins TX1 and TX2 (they were disabled by the reset) */
    mfrc_set_antenna_on(true);
}

/**
 * @brief Writes a value on given register.
 * 
 * @param reg Register to write.
 * @param value Value to write.
 */
static void mfrc_write_register(mfrc_reg_t reg, uint8_t value) {
    /* Create an array with the register and value */
    uint8_t buff[] = {reg, value};
    /* Enable module */
    gpio_put(mfrc->ss, false);
    /* Write buffer */
    spi_write_blocking(mfrc->spi, buff, 2);
    /* Disable module */
    gpio_put(mfrc->ss, true);
}

/**
 * @brief Reads a register and returns the value.
 * 
 * @param reg Register to read.
 * 
 * @return uint8_t Register value.
 */
static uint8_t mfrc_read_register(mfrc_reg_t reg) {
    /* Pointer to store result */
    uint8_t *buff;
    /* Enable module */
    gpio_put(mfrc->ss, false);
    /* Read register and store value */
    spi_read_blocking(mfrc->spi, 0x00, buff, 1);
    /* Disable module */
    gpio_put(mfrc->ss, true);
    /* Return register value */
    return *buff;
}

/**
 * @brief Writes to the given register a specified number of bytes.
 * 
 * @param reg Register to write.
 * @param buff Pointer to data to write.
 * @param len Number of bytes to write.
 */
static void mfrc_write(mfrc_reg_t reg, uint8_t *buff, uint8_t len) {
    /* Enable module */
    gpio_put(mfrc->ss, false);
    /* Write register */
    spi_write_blocking(mfrc->spi, &reg, 1);
    /* Write buffer */
    spi_write_blocking(mfrc->spi, buff, len);
    /* Disable module */
    gpio_put(mfrc->ss, true);
}

/**
 * @brief Turns the antenna on/off by enabling pins
 * TX1 and TX2.
 * 
 * @param on True to turn on, false to turn off.
 * 
 * @note After a reset these pins are disabled.
 */
static void mfrc_set_antenna_on(bool on) {
    /* Check on value */
    if(on) {
        /* If on is true, read tx control regiter first */
        uint8_t value = mfrc_read_register(TxControlReg);
        /* Turn on antenna if off */
        if((value & 0x03) != 0x03) { mfrc_write_register(TxControlReg, value | 0x03); }
    }
    /* If on is false, turn off antenna */
    else { mfrc_clear_register_mask(TxControlReg, 0x03); }
}

/**
 * @brief Performs a soft reset and waits to be on again
 * 
 * @note  The datasheet does not mention how long the SoftRest command takes to complete.
 * But the MFRC522 might have been in soft power-down mode (triggered by bit 4 of CommandReg) 
 * Section 8.8.2 in the datasheet says the oscillator start-up time is the start up time of the 
 * crystal + 37,74μs. Let us be generous: 50ms.
 */
static void mfrc_do_soft_reset(void) {
    /* Perform a soft reset */
    mfrc_write_register(CommandReg, SoftReset);
    /* Wait for the PowerDown bit in CommandReg to be cleared */
    while(mfrc_read_register(CommandReg) & (1 << 4));
    sleep_ms(50);
}