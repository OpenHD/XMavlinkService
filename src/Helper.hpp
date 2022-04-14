//
// Created by consti10 on 13.04.22.
//

#ifndef XMAVLINKSERVICE_HELPER_H
#define XMAVLINKSERVICE_HELPER_H

#include <functional>

#include "mav_include.h"

struct MavlinkMessage{
    mavlink_message_t m;
    std::vector<uint8_t> pack(){
        std::vector<uint8_t> buf(MAVLINK_MAX_PACKET_LEN);
        auto size = mavlink_msg_to_send_buffer(buf.data(), &m);
        buf.resize(size);
        return buf;
    }
};

// For registering a callback that is called every time component X receives a new Mavlink Message
typedef std::function<void(MavlinkMessage& mavlinkMessage)> MAV_MSG_CALLBACK;

#endif //XMAVLINKSERVICE_HELPER_H
