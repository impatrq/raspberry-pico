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

static void mfrc_write_register(mfrc_reg_t reg, uint8_t value) {

    uint8_t buff[] = {reg, value};

    gpio_put(mfrc->ss, false);
    spi_write_blocking(mfrc->spi, buff, 2);
    gpio_put(mfrc->ss, true);
}

static uint8_t mfrc_read_register(mfrc_reg_t reg) {

    uint8_t *buff;

    gpio_put(mfrc->ss, false);
    spi_read_blocking(mfrc->spi, 0x00, buff, 1);
    gpio_put(mfrc->ss, true);

    return *buff;
}

static void mfrc_set_antenna_on(bool on) {

    if(on) {
        uint8_t value = mfrc_read_register(TxControlReg);
        if((value & 0x03) != 0x03) { mfrc_write_register(TxControlReg, value | 0x03); }
    }
    else { mfrc_clear_register_mask(TxControlReg, 0x03); }
}

static void mfrc_do_soft_reset(void) {
    /* Perform a soft reset */
    mfrc_write_register(CommandReg, mfrc_soft_reset);
    /* Wait for the PowerDown bit in CommandReg to be cleared */
    while(mfrc_read_register(CommandReg) & (1 << 4));
    sleep_ms(50);
}