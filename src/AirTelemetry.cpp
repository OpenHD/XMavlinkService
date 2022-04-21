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
    // for now, forward everything to the flight controller
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
        MavlinkMessage heartbeat;
        mavlink_msg_heartbeat_pack(OHD_SYS_ID_AIR, 1, &heartbeat.m, MAV_TYPE_GENERIC, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
        sendMessageGroundPi(heartbeat);
        auto ohdTelemetry=ohdTelemetryGenerator.generateUpdate();
        sendMessageGroundPi(ohdTelemetry);
        std::cout<<"AirTelemetry::loopInfinite()\n";
    }
}

