//#include <atmel_start.h>

/*int main(void)
{
	/* Initializes MCU, drivers and middleware */
//	atmel_start_init();

	/* Replace with your application code */
/*	while (1) {
	}
}*/
	
//#include <asf.h>
#include "cryptoauthlib.h"
//#include "cryptoauthlib_main.h"
#include "atmel_start.h"
#include <cryptoauthlib_interface_config.h>
#include <string.h>

ATCAIfaceCfg CRYPTO_AUTHENTICATION_INTERFACE_0_desc
= {.iface_type            = ATCA_I2C_IFACE,
	.devtype               = ATECC108A,
	.atcai2c.slave_address = CONF_CRYPTO_AUTHENTICATION_INTERFACE_0_I2C_ADDRESS,
	.atcai2c.bus           = 0,
	.atcai2c.baud          = CONF_CRYPTO_AUTHENTICATION_INTERFACE_0_I2C_FREQUENCY,
	.wake_delay            = CONF_CRYPTO_AUTHENTICATION_INTERFACE_0_I2C_WAKEUP_DELAY,
	.rx_retries            = CONF_CRYPTO_AUTHENTICATION_INTERFACE_0_I2C_RXRETRY,
	.cfg_data              = &Interface};


void CRYPTO_AUTHENTICATION_INTERFACE_0_init(void)
{
	atcab_init(&CRYPTO_AUTHENTICATION_INTERFACE_0_desc);
}


int main(void)
{
	
	uint8_t inBytes = 4;
	uint8_t bufferIn[4] = {0x74, 0xba, 0x25, 0x21};
	uint8_t bufferOut[32];
	uint8_t flag = 0;
	ATCA_STATUS status;
	uint8_t     serialnum[ATCA_SERIAL_NUM_SIZE];
	uint8_t     random_number[ATCA_KEY_SIZE];
	uint8_t     loop_count = 2;
			
	system_init();
	
	/* Init CRYPTO_AUTHENTICATION_INTERFACE_0 */
	 CRYPTO_AUTHENTICATION_INTERFACE_0_init();
	
	do {
		/* Read device serial number... Unique value for each device and same on every read */
		if (ATCA_SUCCESS != (status = atcab_read_serial_number(serialnum)))
		break;

		/* Read random number... Unique value on every read */
		if (ATCA_SUCCESS != (status = atcab_random(random_number)))
		break;
		
		/*Generate hash of output length 256-bit*/
		memset(bufferOut, 0x00, 32);
		if (ATCA_SUCCESS != (status = atcab_sha(inBytes, bufferIn, bufferOut)))
			break;
			
	} while (loop_count--);
	
}	
