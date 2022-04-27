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
    wifibroadcastEndpoint=UDPEndpoint::createEndpointForOHDWifibroadcast(false);
    wifibroadcastEndpoint->registerCallback([this](MavlinkMessage& msg){
        onMessageAirPi(msg);
    });
    std::cout<<"Created GroundTelemetry\n";
}

void GroundTelemetry::onMessageAirPi(MavlinkMessage& message) {
    //debugMavlinkMessage(message.m,"GroundTelemetry::onMessageAirPi");
    const mavlink_message_t& m=message.m;
    // we do not need to forward heartbeat messages coming from the air telemetry service
    if(m.msgid==MAVLINK_MSG_ID_HEARTBEAT && m.sysid==OHD_SYS_ID_AIR){
        // heartbeat coming from the air service
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
        // forward to the air pi, which in turn might handle it himself or forward it to the flight controller
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
        std::cout<<"GroundTelemetry::loopInfinite()\n";
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
        auto heartbeat=OHDMessages::createHeartbeat(false);
        sendMessageGroundStationClients(heartbeat);
        // We also broadcast a heartbeat to the air pi, such that it knows the ground service is alive
        sendMessageAirPi(heartbeat);
        auto ohdTelemetryMessages=ohdTelemetryGenerator.generateUpdates();
        for(auto& msg:ohdTelemetryMessages){
            sendMessageGroundStationClients(msg);
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

