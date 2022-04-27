// This example is not self-contained.
// It requires usage of the example driver specific to your platform.
// See the HAL documentation.

#include "src/bindings/hal_common.h"
#include "src/bindings/bricklet_ambient_light_v3.h"

void check(int rc, const char *msg);
void example_setup(TF_HAL *hal);
void example_loop(TF_HAL *hal);

// Callback function for illuminance callback
static void illuminance_handler(TF_AmbientLightV3 *device, uint32_t illuminance,
                                void *user_data) {
	(void)device; (void)user_data; // avoid unused parameter warning

	tf_hal_printf("Illuminance: %d 1/%d lx\n", illuminance, 100);
}

static TF_AmbientLightV3 al;

void example_setup(TF_HAL *hal) {
	// Create device object
	check(tf_ambient_light_v3_create(&al, NULL, hal), "create device object");

	// Register illuminance callback to function illuminance_handler
	tf_ambient_light_v3_register_illuminance_callback(&al,
	                                                  illuminance_handler,
	                                                  NULL);

	// Set period for illuminance callback to 1s (1000ms) without a threshold
	tf_ambient_light_v3_set_illuminance_callback_configuration(&al, 1000, false, 'x', 0, 0);
}

void example_loop(TF_HAL *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
