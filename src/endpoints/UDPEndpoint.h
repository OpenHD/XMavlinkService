//
// Created by consti10 on 14.04.22.
//

#ifndef XMAVLINKSERVICE_UDPENDPOINT_H
#define XMAVLINKSERVICE_UDPENDPOINT_H

#include "../Helper.hpp"
#include "MEndpoint.hpp"
#include <thread>

// Wraps two UDP ports, one for sending and one for receiving data
// (since TCP and UART for example also allow sending and receiving).
// If this endpoint shall only send data, set the receive port to -1 and never
// call sendMessage
class UDPEndpoint : public MEndpoint{
public:
    UDPEndpoint(const int senderPort,const int receiverPort);
    void sendMessage(const MavlinkMessage& message) override;
private:
    std::unique_ptr<SocketHelper::UDPReceiver> receiver;
    std::unique_ptr<SocketHelper::UDPForwarder> transmitter;
    const int SEND_PORT;
    const int RECV_PORT;
};


#endif //XMAVLINKSERVICE_UDPENDPOINT_H
