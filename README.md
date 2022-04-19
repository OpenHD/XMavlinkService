## WORK IN PROGRESS

# Building
sudo apt-get install libboost-all-dev
and build with cmake

# Developer information - Routing
Routing: I recommend reading this first: https://github.com/mavlink-router/mavlink-router
In generall, this module implements the following 2 basic functionalities:
1) Provide a bidirectional connection from the ground pi directly to the flight controller.
This way the telemetry data from the FC connected to the Air pi makes it via wifibroadcast to the ground pi
and can be distributed to the ground station(s) connected to the ground pi.
Via the ground pi, the ground station(s) connected to the OHD Ground pi can also talk to the FC.
For this, I try to implement it such that the Ground station connected to the Ground Pi doesn't know that OpenHD
is sitting between it and the flight controller - this way applications like QGroundControll (which doesn't know what
OpenHD is) can be seemlessly integrated.

2) Provide a bidirectional connection between the ground pi and the air pi. This way the application connected to the
ground station (like QOpenHD) can receive OpenHD-specific telemetry data (fire and forget) but also can change OHD
Settings.

Using the functionalities above, this module should also handle ALL OpenHD settings with acknowledgements. If necessary,
We can have this module talk to another module (for example a camera/video) module locally via mavlink. However, in my opinion 
we should avoid this as much as possible - one single executable / code base makes development and especially 
debugging much easier.

# Developer information - Running
This module exists of 2 executables - one that runs on the OHD air pi / OHD air unit and one executable that runs on the 
OHD grund pi / OHD ground unit.

# Developer information - External systems:
When you consider this module running on both the air and ground pi, there are only the 2 following external systems it
talks to - The Flight controller (connected to the air pi, connected via UART) and the Ground Station (running or connected
to the ground pi). 


# Does this module need any settings / platform info:
Well, the amount of needed options - so to say - will probably increase with added features.
So far there are:
1) UART -> the module needs to know the (file)-name of the UART for the serial connection to the flight controller,
    as well as the Baud rate, usw.

   
# Connecting the ground pi to the Ground station application (QOpenHD or QGroundControl)
Rn, there is only one way to connect either QOpenHD or QGroundControl to his module running on the ground pi -
a bidirectional connection made up of 2 UDP ports.
TODO: When QOpenHD / QGroundControl is not running on the ground station itself, but rather on another device (for example a
smartphone connected to the ground pi, another difficulty arises from the necessity to route the messages over another
network. For this, we probably should go with TCP, but the TCPEndpoint still needs some work.