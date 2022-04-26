//
// Created by consti10 on 19.04.22.
//

#ifndef XMAVLINKSERVICE_INTERNALTELEMETRY_H
#define XMAVLINKSERVICE_INTERNALTELEMETRY_H

#include "../mav_helper.h"
#include "SocketHelper.hpp"
#include "../../lib/wifibroadcast/src/OpenHDStatisticsWriter.hpp"
#include <map>
#include <vector>

// The purpose of this class is to generate all the OpenHD specific telemetry that can be sent
// in a fire and forget manner, as well as handling commands without side effects.
// For example, to report the CPU usage on the air station,
// one can read out the cpu usage in regular intervals and send it out (perhaps together with other
// telemetry values)
// TODO please add more documented ! code here for usefully telemetry data.
class InternalTelemetry {
public:
    explicit InternalTelemetry(bool runsOnAir=false);
    /**
     * generate all the OHD fire and forget telemetry data
     * should be called in regular intervals.
     * @return all the generated OHD mavlink messages
     */
    std::vector<MavlinkMessage> generateUpdates();
    /**
     * Check if the mavlink command can be handled by this module,
     * if yes, consume the command and return true
     * otherwise, return false - the command must then be for another module.
     * @return true if the command has been consumed, false otherwise
     */
    bool handleMavlinkCommandIfPossible(const MavlinkMessage& msg);
private:
    const bool RUNS_ON_AIR;
    // by the sys id QGroundControl knows if this message is telemetry data from the air pi or ground pi.
    // just for convenience, the RUNS_ON_AIR variable determines the sys id.
    const uint8_t SYS_ID;
    // Here all the wb rx instance(s) send their statistics to.
    std::unique_ptr<SocketHelper::UDPReceiver> wifibroadcastStatisticsUdpReceiver;
    // for each unique stream ID, store the last received statistics message.
    // Probably best to go for a write - read, since we don't want to perform any
    // dangerous work on the main service thread.
    std::map<uint8_t ,OpenHDStatisticsWriter::Data> lastWbStatisticsMessage;
    /**
     * Called with the raw Wifibroadcast statistics data from UDP
     */
    void processWifibroadcastStatisticsData(const uint8_t* payload,std::size_t payloadSize);
    MavlinkMessage generateSystemTelemetry();
    MavlinkMessage generateWifibroadcastStatistics();
};


#endif //XMAVLINKSERVICE_INTERNALTELEMETRY_H
