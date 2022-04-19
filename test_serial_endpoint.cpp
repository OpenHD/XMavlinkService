//
// Created by consti10 on 19.04.22.
// Executable to test the serial endpoint implementation
//

#include <iostream>

#include "src/endpoints/SerialEndpoint.h"

int main() {
    std::cout<< "SerialEndpointTest::start" << std::endl;
    SerialEndpoint serialEndpoint(SerialEndpoint::TEST_SERIAL_PORT);
    serialEndpoint.registerCallback([](MavlinkMessage& msg){
        debugMavlinkMessage(msg.m,"SerialTest");
    });
    // now mavlink messages should come in. Try disconnecting and reconnecting, and see if messages continue
    std::this_thread::sleep_for(std::chrono::minutes (5));
    std::cout<< "SerialEndpointTest::end" << std::endl;
    return 0;
}


