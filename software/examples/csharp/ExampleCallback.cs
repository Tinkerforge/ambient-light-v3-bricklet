using System;
using Tinkerforge;

class Example
{
	private static string HOST = "localhost";
	private static int PORT = 4223;
	private static string UID = "XYZ"; // Change XYZ to the UID of your Ambient Light Bricklet 3.0

	// Callback function for illuminance callback
	static void IlluminanceCB(BrickletAmbientLightV3 sender, long illuminance)
	{
		Console.WriteLine("Illuminance: " + illuminance/100.0 + " lx");
	}

	static void Main()
	{
		IPConnection ipcon = new IPConnection(); // Create IP connection
		BrickletAmbientLightV3 al = new BrickletAmbientLightV3(UID, ipcon); // Create device object

		ipcon.Connect(HOST, PORT); // Connect to brickd
		// Don't use device before ipcon is connected

		// Register illuminance callback to function IlluminanceCB
		al.IlluminanceCallback += IlluminanceCB;

		// Set period for illuminance callback to 1s (1000ms) without a threshold
		al.SetIlluminanceCallbackConfiguration(1000, false, 'x', 0, 0);

		Console.WriteLine("Press enter to exit");
		Console.ReadLine();
		ipcon.Disconnect();
	}
}
