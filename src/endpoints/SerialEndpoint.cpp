//
// Created by consti10 on 13.04.22.
//

#include "SerialEndpoint.h"

#include <iostream>
#include <thread>
#include <boost/asio.hpp>
#include <boost/asio/ts/buffer.hpp>
#include <boost/asio/ts/internet.hpp>
#include <boost/thread.hpp>
#include <utility>

#include "../mav_include.h"

SerialEndpoint::SerialEndpoint(std::string serial_port):SERIAL_PORT(std::move(serial_port)),m_serial(io_service){
    //boost::thread t1(&SerialEndpoint::loopInfinite, this);
    std::cout<<"SerialEndpoint created "<<serial_port<<"\n";
}

void SerialEndpoint::loopInfinite() {
    bool opened=false;
    while (!opened){
        try {
            std::cerr << "Opening serial port: " << SERIAL_PORT <<"\n";
            m_serial.open(SERIAL_PORT);
        } catch (boost::system::system_error::exception& e) {
            std::cerr <<"Failed to open serial port \n";
            std::this_thread::sleep_for(RECONNECT_DELAY);
            continue;
        }
        try {
            m_serial.set_option(boost::asio::serial_port_base::baud_rate(BAUD));
            m_serial.set_option(boost::asio::serial_port_base::character_size(8));
            m_serial.set_option(boost::asio::serial_port_base::flow_control(boost::asio::serial_port_base::flow_control::none));
            m_serial.set_option(boost::asio::serial_port_base::parity(boost::asio::serial_port_base::parity::none));
            m_serial.set_option(boost::asio::serial_port_base::stop_bits(boost::asio::serial_port_base::stop_bits::one));
        } catch (boost::system::system_error::exception& e) {
            std::cerr <<"Faild to set serial port baud rate"<<BAUD<<"\n";
            m_serial.close();
            std::this_thread::sleep_for(RECONNECT_DELAY);
            continue;
        }
        std::cout<<"Opened Serial, ready to read or write data\n";
        opened= true;
        startReceive();
    }
}

void SerialEndpoint::startReceive() {
    m_serial.async_read_some(boost::asio::buffer(readBuffer.data(),readBuffer.size()),
                             boost::bind(&SerialEndpoint::handleRead,
                                         this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}

void SerialEndpoint::handleRead(const boost::system::error_code& error,
                                size_t bytes_transferred) {
    if (!error) {
        MEndpoint::parseNewData(readBuffer.data(),bytes_transferred);
        startReceive();
    }else{
        std::cerr<<"SerialEndpoint::handleRead"<<error.message()<<"\n";
    }
}

void SerialEndpoint::handleWrite(const boost::system::error_code& error,
                                 size_t bytes_transferred) {
    if(error){
        std::cerr<<"SerialEndpoint::handleWrite "<<error.message()<<"\n";
    }
}

void SerialEndpoint::sendMessage(const MavlinkMessage &message) {
    if (!m_serial.is_open()) {
        std::cout << "SER: not open\n";
        return;
    }
    const auto packed=message.pack();
    boost::asio::async_write(m_serial,
                             boost::asio::buffer(packed.data(),packed.size()),
                             boost::bind(&SerialEndpoint::handleWrite,
                                         this,
                                         boost::asio::placeholders::error,
                                         boost::asio::placeholders::bytes_transferred));
}




