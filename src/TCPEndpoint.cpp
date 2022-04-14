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

#include "mav_include.h"

void TCPEndpoint::sendMessageToAllClients(MavlinkMessage &message) {
    debugMavlinkMessage(message.m,"TCPEndpoint::send");
    try {
        const auto tmp=message.pack();
        _socket.async_write_some(boost::asio::buffer(tmp.data(),tmp.size()),[this](const boost::system::error_code& error,size_t bytes_transferred){
            std::cout<<"TCP socket write error\n";
        });
    } catch (const std::exception& e) {
        std::cerr << "TCP: catch handle_write error"<<e.what() << std::endl;
    }
    //_socket.write_some(boost::asio::buffer(message.data(),message.data_len()));
}

void TCPEndpoint::onMessageAnyClient(MavlinkMessage &message) {
    debugMavlinkMessage(message.m,"TCPEndpoint::receive");
    if(callback!= nullptr){
        callback(message);
    }
}

void TCPEndpoint::loopInfinite() {
    while (true){
        //listen for new connection
        boost::asio::ip::tcp::acceptor acceptor_(_io_service, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), PORT));
        //waiting for connection
        std::cout<<"Waiting for client to connect\n";
        acceptor_.accept(_socket);
        std::cout<<"Connected\n";
        bool stillConnected= true;
        while (stillConnected){
            std::cout<<"Reading data\n";
            try{
                const auto len=_socket.read_some(boost::asio::buffer(readBuffer, readBuffer.size()));
                if(len>0){
                    parseNewData(readBuffer.data(),len);
                }
            }catch(const std::exception& e){
                std::cout<<"read_some error ?"<<e.what()<<"\n";
                //stillConnected=false;
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        }
    }
    //listen for new connection
    boost::asio::ip::tcp::acceptor acceptor_(_io_service, boost::asio::ip::tcp::endpoint( boost::asio::ip::tcp::v4(), 1234 ));
    //waiting for connection
    acceptor_.accept(_socket);
    std::cout<<"Connected\n";
    while (true){
        std::cout<<"Reading data\n";
        const auto len=_socket.read_some(boost::asio::buffer(readBuffer, readBuffer.size()));
        if(len>0){
            parseNewData(readBuffer.data(),len);
        }
    }
    //read operation
    //std::string message = read_(socket_);
    //std::cout << message << endl;
    //write operation
    //send_(socket_, "Hello From Server!");
    //std::cout << "Servent sent Hello message to Client!" << std::endl;
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

void TCPEndpoint::startLoopInfinite() {
    boost::thread t1(&TCPEndpoint::loopInfinite, this);
    //loopInfinite();
}
