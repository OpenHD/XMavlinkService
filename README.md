WORK IN PROGRESS

sudo apt-get install libboost-all-dev  

and build with cmake

# Developer information

# Does this module need any settings / platform info:
Well, the amount of needed options - so to say - will probably increase with added features.
So far there are:
1) UART -> the module needs to know the (file)-name of the UART for the serial connection to the flight controller,
    as well as the Baud rate, usw.

   
Public connections:

1) There are 2 ways to connect to this Service on the Ground Station (for example QOpenHD)
1.a) UDP via 2 ports (in and out) similar to https://mavlink.io/en/mavgen_c/example_c_udp.html
1.b) TCP on one port (not yet finalized, reconnection and stuff still needs work)