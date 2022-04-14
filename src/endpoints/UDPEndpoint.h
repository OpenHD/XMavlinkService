//
// Created by consti10 on 14.04.22.
//

#ifndef XMAVLINKSERVICE_UDPENDPOINT_H
#define XMAVLINKSERVICE_UDPENDPOINT_H

#include "../Helper.hpp"


// Wraps two UDP ports, one for sending and one for receiving data
// (since TCP and UART for example also allow sending and receiving).
// If this endpoint shall only send data, set the receive port to -1 and never
// call sendMessage
class UDPEndpoint {
public:
    UDPEndpoint(const int senderPort,const int receiverPort):SEND_PORT(senderPort),RECV_PORT(receiverPort){
        if(senderPort==receiverPort){
            throw std::runtime_error("UDPEndpoint - cannot send and receive on same UDP port\n");
        }
        if(SEND_PORT>=0){
            transmitter=std::make_unique<SocketHelper::UDPForwarder>(SocketHelper::ADDRESS_LOCALHOST,SEND_PORT);
        }
        if(RECV_PORT>=0){
            const auto cb=[this](const uint8_t* payload,const std::size_t payloadSize)mutable {
                this->processData(payload,(int)payloadSize);
            };
            receiver=std::make_unique<SocketHelper::UDPReceiver>(SocketHelper::ADDRESS_LOCALHOST,RECV_PORT,cb);
            receiver->start();
        }
    }
    void sendMessage(MavlinkMessage& message);
    void registerCallback(MAV_MSG_CALLBACK cb);
private:
    void processData(const uint8_t* data,int data_len);
    std::unique_ptr<SocketHelper::UDPReceiver> receiver;
    std::unique_ptr<SocketHelper::UDPForwarder> transmitter;
    const int SEND_PORT;
    const int RECV_PORT;
    MAV_MSG_CALLBACK callback=nullptr;
    mavlink_status_t receiveMavlinkStatus{};
};


#endif //XMAVLINKSERVICE_UDPENDPOINT_H
