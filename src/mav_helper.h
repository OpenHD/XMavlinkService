//
// Created by consti10 on 15.04.22.
//

#ifndef XMAVLINKSERVICE_MAV_HELPER_H
#define XMAVLINKSERVICE_MAV_HELPER_H

#include "mav_include.h"
#include <chrono>

namespace MExampleMessage{
    // mostly from https://github.com/mavlink/mavlink/blob/master/examples/linux/mavlink_udp.c
    static uint64_t microsSinceEpoch(){
        return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
    }
    static MavlinkMessage heartbeat(){
        MavlinkMessage msg{};
        mavlink_msg_heartbeat_pack(1, 200, &msg.m, MAV_TYPE_HELICOPTER, MAV_AUTOPILOT_GENERIC, MAV_MODE_GUIDED_ARMED, 0, MAV_STATE_ACTIVE);
        return msg;
    }
    static MavlinkMessage position(){
        MavlinkMessage msg{};
        float position[6] = {};
        mavlink_msg_local_position_ned_pack(1, 200, &msg.m, microsSinceEpoch(),
                                            position[0], position[1], position[2],
                                            position[3], position[4], position[5]);
        return msg;
    }
    static MavlinkMessage attitude(){
        MavlinkMessage msg{};
        mavlink_msg_attitude_pack(1, 200, &msg.m, microsSinceEpoch(), 1.2, 1.7, 3.14, 0.01, 0.02, 0.03);
        return msg;
    }
}


#endif //XMAVLINKSERVICE_MAV_HELPER_H
