package main

import (
	"fmt"
	"tinkerforge/ambient_light_v3_bricklet"
	"tinkerforge/ipconnection"
)

const ADDR string = "localhost:4223"
const UID string = "XYZ" // Change XYZ to the UID of your Ambient Light Bricklet 3.0.

func main() {
	ipcon := ipconnection.New()
	defer ipcon.Close()
	al, _ := ambient_light_v3_bricklet.New(UID, &ipcon) // Create device object.

	ipcon.Connect(ADDR) // Connect to brickd.
	defer ipcon.Disconnect()
	// Don't use device before ipcon is connected.

	al.RegisterIlluminanceCallback(func(illuminance uint32) {
		fmt.Printf("Illuminance: %d lx\n", float64(illuminance)/100.0)
	})

	// Set period for illuminance callback to 1s (1000ms) without a threshold.
	al.SetIlluminanceCallbackConfiguration(1000, false, 'x', 0, 0)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
