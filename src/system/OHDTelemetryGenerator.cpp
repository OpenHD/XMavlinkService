//
// Created by consti10 on 19.04.22.
//

#include "OHDTelemetryGenerator.h"
#include <iostream>
#include "../../lib/wifibroadcast/src/OpenHDStatisticsWriter.hpp"

// from https://github.com/OpenHD/Open.HD/blob/35b6b10fbeda43cd06bbfbd90e2daf29629c2f8a/openhd-status/src/statusmicroservice.cpp#L173
// Return the CPU load of the system the generator is running on
// Unit: Percentage ?
static int readCpuLoad(){
    int cpuload_gnd=0;
    long double a[4];
    FILE *fp;
    try {
        fp = fopen("/proc/stat", "r");
        fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &a[0], &a[1], &a[2], &a[3]);
    } catch (...){
        std::cerr << "ERROR: proc reading1" << std::endl;
        return -1;
    }
    fclose(fp);
    cpuload_gnd = (a[0] + a[1] + a[2]) / (a[0] + a[1] + a[2] + a[3]) * 100;
    return cpuload_gnd;
}

// from https://github.com/OpenHD/Open.HD/blob/35b6b10fbeda43cd06bbfbd90e2daf29629c2f8a/openhd-status/src/statusmicroservice.cpp#L165
// Return the CPU/SOC temperature of the system the generator is running on
// Unit: Degree ?
static int readTemperature(){
    int cpu_temperature = 0;
    FILE *fp;
    try {
        fp = fopen("/sys/class/thermal/thermal_zone0/temp", "r");
        fscanf(fp, "%d", &cpu_temperature);
    } catch (...){
        std::cerr << "ERROR: thermal reading" << std::endl;
        return -1;
    }
    fclose(fp);
    cpu_temperature= cpu_temperature / 1000;
    return cpu_temperature;
}

static MavlinkMessage convertWbStatisticsToMavlink(const OpenHDStatisticsWriter::Data& data,const uint8_t sys_id){
    MavlinkMessage msg;
    mavlink_msg_openhd_wifibroadcast_statistics_pack(sys_id,MAV_COMP_ID_ALL,&msg.m,data.radio_port,data.count_p_all,data.count_p_bad,data.count_p_dec_ok,
                                                     data.count_p_dec_ok,data.count_p_fec_recovered,data.count_p_lost);
    return msg;
}

// TODO please add more documented ! code here for usefully telemetry data.

OHDTelemetryGenerator::OHDTelemetryGenerator(bool runsOnAir):RUNS_ON_AIR(runsOnAir),
SYS_ID(runsOnAir ? OHD_SYS_ID_AIR : OHD_SYS_ID_GROUND)
{
    wifibroadcastStatisticsUdpReceiver=std::make_unique<SocketHelper::UDPReceiver>(SocketHelper::ADDRESS_LOCALHOST,OHD_WIFIBROADCAST_STATISTICS_LOCAL_UDP_PORT,[this](const uint8_t* payload,const std::size_t payloadSize){
        processWifibroadcastStatisticsData(payload,payloadSize);
    });
    wifibroadcastStatisticsUdpReceiver->runInBackground();
}

void OHDTelemetryGenerator::processWifibroadcastStatisticsData(const uint8_t* payload,const std::size_t payloadSize) {
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


MavlinkMessage OHDTelemetryGenerator::generateSystemTelemetry() {
    MavlinkMessage msg;
    mavlink_msg_openhd_system_telemetry_pack(SYS_ID,MAV_COMP_ID_ALL,&msg.m,readCpuLoad(),readTemperature(),8);
    return msg;
}

MavlinkMessage OHDTelemetryGenerator::generateWifibroadcastStatistics() {
    OpenHDStatisticsWriter::Data data;
    // for now, write some crap
    data.radio_port=0;
    data.count_p_all=3;
    data.count_p_dec_err=4;
    auto msg=convertWbStatisticsToMavlink(data,SYS_ID);
    return msg;
}

MavlinkMessage OHDTelemetryGenerator::generateUpdate() {
    return generateSystemTelemetry();
}

