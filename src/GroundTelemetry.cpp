//
// Created by consti10 on 13.04.22.
//

#include "GroundTelemetry.h"
#include <iostream>

void GroundTelemetry::onMessageAirPi(MavlinkMessage& message) {
    debugMavlinkMessage(message.m,"GroundTelemetry::onMessageAirPi");
    const auto& msg=message.m;
    /*if(msg.sysid==OHD_SYS_ID_GROUND){
        // handle locally
    }else{
        // forward to the ground clients like QOpenHD
        sendMessageGroundStationClients(message);
    }*/
    // for now, forward everything
    sendMessageGroundStationClients(message);
}

void GroundTelemetry::onMessageGroundStationClients(MavlinkMessage &message) {
    debugMavlinkMessage(message.m,"GroundTelemetry::onMessageGroundStationClients");
    const auto& msg=message.m;
    /*if(msg.sysid==OHD_SYS_ID_GROUND){
        // handle locally
    }else{
        // forward to the air pi, which in turn might handle it himself or forward it to he flight controller
        sendMessageAirPi(message);
    }*/
    // for now, forward everything
    sendMessageAirPi(message);
}


void GroundTelemetry::sendMessageGroundStationClients(MavlinkMessage& message) {
    // forward via TCP or UDP
}

void GroundTelemetry::sendMessageAirPi(MavlinkMessage& message) {
    // transmit via wifibroadcast
}

void GroundTelemetry::loopInfinite() {
    /*TCPEndpoint tcpEndpoint; // can be QOpenHD, but must not be QOpenHD
    tcpEndpoint.startLoopInfinite();
    for(int i=0;i<100;i++){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        auto test= createExampleMessageAttitude();
        tcpEndpoint.sendMessageToAllClients(test);
    }*/
}
