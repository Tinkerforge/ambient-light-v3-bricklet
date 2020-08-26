#include "bindings/hal_common.h"
#include "bindings/bricklet_ambient_light_v3.h"

#define UID "XYZ" // Change XYZ to the UID of your Ambient Light Bricklet 3.0

void check(int rc, const char* msg);

// Callback function for illuminance callback
void illuminance_handler(TF_AmbientLightV3 *device, uint32_t illuminance,
                         void *user_data) {
	(void)device; (void)user_data; // avoid unused parameter warning

	tf_hal_printf("Illuminance: %d 1/%d lx\n", illuminance, 100.0);
}

TF_AmbientLightV3 al;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_ambient_light_v3_create(&al, UID, hal), "create device object");

	// Register illuminance callback to function illuminance_handler
	tf_ambient_light_v3_register_illuminance_callback(&al,
	                                                  illuminance_handler,
	                                                  NULL);

	// Set period for illuminance callback to 1s (1000ms) without a threshold
	tf_ambient_light_v3_set_illuminance_callback_configuration(&al, 1000, false, 'x', 0, 0);
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
