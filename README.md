# CreeperBot

This is a little remote telepresence robot based on Thingiverse 63165 (http://www.thingiverse.com/thing:63165)

I modified the main body slightly to accomodate larger free rotation servos I had.

I also added a Creeper face with LED eyes and mount for an iPhone 4

This was build as an example in a talk I did for Montreal.rb

# FaceTime AutoAnswer

Unfortunatly there is no way to get FaceTime to auto-answer without Jailbreaking the phone.

Once Jailbroken, simply install the Cydia app called "FaceTime Surveillance"

# Network

As the Arduino does not support HTTPS or any type of security it is not advisable to connect it directly to the internet (unless you make firewall based restrictions).

Therefore a RaspberryPi is put in the mix to provide an abstraction layer

Internet <-----> RaspberryPi <---wifi---> Arduino
