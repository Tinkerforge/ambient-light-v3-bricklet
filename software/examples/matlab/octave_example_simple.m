function octave_example_simple()
    more off;

    HOST = "localhost";
    PORT = 4223;
    UID = "XYZ"; % Change XYZ to the UID of your Ambient Light Bricklet 3.0

    ipcon = javaObject("com.tinkerforge.IPConnection"); % Create IP connection
    al = javaObject("com.tinkerforge.BrickletAmbientLightV3", UID, ipcon); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Get current Illuminance
    illuminance = al.getIlluminance();
    fprintf("Illuminance: %g lx\n", java2int(illuminance)/100.0);

    input("Press key to exit\n", "s");
    ipcon.disconnect();
end

function int = java2int(value)
    if compare_versions(version(), "3.8", "<=")
        int = value.intValue();
    else
        int = value;
    end
end
