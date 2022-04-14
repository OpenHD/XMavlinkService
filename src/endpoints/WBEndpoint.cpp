//
// Created by consti10 on 14.04.22.
//

#include "WBEndpoint.h"

WBEndpoint::WBEndpoint() {
    std::cout<<"WBEndpoint created\n";
}

void WBEndpoint::sendMessage(MavlinkMessage &message) {

}

void WBEndpoint::registerCallback(MAV_MSG_CALLBACK cb) {
    this->callback=std::move(cb);
}


