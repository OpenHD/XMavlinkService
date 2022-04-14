//
// Created by consti10 on 13.04.22.
//

#ifndef XMAVLINKSERVICE_TCPENDPOINT_H
#define XMAVLINKSERVICE_TCPENDPOINT_H

#include "Helper.hpp"
#include <queue>
#include <vector>
#include <array>
#include <boost/asio.hpp>

// Mavlink tcp endpoint (Server)
// Multiple clients can connect to it.
// Supports sending (mavlink) messages to all clients and receiving (mavlink) messages from all clients.
class TCPEndpoint {
public:
    TCPEndpoint(): _socket(_io_service){};
    // send message to all connected clients (for example QOpenHD)
    void sendMessageToAllClients(MavlinkMessage& message);
    // called every time this endpoint has received a new message
    void registerCallback(MAV_MSG_CALLBACK cb);
    // establish a connection to any client who wants to connect
    // process incoming messages
    void loopInfinite();
private:
    // parse new data as it comes in, extract mavlink messages and forward them on the appropriate callback
    void parseNewData(uint8_t* data, int data_len);
    // called every time a message from any client is received
    void onMessageAnyClient(MavlinkMessage& message);
    MAV_MSG_CALLBACK callback= nullptr;
    mavlink_status_t receiveMavlinkStatus;
    std::array<uint8_t,1024> readBuffer;
    //
    boost::asio::io_service _io_service;
    boost::asio::ip::tcp::socket _socket;
};


#endif //XMAVLINKSERVICE_TCPENDPOINT_H
