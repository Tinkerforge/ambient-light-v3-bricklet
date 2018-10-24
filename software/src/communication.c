/* ambient-light-v3-bricklet
 * Copyright (C) 2018 Olaf Lüke <olaf@tinkerforge.com>
 *
 * communication.c: TFP protocol message handling
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

#include "communication.h"

#include "bricklib2/utility/communication_callback.h"
#include "bricklib2/protocols/tfp/tfp.h"
#include "bricklib2/utility/callback_value.h"

#include "ltr329.h"

CallbackValue_uint32_t callback_value_illuminance;


BootloaderHandleMessageResponse handle_message(const void *message, void *response) {
	switch(tfp_get_fid_from_message(message)) {
		case FID_GET_ILLUMINANCE: return get_callback_value_uint32_t(message, response, &callback_value_illuminance);
		case FID_SET_ILLUMINANCE_CALLBACK_CONFIGURATION: return set_callback_value_callback_configuration_uint32_t(message, &callback_value_illuminance);
		case FID_GET_ILLUMINANCE_CALLBACK_CONFIGURATION: return get_callback_value_callback_configuration_uint32_t(message, response, &callback_value_illuminance);
		case FID_SET_CONFIGURATION: return set_configuration(message);
		case FID_GET_CONFIGURATION: return get_configuration(message, response);
		default: return HANDLE_MESSAGE_RESPONSE_NOT_SUPPORTED;
	}
}


BootloaderHandleMessageResponse set_configuration(const SetConfiguration *data) {
	if((data->integration_time > AMBIENT_LIGHT_V3_INTEGRATION_TIME_400MS) || 
	   (data->illuminance_range > AMBIENT_LIGHT_V3_ILLUMINANCE_RANGE_UNLIMITED)) {
		return HANDLE_MESSAGE_RESPONSE_INVALID_PARAMETER;
	}

	ltr329.new_illuminance_range = data->illuminance_range;
	ltr329.new_integration_time = data->integration_time;

	return HANDLE_MESSAGE_RESPONSE_EMPTY;
}

BootloaderHandleMessageResponse get_configuration(const GetConfiguration *data, GetConfiguration_Response *response) {
	response->header.length     = sizeof(GetConfiguration_Response);
	response->illuminance_range = ltr329.illuminance_range;
	response->integration_time  = ltr329.integration_time;

	return HANDLE_MESSAGE_RESPONSE_NEW_MESSAGE;
}




bool handle_illuminance_callback(void) {
	return handle_callback_value_callback_uint32_t(&callback_value_illuminance, FID_CALLBACK_ILLUMINANCE);
}

void communication_tick(void) {
	communication_callback_tick();
}

void communication_init(void) {
	// TODO: Add proper functions
	callback_value_init_uint32_t(&callback_value_illuminance, ltr329_get_illuminance);

	communication_callback_init();
}
