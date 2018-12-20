var Tinkerforge = require('tinkerforge');

var HOST = 'localhost';
var PORT = 4223;
var UID = 'XYZ'; // Change XYZ to the UID of your Ambient Light Bricklet 3.0

var ipcon = new Tinkerforge.IPConnection(); // Create IP connection
var al = new Tinkerforge.BrickletAmbientLightV3(UID, ipcon); // Create device object

ipcon.connect(HOST, PORT,
    function (error) {
        console.log('Error: ' + error);
    }
); // Connect to brickd
// Don't use device before ipcon is connected

ipcon.on(Tinkerforge.IPConnection.CALLBACK_CONNECTED,
    function (connectReason) {
        // Configure threshold for illuminance "greater than 500 lx"
        // with a debounce period of 1s (1000ms)
        al.setIlluminanceCallbackConfiguration(1000, false, '>', 500*100, 0);
    }
);

// Register illuminance callback
al.on(Tinkerforge.BrickletAmbientLightV3.CALLBACK_ILLUMINANCE,
    // Callback function for illuminance callback
    function (illuminance) {
        console.log('Illuminance: ' + illuminance/100.0 + ' lx');
        console.log('Too bright, close the curtains!');
    }
);

console.log('Press key to exit');
process.stdin.on('data',
    function (data) {
        ipcon.disconnect();
        process.exit(0);
    }
);
