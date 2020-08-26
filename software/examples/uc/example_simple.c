#include "bindings/hal_common.h"
#include "bindings/bricklet_ambient_light_v3.h"

#define UID "XYZ" // Change XYZ to the UID of your Ambient Light Bricklet 3.0

void check(int rc, const char* msg);

TF_AmbientLightV3 al;

void example_setup(TF_HalContext *hal) {
	// Create device object
	check(tf_ambient_light_v3_create(&al, UID, hal), "create device object");

	// Get current Illuminance
	uint32_t illuminance;
	check(tf_ambient_light_v3_get_illuminance(&al, &illuminance), "get Illuminance");

	tf_hal_printf("Illuminance: %d 1/%d lx\n", illuminance, 100.0);
}

void example_loop(TF_HalContext *hal) {
	// Poll for callbacks
	tf_hal_callback_tick(hal, 0);
}
