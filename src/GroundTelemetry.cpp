//
// Created by consti10 on 13.04.22.
//

#include "GroundTelemetry.h"
#include <iostream>
#include "mav_helper.h"

GroundTelemetry::GroundTelemetry() {
    /*tcpGroundCLient=std::make_unique<TCPEndpoint>(OHD_GROUND_CLIENT_TCP_PORT);
    tcpGroundCLient->registerCallback([this](MavlinkMessage& msg){
        onMessageGroundStationClients(msg);
    });*/
    udpGroundClient=std::make_unique<UDPEndpoint>("GroundStationUDP",OHD_GROUND_CLIENT_UDP_PORT_OUT,OHD_GROUND_CLIENT_UDP_PORT_IN);
    udpGroundClient->registerCallback([this](MavlinkMessage& msg){
        onMessageGroundStationClients(msg);
    });
    // hacky, start breoadcasting the existence of the OHD ground station
    // udpGroundClient->startHeartBeat(OHD_SYS_ID_GROUND,0);
    // any message coming in via wifibroadcast is a message from the air pi
    wifibroadcastEndpoint=WBEndpoint::createWbEndpointOHD(false);
    wifibroadcastEndpoint->registerCallback([this](MavlinkMessage& msg){
        onMessageAirPi(msg);
    });
    std::cout<<"Created GroundTelemetry\n";
}

void GroundTelemetry::onMessageAirPi(MavlinkMessage& message) {
    //debugMavlinkMessage(message.m,"GroundTelemetry::onMessageAirPi");
    const auto& msg=message.m;
    // we do not need to forward heartbeat messages coming from the air telemetry service
    if(msg.msgid==MAVLINK_MSG_ID_HEARTBEAT && msg.sysid==OHD_SYS_ID_AIR){
        return;
    }
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
        tcpGroundCLient->sendMessage(message);
    }
    if(udpGroundClient){
        udpGroundClient->sendMessage(message);
    }
}

void GroundTelemetry::sendMessageAirPi(MavlinkMessage& message) {
    // transmit via wifibroadcast
    if(wifibroadcastEndpoint){
        wifibroadcastEndpoint->sendMessage(message);
    }
}

void GroundTelemetry::loopInfinite() {
    while (true){
        // for debugging, check if any of the endpoints is not alive
        if(wifibroadcastEndpoint){
            wifibroadcastEndpoint->debugIfAlive();
        }
        if(udpGroundClient){
            udpGroundClient->debugIfAlive();
        }
        // Broadcast existence of OpenHD ground station to all connected clients
        // (for example QOpenHD)
        // everything else is handled by the callbacks and their threads
        std::this_thread::sleep_for(std::chrono::seconds(3));
        auto heartbeat=OHDMessages::createHeartbeat(false);
        sendMessageGroundStationClients(heartbeat);
        auto ohdTelemetryMessages=ohdTelemetryGenerator.generateUpdates();
        for(auto& msg:ohdTelemetryMessages){
            sendMessageGroundStationClients(msg);
        }
        std::cout<<"GroundTelemetry::loopInfinite()\n";
    }
    /*for(int i=0;i<10000000;i++){
        std::this_thread::sleep_for(std::chrono::seconds(3));
        auto heartbeat=MExampleMessage::heartbeat();
        sendMessageGroundStationClients(heartbeat);
        auto attitude= MExampleMessage::attitude();
        sendMessageGroundStationClients(attitude);
        auto position=MExampleMessage::position();
        sendMessageGroundStationClients(position);
        std::cout<<"X\n";
    }*/
}

