//
// Created by consti10 on 14.04.22.
//

#include "UDPEndpoint.h"

#include <utility>

void UDPEndpoint::sendMessage(MavlinkMessage &message) {
    debugMavlinkMessage(message.m,"UDPEndpoint::sendMessage");
    if(transmitter!= nullptr){
        const auto data=message.pack();
        transmitter->forwardPacketViaUDP(data.data(),data.size());
    }else{
        std::cerr<<"UDPEndpoint::sendMessage with no transmitter\n";
    }
}

void UDPEndpoint::processData(const uint8_t *data, int data_len) {
    mavlink_message_t msg;
    for(int i=0;i<data_len;i++){
        uint8_t res = mavlink_parse_char(MAVLINK_COMM_0, (uint8_t)data[i], &msg, &receiveMavlinkStatus);
        if (res) {
            debugMavlinkMessage(msg,"UDPEndpoint::processData");
            MavlinkMessage message{msg};
            if(callback!= nullptr){
                callback(message);
            }
        }
    }
}

void UDPEndpoint::registerCallback(MAV_MSG_CALLBACK cb) {
    this->callback=std::move(cb);
}


