WORK IN PROGRESS

sudo apt-get install libboost-all-dev  

and build with cmake

# Developer information
Public connections:

1) There are 2 ways to connect to this Service on the Ground Station (for example QOpenHD)
1.a) UDP via 2 ports (in and out) similar to https://mavlink.io/en/mavgen_c/example_c_udp.html
1.b) TCP on one port (not yet finalized, reconnection and stuff still needs work)