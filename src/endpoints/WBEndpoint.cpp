//
// Created by consti10 on 14.04.22.
//

#include "WBEndpoint.h"

WBEndpoint::WBEndpoint(const int txRadioPort,const int rxRadioPort):txRadioPort(txRadioPort),rxRadioPort(rxRadioPort) {
    std::cout<<"WBEndpoint created\n";
    if(txRadioPort==rxRadioPort){
        throw std::runtime_error("WBEndpoint - cannot send and receive on same radio port\n");
    }
    {
        TOptions tOptions{};
        tOptions.keypair=std::nullopt;
        tOptions.fec_k=0;
        tOptions.radio_port=txRadioPort;
        tOptions.wlan="todo";
        RadiotapHeader::UserSelectableParams wifiParams{20, false, 0, false, 1};
        RadiotapHeader radiotapHeader{wifiParams};
        wbTransmitter=std::make_unique<WBTransmitter>(radiotapHeader,tOptions);
        std::cout<<"WBEndpoint created tx:"<<txRadioPort<<" rx:"<<rxRadioPort<<"\n";
    }
    /*{
        ROptions rOptions{};
        rOptions.radio_port=rxRadioPort;
        rOptions.keypair=std::nullopt;
        wbReceiver=std::make_shared<WBReceiver>(rOptions,[this](const uint8_t* payload,const std::size_t payloadSize){
            parseNewData(payload,payloadSize);
        });
        MultiRxPcapReceiver receiver(rxInterfaces,options.radio_port,log_interval,
                                     notstd::bind_front(&WBReceiver::processPacket, agg.get()),
                                     notstd::bind_front(&WBReceiver::dump_stats, agg.get()));
        receiver.loop();
    }*/

}

void WBEndpoint::sendMessage(const MavlinkMessage &message) {
    /*if(transmitter!= nullptr){
        const auto data=message.pack();
        transmitter->forwardPacketViaUDP(data.data(),data.size());
    }else{
        std::cerr<<"WBEndpoint::sendMessage with no transmitter\n";
    }*/
    if(wbTransmitter!= nullptr){
        const auto data=message.pack();
        wbTransmitter->feedPacket(data.data(),data.size());
    }
}

std::unique_ptr<WBEndpoint> WBEndpoint::createWbEndpointOHD(const bool isAir) {
    if(isAir){
        return std::make_unique<WBEndpoint>(OHD_WB_RADIO_PORT_AIR_TO_GROUND,OHD_WB_RADIO_PORT_GROUND_TO_AIR);
    }else{
        return std::make_unique<WBEndpoint>(OHD_WB_RADIO_PORT_GROUND_TO_AIR,OHD_WB_RADIO_PORT_AIR_TO_GROUND);
    }
}


