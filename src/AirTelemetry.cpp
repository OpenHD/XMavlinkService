//
// Created by consti10 on 13.04.22.
//

#include "AirTelemetry.h"

void AirTelemetry::sendMessageFC(MavlinkMessage& message) {

}

void AirTelemetry::onMessageFC(MavlinkMessage& message) {

}

void AirTelemetry::sendMessageGroundPi(MavlinkMessage& message) {

}

void AirTelemetry::onMessageGroundPi(MavlinkMessage& message) {

}

void AirTelemetry::loopInfinite() {
    SerialEndpoint serialEndpoint("/dev/ttyUSB0");
    serialEndpoint.registerCallback([this](MavlinkMessage& msg){
        this->onMessageFC(msg);
    });
    serialEndpoint.loopInfinite();
}
