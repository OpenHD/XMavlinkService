//
// Created by consti10 on 13.04.22.
//

#include "GroundTelemetry.h"

void GroundTelemetry::onMessageAirPi(MavlinkMessage& message) {

}

void GroundTelemetry::sendMessageAirPi(MavlinkMessage& message) {

}

void GroundTelemetry::sendMessageGroundStationClients(MavlinkMessage& message) {

}

void GroundTelemetry::loopInfinite() {
    TCPEndpoint tcpEndpoint; // can be QOpenHD, but must not be QOpenHD
    tcpEndpoint.loopInfinite();
}
