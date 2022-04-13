//
// Created by consti10 on 13.04.22.
//

#ifndef XMAVLINKSERVICE_UARTENDPOINT_H
#define XMAVLINKSERVICE_UARTENDPOINT_H

#include "Helper.hpp"

// UART endpoint
// Supports sending (mavlink) messages to the connected UART device (aka the flight controller)
// and receiving (mavlink) messages from it
class UARTEndpoint {
public:
    void onMessage(MavlinkMessage& message);
    void sendMessage(const MavlinkMessage& message);
};


#endif //XMAVLINKSERVICE_UARTENDPOINT_H
