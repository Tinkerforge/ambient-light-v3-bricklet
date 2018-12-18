package main

import (
	"fmt"
	"github.com/Tinkerforge/go-api-bindings/ambient_light_v3_bricklet"
	"github.com/Tinkerforge/go-api-bindings/ipconnection"
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

	// Get current Illuminance.
	illuminance, _ := al.GetIlluminance()
	fmt.Printf("Illuminance: %f lx\n", float64(illuminance)/100.0)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
