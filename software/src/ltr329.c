/* ambient-light-v3-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * ltr329.c: Driver for LTR329ALS ambient light sensor
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#include "ltr329.h"

#include "configs/config_ltr329.h"

#include "bricklib2/os/coop_task.h"
#include "bricklib2/hal/i2c_fifo/i2c_fifo.h"
#include "bricklib2/utility/util_definitions.h"

#define CH0 1
#define CH1 0

LTR329 ltr329;
CoopTask ltr329_task;

void ltr329_update_values(const uint16_t values[2], const uint8_t status) {
	// See Appendix A for Lux calculation from channel 0 and 1 measurements

	uint32_t lux = 0;
	uint32_t ratio = (values[CH1]*1000)/(values[CH0]+values[CH1]);
	if(ratio < 450) {
		lux = (values[CH0]*17743 + values[CH1]*11059);
	} else if(ratio < 640 && ratio >= 450) {
		lux = (values[CH0]*42785 - values[CH1]*19548);
	} else if(ratio < 850 && ratio >= 640) {
		lux = (values[CH0]*5926 + values[CH1]*1185);
	}

	uint32_t divider = 1;
	uint32_t multiplier = 1;

	switch((status >> 4) & 0x7) {
		case LTR329_RANGE_64000LUX: divider = 1;  break;
		case LTR329_RANGE_32000LUX: divider = 2;  break;
		case LTR329_RANGE_16000LUX: divider = 4;  break;
		case LTR329_RANGE_8000LUX:  divider = 8;  break;
		case LTR329_RANGE_1300LUX:  divider = 48; break;
		case LTR329_RANGE_600LUX:   divider = 96; break;
	}

	switch(ltr329.integration_time) {
		case 0:               multiplier = 2; break;
		case 1:                               break;
		case 2: divider *= 3; multiplier = 2; break;
		case 3: divider *= 2;                 break;
		case 4: divider *= 5; multiplier = 2; break;
		case 5: divider *= 3;                 break;
		case 6: divider *= 7; multiplier = 2; break;
		case 7: divider *= 4;                 break;
	}

	lux /= divider * 100 / multiplier; // Calculate lux

	// Cap lux measurement for each range to defined maximum +0.01 lux.
	// This allows to distinguisch between the last value inside the range and
	// out-of-range values.
	switch(ltr329.illuminance_range) {
		case 6:                          break; // Unlimited
		case 5: lux = MIN(lux,   60001); break;
		case 4: lux = MIN(lux,  130001); break;
		case 3: lux = MIN(lux,  800001); break;
		case 2: lux = MIN(lux, 1600001); break;
		case 1: lux = MIN(lux, 3200001); break;
		case 0: lux = MIN(lux, 6400001); break;
	}

	ltr329.illuminance = MAX(lux, 1); // Avoid 0, it means sensor is saturated
}


void ltr329_update_configuration(void) {
	uint8_t range = LTR329_RANGE_8000LUX;
	switch(ltr329.illuminance_range) {
		case 0: range = LTR329_RANGE_64000LUX; break;
		case 1: range = LTR329_RANGE_32000LUX; break;
		case 2: range = LTR329_RANGE_16000LUX; break;
		case 3: range = LTR329_RANGE_8000LUX;  break;
		case 4: range = LTR329_RANGE_1300LUX;  break;
		case 5: range = LTR329_RANGE_600LUX;   break;
		case 6: range = LTR329_RANGE_64000LUX; break; // Unlimited
	}

	uint8_t time = LTR329_INTEGRATION_TIME_150MS;
	switch(ltr329.integration_time) {
		case 0: time = LTR329_INTEGRATION_TIME_50MS; break;
		case 1: time = LTR329_INTEGRATION_TIME_100MS; break;
		case 2: time = LTR329_INTEGRATION_TIME_150MS; break;
		case 3: time = LTR329_INTEGRATION_TIME_200MS; break;
		case 4: time = LTR329_INTEGRATION_TIME_250MS; break;
		case 5: time = LTR329_INTEGRATION_TIME_300MS; break;
		case 6: time = LTR329_INTEGRATION_TIME_350MS; break;
		case 7: time = LTR329_INTEGRATION_TIME_400MS; break;
	}

	// Enable ALS and set gain
	uint8_t data = (range << 2) | (1 << 0);
	i2c_fifo_coop_write_register(&ltr329.i2c_fifo, LTR329_REG_ALS_CONTR, 1, &data, true);

	// Set integration time
	data = time << 3;
	i2c_fifo_coop_write_register(&ltr329.i2c_fifo, LTR329_REG_ALS_MEAS_RATE, 1, &data, true);

	ltr329.throw_next_data_away = true;
}

void ltr329_task_tick(void) {
	uint16_t data[2];
	uint8_t status;

	// Sleep 100ms before initial init (see p22)
	coop_task_sleep_ms(100);

	while(true) {
		if((ltr329.new_illuminance_range != 255) || (ltr329.new_integration_time != 255)) {
			ltr329.illuminance_range = ltr329.new_illuminance_range;
			ltr329.integration_time  = ltr329.new_integration_time;

			ltr329.new_illuminance_range = 255;
			ltr329.new_integration_time  = 255;

			ltr329_update_configuration();
		}

		coop_task_sleep_ms(10);
		i2c_fifo_coop_read_register(&ltr329.i2c_fifo, LTR329_REG_ALS_STATUS, 1, &status);

		// Check if new data is available
		if(status & (1 << 2)) {
			// Check if new data is invalid
			if(status & (1 << 7)) {
				ltr329.illuminance = 0; // 0 means sensor is saturated
			} else {
				i2c_fifo_coop_read_register(&ltr329.i2c_fifo, LTR329_REG_ALS_DATA_CH1, 4, (uint8_t*)&data);
				if(ltr329.throw_next_data_away) {
					ltr329.throw_next_data_away = false;
				} else {
					ltr329_update_values(data, status);
				}
			}
		}
	}
}

void ltr329_init_i2c(void) {
	ltr329.i2c_fifo.baudrate         = LTR329_I2C_BAUDRATE;
	ltr329.i2c_fifo.address          = LTR329_I2C_ADDRESS;
	ltr329.i2c_fifo.i2c              = LTR329_I2C;

	ltr329.i2c_fifo.scl_port         = LTR329_SCL_PORT;
	ltr329.i2c_fifo.scl_pin          = LTR329_SCL_PIN;
	ltr329.i2c_fifo.scl_mode         = LTR329_SCL_PIN_MODE;
	ltr329.i2c_fifo.scl_input        = LTR329_SCL_INPUT;
	ltr329.i2c_fifo.scl_source       = LTR329_SCL_SOURCE;
	ltr329.i2c_fifo.scl_fifo_size    = LTR329_SCL_FIFO_SIZE;
	ltr329.i2c_fifo.scl_fifo_pointer = LTR329_SCL_FIFO_POINTER;

	ltr329.i2c_fifo.sda_port         = LTR329_SDA_PORT;
	ltr329.i2c_fifo.sda_pin          = LTR329_SDA_PIN;
	ltr329.i2c_fifo.sda_mode         = LTR329_SDA_PIN_MODE;
	ltr329.i2c_fifo.sda_input        = LTR329_SDA_INPUT;
	ltr329.i2c_fifo.sda_source       = LTR329_SDA_SOURCE;
	ltr329.i2c_fifo.sda_fifo_size    = LTR329_SDA_FIFO_SIZE;
	ltr329.i2c_fifo.sda_fifo_pointer = LTR329_SDA_FIFO_POINTER;

	i2c_fifo_init(&ltr329.i2c_fifo);
}

void ltr329_init(void) {
	memset(&ltr329, 0, sizeof(LTR329));
	ltr329_init_i2c();

	ltr329.new_illuminance_range = 3; // 8000lux
	ltr329.new_integration_time = 2; // 150ms
	ltr329.throw_next_data_away = true;

	coop_task_init(&ltr329_task, ltr329_task_tick);
}

void ltr329_tick(void) {
	coop_task_tick(&ltr329_task);
}

uint32_t ltr329_get_illuminance(void) {
	return ltr329.illuminance;
}