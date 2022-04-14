//
// Created by consti10 on 13.04.22.
//

#include "GroundTelemetry.h"
#include <iostream>

//static constexpr auto OHD_GROUND_CLIENT_TCP_PORT=14445;
static constexpr auto OHD_GROUND_CLIENT_TCP_PORT=1234;
static constexpr auto OHD_GROUND_CLIENT_UDP_PORT_OUT=14550;
static constexpr auto OHD_GROUND_CLIENT_UDP_PORT_IN=14551;

GroundTelemetry::GroundTelemetry() {
    tcpGroundCLient=std::make_unique<TCPEndpoint>(OHD_GROUND_CLIENT_TCP_PORT);
    tcpGroundCLient->registerCallback([this](MavlinkMessage& msg){
        onMessageGroundStationClients(msg);
    });
    udpGroundClient=std::make_unique<UDPEndpoint>(OHD_GROUND_CLIENT_UDP_PORT_OUT,OHD_GROUND_CLIENT_UDP_PORT_IN);
    udpGroundClient->registerCallback([this](MavlinkMessage& msg){
        onMessageGroundStationClients(msg);
    });
    // any message coming in via wifibroadcast is a message from the air pi
    wifibroadcastEndpoint=std::make_unique<WBEndpoint>();
    wifibroadcastEndpoint->registerCallback([this](MavlinkMessage& msg){
        onMessageAirPi(msg);
    });
    std::cout<<"Created GroundTelemetry\n";
}

void GroundTelemetry::onMessageAirPi(MavlinkMessage& message) {
    debugMavlinkMessage(message.m,"GroundTelemetry::onMessageAirPi");
    const auto& msg=message.m;
    /*if(msg.sysid==OHD_SYS_ID_GROUND){
        // handle locally
    }else{
        // forward to the ground clients like QOpenHD
        sendMessageGroundStationClients(message);
    }*/
    // for now, forward everything
    sendMessageGroundStationClients(message);
}

void GroundTelemetry::onMessageGroundStationClients(MavlinkMessage &message) {
    debugMavlinkMessage(message.m,"GroundTelemetry::onMessageGroundStationClients");
    const auto& msg=message.m;
    /*if(msg.sysid==OHD_SYS_ID_GROUND){
        // handle locally
    }else{
        // forward to the air pi, which in turn might handle it himself or forward it to he flight controller
        sendMessageAirPi(message);
    }*/
    // for now, forward everything
    sendMessageAirPi(message);
}


void GroundTelemetry::sendMessageGroundStationClients(MavlinkMessage& message) {
    // forward via TCP or UDP
    if(tcpGroundCLient){
        tcpGroundCLient->sendMessageToAllClients(message);
    }
    if(udpGroundClient){
        udpGroundClient->sendMessage(message);
    }
}

void GroundTelemetry::sendMessageAirPi(MavlinkMessage& message) {
    // transmit via wifibroadcast
    wifibroadcastEndpoint->sendMessage(message);
}

void GroundTelemetry::loopInfinite() {
    for(int i=0;i<10000000;i++){
        std::this_thread::sleep_for(std::chrono::seconds(3));
        auto test= createExampleMessageAttitude();
        sendMessageGroundStationClients(test);
        std::cout<<"X\n";
    }
}

