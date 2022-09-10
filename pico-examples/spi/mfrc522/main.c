#include <stdio.h>
#include "pico/stdlib.h"
#include "mfrc522.h"

int main(void) {
    /* Init pico */
    stdio_init_all();
    /* Wait for USB to boot */
    sleep_ms(1000);
    /* Print welcome messaje */
    printf("\n\n");
    printf("MFRC522 example\n");
    /* Initialize MFRC522 */
    mfrc_init();
    printf("MFRC522 initialized!\n");
    /* Check firmware version to verify communication */
    mfrc_firmware_version_t version = mfrc_get_version();
    /* Print firmware version */
    switch (version) {
 
        case FM17522:
            printf("FM17522 Firmware\n");
            break;

        case MFRC522_V0_0:
            printf("MFRC522 V0.0\n");
            break;

        case MFRC522_V1_0:
            printf("MFRC522 V1.0\n");
            break;

        case MFRC522_V2_0:
            printf("MFRC522 V2.0\n");
            break;
        
        default:
            printf("No valid firmware (0x%02x)\n", version);
            break;
    }

    while(1);
}