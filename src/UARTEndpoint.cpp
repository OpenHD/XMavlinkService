//
// Created by consti10 on 13.04.22.
//

#include "UARTEndpoint.h"

#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/thread.hpp>
#include <utility>

#include "mav_include.h"


void UARTEndpoint::sendMessage(const MavlinkMessage &message) {

}

void UARTEndpoint::onMessage(MavlinkMessage &message) {
    callback(message);
}

void UARTEndpoint::registerCallback(MAV_MSG_CALLBACK cb) {
    this->callback=cb;
}

void UARTEndpoint::loopInfinite() {

}

void UARTEndpoint::startLoopInfinite() {
    boost::thread t1(&UARTEndpoint::loopInfinite, this);
}

