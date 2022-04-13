//
// Created by consti10 on 13.04.22.
//

#ifndef OPENHD_TELEMETRY_GROUNDTELEMETRY_H
#define OPENHD_TELEMETRY_GROUNDTELEMETRY_H

#include "Helper.hpp"

class GroundTelemetry {
public:
    // called every time a message from the air pi is received
    void onMessageAirPi(MavlinkMessage& message);
    // send a message to the air pi
    void sendMessageAirPi(MavlinkMessage& message);
    // send a message to all clients connected to the ground station, for example QOpenHD
    void sendMessageGroundStationClients(MavlinkMessage& message);
public:
    // this is the main entry point for this service - it will run infinitely (until the air unit is either powered down or crashes).
    // This must NEVER crash
    void loopInfinite();
};


#endif //OPENHD_TELEMETRY_GROUNDTELEMETRY_H
