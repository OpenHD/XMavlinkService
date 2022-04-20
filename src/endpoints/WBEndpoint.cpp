//
// Created by consti10 on 14.04.22.
//

#include "WBEndpoint.h"

WBEndpoint::WBEndpoint(const int senderPort,const int receiverPort):SEND_PORT(senderPort),RECV_PORT(receiverPort) {
    std::cout<<"WBEndpoint created\n";
    if(senderPort==receiverPort){
        throw std::runtime_error("WBEndpoint - cannot send and receive on same UDP port\n");
    }
    if(SEND_PORT>=0){
        transmitter=std::make_unique<SocketHelper::UDPForwarder>(SocketHelper::ADDRESS_LOCALHOST,SEND_PORT);
    }
    if(RECV_PORT>=0){
        const auto cb=[this](const uint8_t* payload,const std::size_t payloadSize)mutable {
            this->parseNewData(payload,(int)payloadSize);
        };
        receiver=std::make_unique<SocketHelper::UDPReceiver>(SocketHelper::ADDRESS_LOCALHOST,RECV_PORT,cb);
        receiver->runInBackground();
    }
    std::cout<<"WBEndpoint created send:"<<senderPort<<" recv:"<<receiverPort<<"\n";
}

void WBEndpoint::sendMessage(const MavlinkMessage &message) {
    if(transmitter!= nullptr){
        const auto data=message.pack();
        transmitter->forwardPacketViaUDP(data.data(),data.size());
    }else{
        std::cerr<<"WBEndpoint::sendMessage with no transmitter\n";
    }
}

std::unique_ptr<WBEndpoint> WBEndpoint::createWbEndpointOHD(bool isAir) {
    return std::make_unique<WBEndpoint>(0,1);
}


