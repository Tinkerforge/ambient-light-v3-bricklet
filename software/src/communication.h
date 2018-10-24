/* ambient-light-v3-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.h: TFP protocol message handling
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

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdint.h>
#include <stdbool.h>

#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/bootloader/bootloader.h"

// Default functions
BootloaderHandleMessageResponse handle_message(const void *data, void *response);
void communication_tick(void);
void communication_init(void);

// Constants
#define AMBIENT_LIGHT_V3_THRESHOLD_OPTION_OFF 'x'
#define AMBIENT_LIGHT_V3_THRESHOLD_OPTION_OUTSIDE 'o'
#define AMBIENT_LIGHT_V3_THRESHOLD_OPTION_INSIDE 'i'
#define AMBIENT_LIGHT_V3_THRESHOLD_OPTION_SMALLER '<'
#define AMBIENT_LIGHT_V3_THRESHOLD_OPTION_GREATER '>'

#define AMBIENT_LIGHT_V3_ILLUMINANCE_RANGE_UNLIMITED 6
#define AMBIENT_LIGHT_V3_ILLUMINANCE_RANGE_64000LUX 0
#define AMBIENT_LIGHT_V3_ILLUMINANCE_RANGE_32000LUX 1
#define AMBIENT_LIGHT_V3_ILLUMINANCE_RANGE_16000LUX 2
#define AMBIENT_LIGHT_V3_ILLUMINANCE_RANGE_8000LUX 3
#define AMBIENT_LIGHT_V3_ILLUMINANCE_RANGE_1300LUX 4
#define AMBIENT_LIGHT_V3_ILLUMINANCE_RANGE_600LUX 5

#define AMBIENT_LIGHT_V3_INTEGRATION_TIME_50MS 0
#define AMBIENT_LIGHT_V3_INTEGRATION_TIME_100MS 1
#define AMBIENT_LIGHT_V3_INTEGRATION_TIME_150MS 2
#define AMBIENT_LIGHT_V3_INTEGRATION_TIME_200MS 3
#define AMBIENT_LIGHT_V3_INTEGRATION_TIME_250MS 4
#define AMBIENT_LIGHT_V3_INTEGRATION_TIME_300MS 5
#define AMBIENT_LIGHT_V3_INTEGRATION_TIME_350MS 6
#define AMBIENT_LIGHT_V3_INTEGRATION_TIME_400MS 7

#define AMBIENT_LIGHT_V3_BOOTLOADER_MODE_BOOTLOADER 0
#define AMBIENT_LIGHT_V3_BOOTLOADER_MODE_FIRMWARE 1
#define AMBIENT_LIGHT_V3_BOOTLOADER_MODE_BOOTLOADER_WAIT_FOR_REBOOT 2
#define AMBIENT_LIGHT_V3_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_REBOOT 3
#define AMBIENT_LIGHT_V3_BOOTLOADER_MODE_FIRMWARE_WAIT_FOR_ERASE_AND_REBOOT 4

#define AMBIENT_LIGHT_V3_BOOTLOADER_STATUS_OK 0
#define AMBIENT_LIGHT_V3_BOOTLOADER_STATUS_INVALID_MODE 1
#define AMBIENT_LIGHT_V3_BOOTLOADER_STATUS_NO_CHANGE 2
#define AMBIENT_LIGHT_V3_BOOTLOADER_STATUS_ENTRY_FUNCTION_NOT_PRESENT 3
#define AMBIENT_LIGHT_V3_BOOTLOADER_STATUS_DEVICE_IDENTIFIER_INCORRECT 4
#define AMBIENT_LIGHT_V3_BOOTLOADER_STATUS_CRC_MISMATCH 5

#define AMBIENT_LIGHT_V3_STATUS_LED_CONFIG_OFF 0
#define AMBIENT_LIGHT_V3_STATUS_LED_CONFIG_ON 1
#define AMBIENT_LIGHT_V3_STATUS_LED_CONFIG_SHOW_HEARTBEAT 2
#define AMBIENT_LIGHT_V3_STATUS_LED_CONFIG_SHOW_STATUS 3

// Function and callback IDs and structs
#define FID_GET_ILLUMINANCE 1
#define FID_SET_ILLUMINANCE_CALLBACK_CONFIGURATION 2
#define FID_GET_ILLUMINANCE_CALLBACK_CONFIGURATION 3
#define FID_SET_CONFIGURATION 5
#define FID_GET_CONFIGURATION 6

#define FID_CALLBACK_ILLUMINANCE 4

typedef struct {
	TFPMessageHeader header;
	uint8_t illuminance_range;
	uint8_t integration_time;
} __attribute__((__packed__)) SetConfiguration;

typedef struct {
	TFPMessageHeader header;
} __attribute__((__packed__)) GetConfiguration;

typedef struct {
	TFPMessageHeader header;
	uint8_t illuminance_range;
	uint8_t integration_time;
} __attribute__((__packed__)) GetConfiguration_Response;


// Function prototypes
BootloaderHandleMessageResponse set_configuration(const SetConfiguration *data);
BootloaderHandleMessageResponse get_configuration(const GetConfiguration *data, GetConfiguration_Response *response);

// Callbacks
bool handle_illuminance_callback(void);

#define COMMUNICATION_CALLBACK_TICK_WAIT_MS 1
#define COMMUNICATION_CALLBACK_HANDLER_NUM 1
#define COMMUNICATION_CALLBACK_LIST_INIT \
	handle_illuminance_callback, \


#endif
