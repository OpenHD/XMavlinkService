//
// Created by consti10 on 13.04.22.
//

#include "TCPEndpoint.h"
#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/thread.hpp>
#include <utility>

#include "../mav_include.h"

TCPEndpoint::TCPEndpoint(int Port):PORT(Port), _socket(_io_service){
    std::cout<<"TCPEndpoint created Port:"<<PORT<<"\n";
    boost::thread t1(&TCPEndpoint::loopAllowConnection, this);
};

void TCPEndpoint::loopAllowConnection(){
    //while (true){
        //listen for new connection
        boost::asio::ip::tcp::acceptor acceptor_(_io_service, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), PORT));
        //waiting for connection
        std::cout<<"Waiting for client to connect\n";
        acceptor_.accept(_socket);
        std::cout<<"Connected\n";
        startReceive();
    //}
}

void TCPEndpoint::sendMessageToAllClients(MavlinkMessage &message) {
    debugMavlinkMessage(message.m,"TCPEndpoint::send");
    try {
        if (!_socket.is_open()) {
            std::cout << "Socket not open\n";
            return;
        }
        const auto tmp=message.pack();
        _socket.async_write_some(boost::asio::buffer(tmp.data(),tmp.size()),[this](const boost::system::error_code& error,size_t bytes_transferred){
            std::cout<<"TCP socket write error\n";
        });
    } catch (const std::exception& e) {
        std::cerr << "TCP: catch handle_write error"<<e.what() << std::endl;
    }
    //_socket.write_some(boost::asio::buffer(message.data(),message.data_len()));
}

void TCPEndpoint::startReceive() {
    std::cout<<"start receive\n";
    _socket.async_read_some(boost::asio::buffer(readBuffer.data(),readBuffer.size()),
                             boost::bind(&TCPEndpoint::handleRead,
                                         this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void TCPEndpoint::handleRead(const boost::system::error_code &error, size_t bytes_transferred) {
    if (!error) {
        parseNewData(readBuffer.data(),bytes_transferred);
        startReceive();
    }else{
        std::cerr<<"SerialEndpoint::handleRead"<<error.message()<<"\n";
    }
}

void TCPEndpoint::onMessageAnyClient(MavlinkMessage &message) {
    debugMavlinkMessage(message.m,"TCPEndpoint::receive");
    if(callback!= nullptr){
        callback(message);
    }
}

void TCPEndpoint::registerCallback(MAV_MSG_CALLBACK cb) {
    this->callback=std::move(cb);
}

void TCPEndpoint::parseNewData(uint8_t* data, int data_len) {
    mavlink_message_t msg;
    for(int i=0;i<data_len;i++){
        uint8_t res = mavlink_parse_char(MAVLINK_COMM_0, (uint8_t)data[i], &msg, &receiveMavlinkStatus);
        if (res) {
            debugMavlinkMessage(msg,"TCPEndpoint::receive");
            MavlinkMessage message{msg};
            onMessageAnyClient(message);
        }
    }
}





