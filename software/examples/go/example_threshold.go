package main

import (
	"fmt"
	"github.com/tinkerforge/go-api-bindings/ambient_light_v3_bricklet"
	"github.com/tinkerforge/go-api-bindings/ipconnection"
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
		fmt.Printf("Illuminance: %f lx\n", float64(illuminance)/100.0)
		fmt.Println("Too bright, close the curtains!")
	})

	// Configure threshold for illuminance "greater than 500 lx"
	// with a debounce period of 1s (1000ms).
	al.SetIlluminanceCallbackConfiguration(1000, false, '>', 500*100, 0)

	fmt.Print("Press enter to exit.")
	fmt.Scanln()

}
