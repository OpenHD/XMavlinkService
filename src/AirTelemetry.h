//
// Created by consti10 on 13.04.22.
//

#ifndef OPENHD_TELEMETRY_AIRTELEMETRY_H
#define OPENHD_TELEMETRY_AIRTELEMETRY_H

#include "Helper.hpp"
#include "endpoints/SerialEndpoint.h"
#include "endpoints/UDPEndpoint.h"
#include "endpoints/WBEndpoint.h"
#include "system/OHDTelemetryGenerator.h"

/**
 * OpenHD Air telemetry service
 */
class AirTelemetry {
public:
    explicit AirTelemetry();
    // send a mavlink message to the flight controller connected to the air unit via UART
    void sendMessageFC(MavlinkMessage& message);
    // called every time a message from the flight controller bus is received
    void onMessageFC(MavlinkMessage& message);
    // send a message to the ground pi
    void sendMessageGroundPi(MavlinkMessage& message);
    // called every time a message from the ground pi is received
    void onMessageGroundPi(MavlinkMessage& message);
public:
    // this is the main entry point for this service - it will run infinitely (until the air unit is either powered down or crashes).
    // This must NEVER crash
    void loopInfinite();
private:
    std::unique_ptr<SerialEndpoint> serialEndpoint;
    std::unique_ptr<WBEndpoint> wifibroadcastEndpoint;
    OHDTelemetryGenerator ohdTelemetryGenerator{true};
};


#endif //OPENHD_TELEMETRY_AIRTELEMETRY_H
