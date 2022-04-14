//
// Created by consti10 on 13.04.22.
//

#ifndef XMAVLINKSERVICE_MAV_INCLUDE_H
#define XMAVLINKSERVICE_MAV_INCLUDE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <common/mavlink.h>
#include <protocol.h>
#include <mavlink_types.h>


#ifdef __cplusplus
}

// OpenHD mavlink sys IDs
static constexpr auto OHD_SYS_ID_GROUND=100;
static constexpr auto OHD_SYS_ID_AIR=101;
static_assert(OHD_SYS_ID_GROUND!=OHD_SYS_ID_AIR);

struct MavlinkMessage{
    mavlink_message_t m{};
    [[nodiscard]] std::vector<uint8_t> pack()const{
        std::vector<uint8_t> buf(MAVLINK_MAX_PACKET_LEN);
        auto size = mavlink_msg_to_send_buffer(buf.data(), &m);
        buf.resize(size);
        return buf;
    }
};

static MavlinkMessage createExampleMessageAttitude(){
    MavlinkMessage msg{};
    mavlink_msg_attitude_pack(0, 0, &msg.m,
            // time_boot_ms Timestamp (milliseconds since system boot)
                              0,
            // roll Roll angle (rad)
                           0.18,
            // pitch Pitch angle (rad)
                              0.3,
            // yaw Yaw angle (rad)
                              0,
            // rollspeed Roll angular speed (rad/s)
                              0,
            // pitchspeed Pitch angular speed (rad/s)
                              0.1,
            // yawspeed Yaw angular speed (rad/s)
                              0);
    return msg;
}

static void debugMavlinkMessage(const mavlink_message_t& msg,const char* TAG){
    printf("%s message with ID %d, sequence: %d from component %d of system %d\n",TAG, msg.msgid, msg.seq, msg.compid, msg.sysid);
}

// For registering a callback that is called every time component X receives a new Mavlink Message
typedef std::function<void(MavlinkMessage& mavlinkMessage)> MAV_MSG_CALLBACK;

#endif // __cplusplus
#endif //XMAVLINKSERVICE_MAV_INCLUDE_H
