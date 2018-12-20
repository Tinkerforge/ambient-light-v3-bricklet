#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Ambient Light Bricklet 3.0

# Handle incoming illuminance callbacks
tinkerforge dispatch ambient-light-v3-bricklet $uid illuminance &

# Set period for illuminance callback to 1s (1000ms) without a threshold
tinkerforge call ambient-light-v3-bricklet $uid set-illuminance-callback-configuration 1000 false threshold-option-off 0 0

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
