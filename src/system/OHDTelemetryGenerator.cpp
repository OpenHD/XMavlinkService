//
// Created by consti10 on 19.04.22.
//

#include "OHDTelemetryGenerator.h"

OHDTelemetryGenerator::OHDTelemetryGenerator(bool runsOnAir):RUNS_ON_AIR(runsOnAir) {

}

MavlinkMessage OHDTelemetryGenerator::generateUpdate() {
    MavlinkMessage msg;
    const uint8_t sys_id=RUNS_ON_AIR ? OHD_SYS_ID_AIR : OHD_SYS_ID_GROUND;
    mavlink_msg_openhd_system_telemetry_pack(sys_id,MAV_COMP_ID_ALL,&msg.m,10,9,8);
    return msg;
}
