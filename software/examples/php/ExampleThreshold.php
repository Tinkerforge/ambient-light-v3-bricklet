<?php

require_once('Tinkerforge/IPConnection.php');
require_once('Tinkerforge/BrickletAmbientLightV3.php');

use Tinkerforge\IPConnection;
use Tinkerforge\BrickletAmbientLightV3;

const HOST = 'localhost';
const PORT = 4223;
const UID = 'XYZ'; // Change XYZ to the UID of your Ambient Light Bricklet 3.0

// Callback function for illuminance callback
function cb_illuminance($illuminance)
{
    echo "Illuminance: " . $illuminance/100.0 . " lx\n";
    echo "Too bright, close the curtains!\n";
}

$ipcon = new IPConnection(); // Create IP connection
$al = new BrickletAmbientLightV3(UID, $ipcon); // Create device object

$ipcon->connect(HOST, PORT); // Connect to brickd
// Don't use device before ipcon is connected

// Register illuminance callback to function cb_illuminance
$al->registerCallback(BrickletAmbientLightV3::CALLBACK_ILLUMINANCE, 'cb_illuminance');

// Configure threshold for illuminance "greater than 500 lx"
// with a debounce period of 1s (1000ms)
$al->setIlluminanceCallbackConfiguration(1000, FALSE, '>', 500*100, 0);

echo "Press ctrl+c to exit\n";
$ipcon->dispatchCallbacks(-1); // Dispatch callbacks forever

?>
