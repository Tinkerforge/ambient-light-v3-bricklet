function matlab_example_threshold()
    import com.tinkerforge.IPConnection;
    import com.tinkerforge.BrickletAmbientLightV3;

    HOST = 'localhost';
    PORT = 4223;
    UID = 'XYZ'; % Change XYZ to the UID of your Ambient Light Bricklet 3.0

    ipcon = IPConnection(); % Create IP connection
    al = handle(BrickletAmbientLightV3(UID, ipcon), 'CallbackProperties'); % Create device object

    ipcon.connect(HOST, PORT); % Connect to brickd
    % Don't use device before ipcon is connected

    % Register illuminance callback to function cb_illuminance
    set(al, 'IlluminanceCallback', @(h, e) cb_illuminance(e));

    % Configure threshold for illuminance "greater than 500 lx"
    % with a debounce period of 1s (1000ms)
    al.setIlluminanceCallbackConfiguration(1000, false, '>', 500*100, 0);

    input('Press key to exit\n', 's');
    ipcon.disconnect();
end

% Callback function for illuminance callback
function cb_illuminance(e)
    fprintf('Illuminance: %g lx\n', e.illuminance/100.0);
    fprintf('Too bright, close the curtains!\n');
end
