Imports System
Imports Tinkerforge

Module ExampleCallback
    Const HOST As String = "localhost"
    Const PORT As Integer = 4223
    Const UID As String = "XYZ" ' Change XYZ to the UID of your Ambient Light Bricklet 3.0

    ' Callback subroutine for illuminance callback
    Sub IlluminanceCB(ByVal sender As BrickletAmbientLightV3, ByVal illuminance As Long)
        Console.WriteLine("Illuminance: " + (illuminance/100.0).ToString() + " lx")
    End Sub

    Sub Main()
        Dim ipcon As New IPConnection() ' Create IP connection
        Dim al As New BrickletAmbientLightV3(UID, ipcon) ' Create device object

        ipcon.Connect(HOST, PORT) ' Connect to brickd
        ' Don't use device before ipcon is connected

        ' Register illuminance callback to subroutine IlluminanceCB
        AddHandler al.IlluminanceCallback, AddressOf IlluminanceCB

        ' Set period for illuminance callback to 1s (1000ms) without a threshold
        al.SetIlluminanceCallbackConfiguration(1000, False, "x"C, 0, 0)

        Console.WriteLine("Press key to exit")
        Console.ReadLine()
        ipcon.Disconnect()
    End Sub
End Module
