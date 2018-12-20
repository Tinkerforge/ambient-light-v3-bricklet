#!/usr/bin/env ruby
# -*- ruby encoding: utf-8 -*-

require 'tinkerforge/ip_connection'
require 'tinkerforge/bricklet_ambient_light_v3'

include Tinkerforge

HOST = 'localhost'
PORT = 4223
UID = 'XYZ' # Change XYZ to the UID of your Ambient Light Bricklet 3.0

ipcon = IPConnection.new # Create IP connection
al = BrickletAmbientLightV3.new UID, ipcon # Create device object

ipcon.connect HOST, PORT # Connect to brickd
# Don't use device before ipcon is connected

# Get current Illuminance
illuminance = al.get_illuminance
puts "Illuminance: #{illuminance/100.0} lx"

puts 'Press key to exit'
$stdin.gets
ipcon.disconnect
