//
// Created by consti10 on 14.04.22.
//

#ifndef XMAVLINKSERVICE_WBENDPOINT_H
#define XMAVLINKSERVICE_WBENDPOINT_H

#include "Helper.hpp"
#include "MEndpoint.hpp"
#include "wb_include.h"
#include "UDPEndpoint.h"
#include <thread>
#include <memory>

// dummy for now, this is what handles the Wifibroadcast out/in on air or ground pi.
class WBEndpoint :public MEndpoint{
public:
    /**
     * Uses 2 wifibroadcast instances (one for rx, one for tx)
     * to transmit and receive telemetry data.
     * @param txRadioPort the radio port of the tx instance
     * @param rxRadioPort the radio port of the rx instance.
     */
    explicit WBEndpoint(int txRadioPort,int rxRadioPort);
    void sendMessage(const MavlinkMessage& message) override;
private:
    const int txRadioPort;
    const int rxRadioPort;
    std::unique_ptr<WBTransmitter> wbTransmitter;
    std::unique_ptr<WBReceiver> wbReceiver;
    std::unique_ptr<std::thread> receiverThread;
    // For debugging without a wifi card, I use UDPEndpoint as a alternative
    // to wifibroadcast.
    std::unique_ptr<UDPEndpoint> emulatWifibroadcastUdpEndpoint;
public:
    // Air sends data to this port, ground receives data on this port
    //static constexpr auto OHD_WB_LINK1_PORT=7000;
    // Air receives data on this port, ground sends data on this port
    //static constexpr auto OHD_WB_LINK2_PORT=7001;
public:
    // the link id for data from air to ground
    static constexpr int OHD_WB_RADIO_PORT_AIR_TO_GROUND=10;
    // same for ground to air
    static constexpr int OHD_WB_RADIO_PORT_GROUND_TO_AIR=11;
    static std::unique_ptr<WBEndpoint> createWbEndpointOHD(bool isAir);
};


#endif //XMAVLINKSERVICE_WBENDPOINT_H
