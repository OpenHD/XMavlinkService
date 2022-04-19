//
// Created by consti10 on 14.04.22.
//

#ifndef XMAVLINKSERVICE_WBENDPOINT_H
#define XMAVLINKSERVICE_WBENDPOINT_H

#include "../Helper.hpp"
#include "MEndpoint.hpp"
#include <thread>

// dummy for now, this is what handles the Wifibroadcast out/in on air or ground pi.
class WBEndpoint :public MEndpoint{
public:
    explicit WBEndpoint(const int senderPort,const int receiverPort);
    void sendMessage(const MavlinkMessage& message) override;
private:
private:
    std::unique_ptr<SocketHelper::UDPReceiver> receiver;
    std::unique_ptr<SocketHelper::UDPForwarder> transmitter;
    const int SEND_PORT;
    const int RECV_PORT;
public:
    // Air sends data to this port, ground receives data on this port
    static constexpr auto OHD_WB_LINK1_PORT=7000;
    // Air receives data on this port, ground sends data on this port
    static constexpr auto OHD_WB_LINK2_PORT=7001;
};


#endif //XMAVLINKSERVICE_WBENDPOINT_H
