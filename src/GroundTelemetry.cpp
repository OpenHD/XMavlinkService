//
// Created by consti10 on 13.04.22.
//

#include "GroundTelemetry.h"
#include <iostream>

void GroundTelemetry::onMessageAirPi(MavlinkMessage& message) {

}

void GroundTelemetry::sendMessageAirPi(MavlinkMessage& message) {

}

void GroundTelemetry::sendMessageGroundStationClients(MavlinkMessage& message) {

}

void GroundTelemetry::loopInfinite() {
    TCPEndpoint tcpEndpoint; // can be QOpenHD, but must not be QOpenHD
    tcpEndpoint.startLoopInfinite();
    for(int i=0;i<100;i++){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto test=createExampleMessage();
        tcpEndpoint.sendMessageToAllClients(test);
        std::cout<<"Sent message\n";
    }
}
