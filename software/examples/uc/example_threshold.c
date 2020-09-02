// This example is not self-contained.
// It requres usage of the example driver specific to your platform.
// See the HAL documentation.

#include "bindings/hal_common.h"
#include "bindings/bricklet_ambient_light_v3.h"

#define UID "XYZ" // Change XYZ to the UID of your Ambient Light Bricklet 3.0

void check(int rc, const char* msg);

void example_setup(TF_HalContext *hal);
void example_loop(TF_HalContext *hal);


// Callback function for illuminance callback
static void illuminance_handler(TF_AmbientLightV3 *device, uint32_t illuminance,
                                void *user_data) {
	(void)device; (void)user_data; // avoid unused parameter warning

	tf_hal_printf("Illuminance: %d 1/%d lx\n", illuminance, 100.0);
	tf_hal_printf("Too bright, close the curtains!\n");
}

static TF_AmbientLightV3 al;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_ambient_light_v3_create(&al, UID, hal), "create device object");

	// Register illuminance callback to function illuminance_handler
	tf_ambient_light_v3_register_illuminance_callback(&al,
	                                                  illuminance_handler,
	                                                  NULL);

	// Configure threshold for illuminance "greater than 500 lx"
	// with a debounce period of 1s (1000ms)
	tf_ambient_light_v3_set_illuminance_callback_configuration(&al, 1000, false, '>', 500*100, 0);
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
