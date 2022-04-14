//
// Created by consti10 on 13.04.22.
//

#ifndef OPENHD_TELEMETRY_GROUNDTELEMETRY_H
#define OPENHD_TELEMETRY_GROUNDTELEMETRY_H

#include "Helper.hpp"
#include "endpoints/TCPEndpoint.h"
#include "endpoints/UDPEndpoint.h"
#include <memory>

class GroundTelemetry {
public:
    explicit GroundTelemetry();
    // called every time a message from the air pi is received
    void onMessageAirPi(MavlinkMessage& message);
    // send a message to the air pi
    void sendMessageAirPi(MavlinkMessage& message);
    // called every time a message is received from any of the clients connected to the Ground Station (For Example QOpenHD)
    void onMessageGroundStationClients(MavlinkMessage& message);
    // send a message to all clients connected to the ground station, for example QOpenHD
    void sendMessageGroundStationClients(MavlinkMessage& message);
public:
    // this is the main entry point for this service - it will run infinitely (until the air unit is either powered down or crashes).
    // This must NEVER crash
    void loopInfinite();
private:
    // This endpoint goes out to the wifibroadcast tx/ rx instances
    //UDPEndpoint wifibroadcastEndpoint{};
    std::unique_ptr<TCPEndpoint> tcpGroundCLient;
    std::unique_ptr<UDPEndpoint> udpGroundClient;
};


#endif //OPENHD_TELEMETRY_GROUNDTELEMETRY_H
