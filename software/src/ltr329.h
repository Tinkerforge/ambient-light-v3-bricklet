/* ambient-light-v3-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * ltr329.h: Driver for LTR329ALS ambient light sensor
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

#ifndef LTR329_H
#define LTR329_H

#include <stdint.h>

#include "bricklib2/hal/i2c_fifo/i2c_fifo.h"

#define LTR329_REG_ALS_CONTR     0x80
#define LTR329_REG_ALS_MEAS_RATE 0x85
#define LTR329_REG_PART_ID       0x86
#define LTR329_REG_MANUFAC_ID    0x87
#define LTR329_REG_ALS_DATA_CH1  0x88 // 2 bytes
#define LTR329_REG_ALS_DATA_CH0  0x8A // 2 bytes
#define LTR329_REG_ALS_STATUS    0x8C

// These are sensor register values, NOT Bricklet API constant values
#define LTR329_RANGE_64000LUX 0
#define LTR329_RANGE_32000LUX 1
#define LTR329_RANGE_16000LUX 2
#define LTR329_RANGE_8000LUX  3
#define LTR329_RANGE_1300LUX  6
#define LTR329_RANGE_600LUX   7

// These are sensor register values, NOT Bricklet API constant values
#define LTR329_INTEGRATION_TIME_100MS 0
#define LTR329_INTEGRATION_TIME_50MS  1
#define LTR329_INTEGRATION_TIME_200MS 2
#define LTR329_INTEGRATION_TIME_400MS 3
#define LTR329_INTEGRATION_TIME_150MS 4
#define LTR329_INTEGRATION_TIME_250MS 5
#define LTR329_INTEGRATION_TIME_300MS 6
#define LTR329_INTEGRATION_TIME_350MS 7

typedef struct {
	I2CFifo i2c_fifo;

	uint8_t illuminance_range;
	uint8_t integration_time;

	uint8_t new_illuminance_range;
	uint8_t new_integration_time;

	uint32_t illuminance;
	bool throw_next_data_away;
} LTR329;

extern LTR329 ltr329;

void ltr329_tick(void);
void ltr329_init(void);
uint32_t ltr329_get_illuminance(void);

#endif