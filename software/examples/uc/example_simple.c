// This example is not self-contained.
// It requires usage of the example driver specific to your platform.
// See the HAL documentation.

#include "src/bindings/hal_common.h"
#include "src/bindings/bricklet_ambient_light_v3.h"

void check(int rc, const char *msg);
void example_setup(TF_HAL *hal);
void example_loop(TF_HAL *hal);

static TF_AmbientLightV3 al;

void example_setup(TF_HAL *hal) {
	// Create device object
	check(tf_ambient_light_v3_create(&al, NULL, hal), "create device object");

	// Get current Illuminance
	uint32_t illuminance;
	check(tf_ambient_light_v3_get_illuminance(&al, &illuminance), "get Illuminance");

	tf_hal_printf("Illuminance: %d 1/%d lx\n", illuminance, 100);
}

void example_loop(TF_HAL *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
