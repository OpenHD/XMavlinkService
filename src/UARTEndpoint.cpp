//
// Created by consti10 on 13.04.22.
//

#include "UARTEndpoint.h"

#include <utility>


void UARTEndpoint::sendMessage(const MavlinkMessage &message) {

}

void UARTEndpoint::onMessage(MavlinkMessage &message) {
    callback(message);
}

void UARTEndpoint::registerCallback(MAV_MSG_CALLBACK cb) {
    this->callback=cb;
}

