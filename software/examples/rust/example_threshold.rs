use std::{error::Error, io, thread};
use tinkerforge::{ambient_light_v3_bricklet::*, ip_connection::IpConnection};

const HOST: &str = "localhost";
const PORT: u16 = 4223;
const UID: &str = "XYZ"; // Change XYZ to the UID of your Ambient Light Bricklet 3.0.

fn main() -> Result<(), Box<dyn Error>> {
    let ipcon = IpConnection::new(); // Create IP connection.
    let al = AmbientLightV3Bricklet::new(UID, &ipcon); // Create device object.

    ipcon.connect((HOST, PORT)).recv()??; // Connect to brickd.
                                          // Don't use device before ipcon is connected.

    let illuminance_receiver = al.get_illuminance_callback_receiver();

    // Spawn thread to handle received callback messages.
    // This thread ends when the `al` object
    // is dropped, so there is no need for manual cleanup.
    thread::spawn(move || {
        for illuminance in illuminance_receiver {
            println!("Illuminance: {} lx", illuminance as f32 / 100.0);
            println!("Too bright, close the curtains!");
        }
    });

    // Configure threshold for illuminance "greater than 500 lx"
    // with a debounce period of 1s (1000ms).
    al.set_illuminance_callback_configuration(1000, false, '>', 500 * 100, 0);

    println!("Press enter to exit.");
    let mut _input = String::new();
    io::stdin().read_line(&mut _input)?;
    ipcon.disconnect();
    Ok(())
}
