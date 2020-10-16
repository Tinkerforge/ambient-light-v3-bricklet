// This example is not self-contained.
// It requres usage of the example driver specific to your platform.
// See the HAL documentation.

#include "bindings/hal_common.h"
#include "bindings/bricklet_ambient_light_v3.h"

#define UID "XYZ" // Change XYZ to the UID of your Ambient Light Bricklet 3.0

void check(int rc, const char* msg);

void example_setup(TF_HalContext *hal);
void example_loop(TF_HalContext *hal);


static TF_AmbientLightV3 al;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_ambient_light_v3_create(&al, UID, hal), "create device object");

	// Get current Illuminance
	uint32_t illuminance;
	check(tf_ambient_light_v3_get_illuminance(&al, &illuminance), "get Illuminance");

	tf_hal_printf("Illuminance: %d 1/%d lx\n", illuminance, 100);
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
