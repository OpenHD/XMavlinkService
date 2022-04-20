//
// Created by consti10 on 14.04.22.
//

#include "WBEndpoint.h"

WBEndpoint::WBEndpoint(const int txRadioPort,const int rxRadioPort):txRadioPort(txRadioPort),rxRadioPort(rxRadioPort) {
    std::cout<<"WBEndpoint created\n";
    if(txRadioPort==rxRadioPort){
        throw std::runtime_error("WBEndpoint - cannot send and receive on same radio port\n");
    }
    std::cout<<"WBEndpoint created tx:"<<txRadioPort<<" rx:"<<rxRadioPort<<"\n";
}

void WBEndpoint::sendMessage(const MavlinkMessage &message) {
    /*if(transmitter!= nullptr){
        const auto data=message.pack();
        transmitter->forwardPacketViaUDP(data.data(),data.size());
    }else{
        std::cerr<<"WBEndpoint::sendMessage with no transmitter\n";
    }*/
}

std::unique_ptr<WBEndpoint> WBEndpoint::createWbEndpointOHD(const bool isAir) {
    if(isAir){
        return std::make_unique<WBEndpoint>(OHD_WB_RADIO_PORT_AIR_TO_GROUND,OHD_WB_RADIO_PORT_GROUND_TO_AIR);
    }else{
        return std::make_unique<WBEndpoint>(OHD_WB_RADIO_PORT_GROUND_TO_AIR,OHD_WB_RADIO_PORT_AIR_TO_GROUND);
    }
}


