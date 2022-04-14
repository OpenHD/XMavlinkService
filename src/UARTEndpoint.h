//
// Created by consti10 on 13.04.22.
//

#ifndef XMAVLINKSERVICE_UARTENDPOINT_H
#define XMAVLINKSERVICE_UARTENDPOINT_H

#include "Helper.hpp"

// UART endpoint
// Supports sending (mavlink) messages to the connected UART device (aka the flight controller)
// and receiving (mavlink) messages from it

// Should do's
// 1) Handle a disconnecting flight controller: When the flight controller uart for some reason is disconnected,
// try to reconnect
// 2) Handle no flight controller at all: Simple, just do nothing until a flight controller is connected

class UARTEndpoint {
public:
    void sendMessage(const MavlinkMessage& message);
    // called every time this endpoint has received a new message
    void registerCallback(MAV_MSG_CALLBACK cb);
    //
    void loopInfinite();
    void startLoopInfinite();
private:
    void onMessage(MavlinkMessage& message);
    MAV_MSG_CALLBACK callback=nullptr;
};


#endif //XMAVLINKSERVICE_UARTENDPOINT_H
