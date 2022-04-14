//
// Created by consti10 on 13.04.22.
//

#ifndef XMAVLINKSERVICE_HELPER_H
#define XMAVLINKSERVICE_HELPER_H

#include <functional>

#include "mav_include.h"

struct MavlinkMessage{
    mavlink_message_t m;
    uint8_t* data(){
        return nullptr;
    }
    int data_len(){
        return 0;
    }
};

// For registering a callback that is called every time component X receives a new Mavlink Message
typedef std::function<void(MavlinkMessage& mavlinkMessage)> MAV_MSG_CALLBACK;

#endif //XMAVLINKSERVICE_HELPER_H
