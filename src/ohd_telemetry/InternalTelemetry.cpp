//
// Created by consti10 on 19.04.22.
//

#include "InternalTelemetry.h"
#include <iostream>
#include "../../lib/wifibroadcast/src/OpenHDStatisticsWriter.hpp"
#include "SystemReadUtil.hpp"
#include "WBStatisticsConverter.hpp"

InternalTelemetry::InternalTelemetry(bool runsOnAir):RUNS_ON_AIR(runsOnAir),
SYS_ID(runsOnAir ? OHD_SYS_ID_AIR : OHD_SYS_ID_GROUND)
{
    wifibroadcastStatisticsUdpReceiver=std::make_unique<SocketHelper::UDPReceiver>(SocketHelper::ADDRESS_LOCALHOST,OHD_WIFIBROADCAST_STATISTICS_LOCAL_UDP_PORT,[this](const uint8_t* payload,const std::size_t payloadSize){
        processWifibroadcastStatisticsData(payload,payloadSize);
    });
    wifibroadcastStatisticsUdpReceiver->runInBackground();
    logMessagesReceiver=std::make_unique<SocketHelper::UDPReceiver>(SocketHelper::ADDRESS_LOCALHOST,OHD_LOCAL_LOG_MESSAGES_UDP_PORT,[this](const uint8_t* payload,const std::size_t payloadSize){
        processLogMessageData(payload,payloadSize);
    });
    logMessagesReceiver->runInBackground();
}

std::vector<MavlinkMessage> InternalTelemetry::generateUpdates() {
    std::vector<MavlinkMessage> ret;
    ret.push_back(generateSystemTelemetry());
    ret.push_back(generateWifibroadcastStatistics());
    auto logs=generateLogMessages();
    ret.insert(ret.end(),logs.begin(),logs.end());
    return ret;
}

bool InternalTelemetry::handleMavlinkCommandIfPossible(const MavlinkMessage &msg) {
    // regarding reboot: https://mavlink.io/en/messages/common.html#MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN
    //if(msg.m.msgid==MAV_CMD_PREFLIGHT_REBOOT_SHUTDOWN){
    //}
    return false;
}

void InternalTelemetry::processWifibroadcastStatisticsData(const uint8_t* payload,const std::size_t payloadSize) {
    std::cout<<"OHDTelemetryGenerator::processNewWifibroadcastStatisticsMessage: "<<payloadSize<<"\n";
    const auto MSG_SIZE=sizeof(OpenHDStatisticsWriter::Data);
    if(payloadSize >= MSG_SIZE && (payloadSize % MSG_SIZE ==0)){
        // we got new properly aligned data
        OpenHDStatisticsWriter::Data data;
        memcpy((uint8_t*)&data,payload,MSG_SIZE);
        lastWbStatisticsMessage[data.radio_port]=data;
    }else{
        std::cerr<<"Cannot parse WB statistics due to size mismatch\n";
    }
}


MavlinkMessage InternalTelemetry::generateSystemTelemetry() {
    MavlinkMessage msg;
    mavlink_msg_openhd_system_telemetry_pack(SYS_ID,MAV_COMP_ID_ALL,&msg.m,SystemReadUtil::readCpuLoad(),SystemReadUtil::readTemperature(),8);
    return msg;
}

MavlinkMessage InternalTelemetry::generateWifibroadcastStatistics() {
    OpenHDStatisticsWriter::Data data;
    // for now, write some crap
    data.radio_port=0;
    data.count_p_all=3;
    data.count_p_dec_err=4;
    auto msg=WBStatisticsConverter::convertWbStatisticsToMavlink(data,SYS_ID);
    return msg;
}

std::vector<MavlinkMessage> InternalTelemetry::generateLogMessages() {
    std::vector<MavlinkMessage> ret;
    std::lock_guard<std::mutex> guard(bufferedLogMessagesLock);
    while (!bufferedLogMessages.empty()){
        const auto msg = bufferedLogMessages.front();
        if(msg.msg.length()<50){ //49 characters and string terminator
            MavlinkMessage mavMsg;
            mavlink_msg_openhd_log_message_pack(SYS_ID,MAV_COMP_ID_ALL,&mavMsg.m,msg.severity,msg.msg.c_str(),0);
            ret.push_back(mavMsg);
        }
        bufferedLogMessages.pop();
    }
    return ret;
}

void InternalTelemetry::processLogMessageData(const uint8_t* data,std::size_t dataLen) {
    // TODO
}


