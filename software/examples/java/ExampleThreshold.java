import com.tinkerforge.IPConnection;
import com.tinkerforge.BrickletAmbientLightV3;

public class ExampleThreshold {
	private static final String HOST = "localhost";
	private static final int PORT = 4223;

	// Change XYZ to the UID of your Ambient Light Bricklet 3.0
	private static final String UID = "XYZ";

	// Note: To make the example code cleaner we do not handle exceptions. Exceptions
	//       you might normally want to catch are described in the documentation
	public static void main(String args[]) throws Exception {
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletAmbientLightV3 al = new BrickletAmbientLightV3(UID, ipcon); // Create device object

		ipcon.connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Add illuminance listener
		al.addIlluminanceListener(new BrickletAmbientLightV3.IlluminanceListener() {
			public void illuminance(long illuminance) {
				System.out.println("Illuminance: " + illuminance/100.0 + " lx");
				System.out.println("Too bright, close the curtains!");
			}
		});

		// Configure threshold for illuminance "greater than 500 lx"
		// with a debounce period of 1s (1000ms)
		al.setIlluminanceCallbackConfiguration(1000, false, '>', 500*100, 0);

		System.out.println("Press key to exit"); System.in.read();
		ipcon.disconnect();
	}
}
