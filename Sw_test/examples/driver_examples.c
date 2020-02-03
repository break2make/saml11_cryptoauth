/*
 * Code generated from Atmel Start.
 *
 * This file will be overwritten when reconfiguring your Atmel Start project.
 * Please copy examples or other code you want to keep to a separate file
 * to avoid losing it when reconfiguring.
 */

#include "driver_examples.h"
#include "driver_init.h"
#include "utils.h"

void Interface_example(void)
{
	struct io_descriptor *Interface_io;

	i2c_m_sync_get_io_descriptor(&Interface, &Interface_io);
	i2c_m_sync_enable(&Interface);
	i2c_m_sync_set_slaveaddr(&Interface, 0x12, I2C_M_SEVEN);
	io_write(Interface_io, (uint8_t *)"Hello World!", 12);
}
