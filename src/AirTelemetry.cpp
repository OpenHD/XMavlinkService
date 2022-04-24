//
// Created by consti10 on 13.04.22.
//

#include "AirTelemetry.h"
#include "mav_helper.h"

AirTelemetry::AirTelemetry() {
    serialEndpoint=std::make_unique<SerialEndpoint>("FCSerial",SerialEndpoint::TEST_SERIAL_PORT);
    serialEndpoint->registerCallback([this](MavlinkMessage& msg){
        this->onMessageFC(msg);
    });
    // any message coming in via wifibroadcast is a message from the ground pi
    wifibroadcastEndpoint=WBEndpoint::createWbEndpointOHD(true);
    wifibroadcastEndpoint->registerCallback([this](MavlinkMessage& msg){
        onMessageGroundPi(msg);
    });
    std::cout<<"Created AirTelemetry\n";
}

void AirTelemetry::sendMessageFC(MavlinkMessage& message) {
    serialEndpoint->sendMessage(message);
}

void AirTelemetry::onMessageFC(MavlinkMessage& message) {
    // forward everything to the ground pi
    sendMessageGroundPi(message);
}

void AirTelemetry::sendMessageGroundPi(MavlinkMessage& message) {
    // broadcast the mavlink message via wifibroadcast
    wifibroadcastEndpoint->sendMessage(message);
}

void AirTelemetry::onMessageGroundPi(MavlinkMessage& message) {
    const mavlink_message_t& m=message.m;
    // we do not need to forward heartbeat messages coming from the ground telemetry service
    if(m.msgid==MAVLINK_MSG_ID_HEARTBEAT && m.sysid==OHD_SYS_ID_GROUND){
        return;
    }
    // for now, do it as simple as possible
    sendMessageFC(message);
}

void AirTelemetry::loopInfinite() {
    while (true){
        // for debugging, check if any of the endpoints is not alive
        if(wifibroadcastEndpoint){
            wifibroadcastEndpoint->debugIfAlive();
        }
        if(serialEndpoint){
            serialEndpoint->debugIfAlive();
        }
        // send heartbeat to the ground pi - everything else is handled by the callbacks and their threads
        std::this_thread::sleep_for(std::chrono::seconds(3));
        auto heartbeat=OHDMessages::createHeartbeat(true);
        sendMessageGroundPi(heartbeat);
        auto ohdTelemetry=ohdTelemetryGenerator.generateUpdates();
        //sendMessageGroundPi(ohdTelemetry);
        std::cout<<"AirTelemetry::loopInfinite()\n";
    }
}

