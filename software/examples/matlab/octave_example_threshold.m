function octave_example_threshold()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Ambient Light Bricklet 3.0

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    al = javaObject("com.tinkerforge.BrickletAmbientLightV3", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register illuminance callback to function cb_illuminance
    al.addIlluminanceCallback(@cb_illuminance);

    % Configure threshold for illuminance "greater than 500 lx"
    % with a debounce period of 1s (1000ms)
    al.setIlluminanceCallbackConfiguration(1000, false, ">", 500*100, 0);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

% Callback function for illuminance callback
function cb_illuminance(e)
    fprintf("Illuminance: %g lx\n", java2int(e.illuminance)/100.0);
    fprintf("Too bright, close the curtains!\n");
end

function int = java2int(value)
    if compare_versions(version(), "3.8", "<=")
        int = value.intValue();
    else
        int = value;
    end
end
