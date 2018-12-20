#!/bin/sh
# Connects to localhost:4223 by default, use --host and --port to change this

uid=XYZ # Change XYZ to the UID of your Ambient Light Bricklet 3.0

# Handle incoming illuminance callbacks
tinkerforge dispatch ambient-light-v3-bricklet $uid illuminance\
 --execute "echo Illuminance: {illuminance}/100 lx. Too bright, close the curtains!" &

# Configure threshold for illuminance "greater than 500 lx"
# with a debounce period of 1s (1000ms)
tinkerforge call ambient-light-v3-bricklet $uid set-illuminance-callback-configuration 1000 false threshold-option-greater 50000 0

echo "Press key to exit"; read dummy

kill -- -$$ # Stop callback dispatch in background
