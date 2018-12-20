#!/usr/bin/perl

use strict;
use Tinkerforge::IPConnection;
use Tinkerforge::BrickletAmbientLightV3;

use constant HOST => 'localhost';
use constant PORT => 4223;
use constant UID => 'XYZ'; # Change XYZ to the UID of your Ambient Light Bricklet 3.0

my $ipcon = Tinkerforge::IPConnection->new(); # Create IP connection
my $al = Tinkerforge::BrickletAmbientLightV3->new(&UID, $ipcon); # Create device object

$ipcon->connect(&HOST, &PORT); # Connect to brickd
# Don't use device before ipcon is connected

# Get current Illuminance
my $illuminance = $al->get_illuminance();
print "Illuminance: " . $illuminance/100.0 . " lx\n";

print "Press key to exit\n";
<STDIN>;
$ipcon->disconnect();
