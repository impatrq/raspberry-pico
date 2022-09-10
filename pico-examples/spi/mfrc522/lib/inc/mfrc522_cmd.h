#ifndef MFRC522_CMD_H_
#define MFRC522_CMD_H_

/**
 * @brief MFRC522 commands. Described in chapter 10 of the datasheet
 */
typedef enum {
    mfrc_idle				= 0x00,		// no action, cancels current command execution
    mfrc_mem				= 0x01,		// stores 25 bytes into the internal buffer
    mfrc_generate_random_id	= 0x02,		// generates a 10-byte random ID number
    mfrc_calc_crc			= 0x03,		// activates the CRC coprocessor or performs a self-test
    mfrc_transmit			= 0x04,		// transmits data from the FIFO buffer
    mfrc_no_cmd_change		= 0x07,		// no command change, can be used to modify the CommandReg register bits without affecting the command, for example, the PowerDown bit
    mfrc_receive			= 0x08,		// activates the receiver circuits
    mfrc_transceive			= 0x0C,		// transmits data from FIFO buffer to antenna and automatically activates the receiver after transmission
    mfrc_mf_authent 		= 0x0E,		// performs the MIFARE standard authentication as a reader
    mfrc_soft_reset			= 0x0F		// resets the MFRC522
} mfrc_cmd_t;

#endif  /* MFRC522_CMD_H_ */