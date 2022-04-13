//
// Created by consti10 on 13.04.22.
//

#ifndef XMAVLINKSERVICE_HELPER_H
#define XMAVLINKSERVICE_HELPER_H

#include <functional>

struct MavlinkMessage{
    int lol;
};

// For registering a callback that is called every time component X receives a new Message
typedef std::function<void(MavlinkMessage& mavlinkMessage)> MAV_MSG_CALLBACK;

#endif //XMAVLINKSERVICE_HELPER_H
