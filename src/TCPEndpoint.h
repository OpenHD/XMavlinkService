//
// Created by consti10 on 13.04.22.
//

#ifndef XMAVLINKSERVICE_TCPENDPOINT_H
#define XMAVLINKSERVICE_TCPENDPOINT_H

#include "Helper.hpp"

// Mavlink tcp endpoint (Server)
// Multiple clients can connect to it.
// Supports sending (mavlink) messages to all clients and receiving (mavlink) messages from all clients.
class TCPEndpoint {
public:
    // send message to all connected clients (for example QOpenHD)
    void sendMessageToAllClients(MavlinkMessage& message);
    // called every time a message from any client is received
    void onMessageAnyClient(MavlinkMessage& message);
    // establish a connection to any client who wants to connect
    // process incoming messages
    void loopInfinite();
};


#endif //XMAVLINKSERVICE_TCPENDPOINT_H
