#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Ambient Light Bricklet 3.0

# Get current Illuminance
tinkerforge call ambient-light-v3-bricklet $uid get-illuminance
