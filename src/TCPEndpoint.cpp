//
// Created by consti10 on 13.04.22.
//

#include "TCPEndpoint.h"
#include <iostream>
#include <boost/asio.hpp>
#include <utility>

void TCPEndpoint::sendMessageToAllClients(MavlinkMessage &message) {

}

void TCPEndpoint::onMessageAnyClient(MavlinkMessage &message) {

}

void TCPEndpoint::loopInfinite() {
    boost::asio::io_service io_service;
    //listen for new connection
    boost::asio::ip::tcp::acceptor acceptor_(io_service, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), 1234 ));
    //socket creation
    boost::asio::ip::tcp::socket socket_(io_service);
    //waiting for connection
    acceptor_.accept(socket_);

    while (true){

    }
    //read operation
    //std::string message = read_(socket_);
    //std::cout << message << endl;
    //write operation
    //send_(socket_, "Hello From Server!");
    //std::cout << "Servent sent Hello message to Client!" << std::endl;
}

void TCPEndpoint::registerCallback(MAV_MSG_CALLBACK cb) {
    this->callback=cb;
}
