//
// Created by consti10 on 14.04.22.
//

#ifndef XMAVLINKSERVICE_WBENDPOINT_H
#define XMAVLINKSERVICE_WBENDPOINT_H

#include "../Helper.hpp"
#include <queue>
#include <vector>
#include <array>
#include <boost/asio.hpp>

// dummy for now, this is what handles the Wifibroadcast out/in
class WBEndpoint {
public:
    explicit WBEndpoint();
    void sendMessage(MavlinkMessage& message);
    void registerCallback(MAV_MSG_CALLBACK cb);
private:
    MAV_MSG_CALLBACK callback= nullptr;
};


#endif //XMAVLINKSERVICE_WBENDPOINT_H
