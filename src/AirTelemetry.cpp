//
// Created by consti10 on 13.04.22.
//

#include "AirTelemetry.h"

AirTelemetry::AirTelemetry() {
    serialEndpoint=std::make_unique<SerialEndpoint>(SerialEndpoint::USB_SERIAL_PORT);
    serialEndpoint->registerCallback([this](MavlinkMessage& msg){
        this->onMessageFC(msg);
    });
    // any message coming in via wifibroadcast is a message from the ground pi
    wifibroadcastEndpoint=std::make_unique<WBEndpoint>();
    wifibroadcastEndpoint->registerCallback([this](MavlinkMessage& msg){
        onMessageGroundPi(msg);
    });
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
    for(int i=0;i<10000000;i++){
        std::this_thread::sleep_for(std::chrono::seconds(3));
        auto test= createExampleMessageAttitude();
        onMessageFC(test);
    }
}

