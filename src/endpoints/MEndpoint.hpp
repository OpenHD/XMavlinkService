//
// Created by consti10 on 15.04.22.
//

#ifndef XMAVLINKSERVICE_MENDPOINT_H
#define XMAVLINKSERVICE_MENDPOINT_H

#include "../mav_include.h"
#include <iostream>
#include <chrono>

// Mavlink Endpoint
// A Mavlink endpoint hides away the underlying connection - e.g. UART, TCP, UDP.
// It has a (implementation-specific) method to send a message (sendMessage) and (implementation-specific)
// continuously forwards new incoming messages via a callback.
// It MUST also hide away any problems that could exist with this endpoint - e.g. a disconnecting UART.
// If (for example) in case of UART the connection is lost, it should just try to reconnect
// and as soon as the connection has been re-established, continue working as if nothing happened.
class MEndpoint{
public:
    /**
     * The implementation-specific constructor SHOULD try and establish a connection as soon as possible
     * And re-establish the connection when disconnected.
     * @param tag a tag for debugging.
     */
    explicit MEndpoint(std::string tag="MEndpoint"):TAG(std::move(tag)){};
    /**
     * send a message via this endpoint.
     * If the endpoint is silently disconnected, this MUST NOT FAIL/CRASH
     * @param message the message to send
     */
    virtual void sendMessage(const MavlinkMessage& message)=0;
    /**
     * register a callback that is called every time
     * this endpoint has received a new message
     * @param cb the callback function to register that is then called with a message every time a new full mavlink message has been parsed
     */
    void registerCallback(MAV_MSG_CALLBACK cb){
        if(callback!= nullptr){
            // this might be a common programming mistake - you can only register one callback here
            std::cerr<<"Overwriting already existing callback\n";
        }
        callback=std::move(cb);
    }
    /**
     * If (for some reason) you need to reason if this endpoint is alive, just check if it has received any mavlink messages
     * in the last X seconds
     */
     bool isAlive(){
        return (std::chrono::steady_clock::now()-lastMessage).count()>std::chrono::seconds(5).count();
     }
     /**
      * Start broadcasting a heartbeat in a reqular interval, some endpoints require this, some might not.
      * @param sys_is
      * @param comp_id
      */
     void startHeartBeat(int sys_is,int comp_id){
         this->sys_id=sys_is;
         this->comp_id=comp_id;
         mHeartbeatThread=std::make_unique<std::thread>([this](){
             while (true){
                 std::this_thread::sleep_for(std::chrono::seconds(1));
                 onHeartBeat();
             }
         });
     }
protected:
    MAV_MSG_CALLBACK callback=nullptr;
    // parse new data as it comes in, extract mavlink messages and forward them on the registered callback (if it has been registered)
    void parseNewData(const uint8_t* data, int data_len){
        std::cout<<TAG<<"parseNewData\n";
        mavlink_message_t msg;
        for(int i=0;i<data_len;i++){
            uint8_t res = mavlink_parse_char(MAVLINK_COMM_0, (uint8_t)data[i], &msg, &receiveMavlinkStatus);
            if (res) {
                lastMessage=std::chrono::steady_clock::now();
                MavlinkMessage message{msg};
                debugMavlinkMessage(message.m,TAG.c_str());
                if(callback!= nullptr){
                    callback(message);
                }else{
                    std::cerr<<"No callback set,did you forget to add it ?\n";
                }
            }
        }
    }
private:
    const std::string TAG;
    mavlink_status_t receiveMavlinkStatus{};
    std::chrono::steady_clock::time_point lastMessage;
    int sys_id=0;
    int comp_id=0;
private:
    std::unique_ptr<std::thread> mHeartbeatThread;
    void onHeartBeat(){
        std::cout<<TAG<<" heartbeat\n";
        mavlink_message_t msg;
        // values from QGroundControll
        mavlink_msg_heartbeat_pack(sys_id,comp_id, &msg,MAV_TYPE_GENERIC,            // MAV_TYPE TODO figure out
                                   MAV_AUTOPILOT_INVALID,   // MAV_AUTOPILOT
                                   MAV_MODE_MANUAL_ARMED,   // MAV_MODE
                                   0,                       // custom mode
                                   MAV_STATE_ACTIVE);       // MAV_STATE
        sendMessage({msg});
    }
};

#endif //XMAVLINKSERVICE_MENDPOINT_H
