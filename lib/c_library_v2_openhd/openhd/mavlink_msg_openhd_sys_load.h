#pragma once
// MESSAGE OPENHD_SYS_LOAD PACKING

#define MAVLINK_MSG_ID_OPENHD_SYS_LOAD 1230


typedef struct __mavlink_openhd_sys_load_t {
 uint8_t target_system; /*<  system id of the requesting system*/
 uint8_t target_component; /*<  component id of the requesting component*/
 uint8_t cpuload; /*<  cpuload*/
 uint8_t temp; /*<  temp*/
} mavlink_openhd_sys_load_t;

#define MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN 4
#define MAVLINK_MSG_ID_OPENHD_SYS_LOAD_MIN_LEN 4
#define MAVLINK_MSG_ID_1230_LEN 4
#define MAVLINK_MSG_ID_1230_MIN_LEN 4

#define MAVLINK_MSG_ID_OPENHD_SYS_LOAD_CRC 26
#define MAVLINK_MSG_ID_1230_CRC 26



#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_OPENHD_SYS_LOAD { \
    1230, \
    "OPENHD_SYS_LOAD", \
    4, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_openhd_sys_load_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_openhd_sys_load_t, target_component) }, \
         { "cpuload", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_openhd_sys_load_t, cpuload) }, \
         { "temp", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_openhd_sys_load_t, temp) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_OPENHD_SYS_LOAD { \
    "OPENHD_SYS_LOAD", \
    4, \
    {  { "target_system", NULL, MAVLINK_TYPE_UINT8_T, 0, 0, offsetof(mavlink_openhd_sys_load_t, target_system) }, \
         { "target_component", NULL, MAVLINK_TYPE_UINT8_T, 0, 1, offsetof(mavlink_openhd_sys_load_t, target_component) }, \
         { "cpuload", NULL, MAVLINK_TYPE_UINT8_T, 0, 2, offsetof(mavlink_openhd_sys_load_t, cpuload) }, \
         { "temp", NULL, MAVLINK_TYPE_UINT8_T, 0, 3, offsetof(mavlink_openhd_sys_load_t, temp) }, \
         } \
}
#endif

/**
 * @brief Pack a openhd_sys_load message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param target_system  system id of the requesting system
 * @param target_component  component id of the requesting component
 * @param cpuload  cpuload
 * @param temp  temp
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_openhd_sys_load_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               uint8_t target_system, uint8_t target_component, uint8_t cpuload, uint8_t temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, cpuload);
    _mav_put_uint8_t(buf, 3, temp);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN);
#else
    mavlink_openhd_sys_load_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.cpuload = cpuload;
    packet.temp = temp;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_OPENHD_SYS_LOAD;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_MIN_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_CRC);
}

/**
 * @brief Pack a openhd_sys_load message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param target_system  system id of the requesting system
 * @param target_component  component id of the requesting component
 * @param cpuload  cpuload
 * @param temp  temp
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_openhd_sys_load_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   uint8_t target_system,uint8_t target_component,uint8_t cpuload,uint8_t temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, cpuload);
    _mav_put_uint8_t(buf, 3, temp);

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN);
#else
    mavlink_openhd_sys_load_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.cpuload = cpuload;
    packet.temp = temp;

        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_OPENHD_SYS_LOAD;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_MIN_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_CRC);
}

/**
 * @brief Encode a openhd_sys_load struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param openhd_sys_load C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_openhd_sys_load_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_openhd_sys_load_t* openhd_sys_load)
{
    return mavlink_msg_openhd_sys_load_pack(system_id, component_id, msg, openhd_sys_load->target_system, openhd_sys_load->target_component, openhd_sys_load->cpuload, openhd_sys_load->temp);
}

/**
 * @brief Encode a openhd_sys_load struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param openhd_sys_load C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_openhd_sys_load_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_openhd_sys_load_t* openhd_sys_load)
{
    return mavlink_msg_openhd_sys_load_pack_chan(system_id, component_id, chan, msg, openhd_sys_load->target_system, openhd_sys_load->target_component, openhd_sys_load->cpuload, openhd_sys_load->temp);
}

/**
 * @brief Send a openhd_sys_load message
 * @param chan MAVLink channel to send the message
 *
 * @param target_system  system id of the requesting system
 * @param target_component  component id of the requesting component
 * @param cpuload  cpuload
 * @param temp  temp
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_openhd_sys_load_send(mavlink_channel_t chan, uint8_t target_system, uint8_t target_component, uint8_t cpuload, uint8_t temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN];
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, cpuload);
    _mav_put_uint8_t(buf, 3, temp);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPENHD_SYS_LOAD, buf, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_MIN_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_CRC);
#else
    mavlink_openhd_sys_load_t packet;
    packet.target_system = target_system;
    packet.target_component = target_component;
    packet.cpuload = cpuload;
    packet.temp = temp;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPENHD_SYS_LOAD, (const char *)&packet, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_MIN_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_CRC);
#endif
}

/**
 * @brief Send a openhd_sys_load message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_openhd_sys_load_send_struct(mavlink_channel_t chan, const mavlink_openhd_sys_load_t* openhd_sys_load)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_openhd_sys_load_send(chan, openhd_sys_load->target_system, openhd_sys_load->target_component, openhd_sys_load->cpuload, openhd_sys_load->temp);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPENHD_SYS_LOAD, (const char *)openhd_sys_load, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_MIN_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_CRC);
#endif
}

#if MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_openhd_sys_load_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  uint8_t target_system, uint8_t target_component, uint8_t cpuload, uint8_t temp)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;
    _mav_put_uint8_t(buf, 0, target_system);
    _mav_put_uint8_t(buf, 1, target_component);
    _mav_put_uint8_t(buf, 2, cpuload);
    _mav_put_uint8_t(buf, 3, temp);

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPENHD_SYS_LOAD, buf, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_MIN_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_CRC);
#else
    mavlink_openhd_sys_load_t *packet = (mavlink_openhd_sys_load_t *)msgbuf;
    packet->target_system = target_system;
    packet->target_component = target_component;
    packet->cpuload = cpuload;
    packet->temp = temp;

    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPENHD_SYS_LOAD, (const char *)packet, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_MIN_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_CRC);
#endif
}
#endif

#endif

// MESSAGE OPENHD_SYS_LOAD UNPACKING


/**
 * @brief Get field target_system from openhd_sys_load message
 *
 * @return  system id of the requesting system
 */
static inline uint8_t mavlink_msg_openhd_sys_load_get_target_system(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  0);
}

/**
 * @brief Get field target_component from openhd_sys_load message
 *
 * @return  component id of the requesting component
 */
static inline uint8_t mavlink_msg_openhd_sys_load_get_target_component(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  1);
}

/**
 * @brief Get field cpuload from openhd_sys_load message
 *
 * @return  cpuload
 */
static inline uint8_t mavlink_msg_openhd_sys_load_get_cpuload(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  2);
}

/**
 * @brief Get field temp from openhd_sys_load message
 *
 * @return  temp
 */
static inline uint8_t mavlink_msg_openhd_sys_load_get_temp(const mavlink_message_t* msg)
{
    return _MAV_RETURN_uint8_t(msg,  3);
}

/**
 * @brief Decode a openhd_sys_load message into a struct
 *
 * @param msg The message to decode
 * @param openhd_sys_load C-struct to decode the message contents into
 */
static inline void mavlink_msg_openhd_sys_load_decode(const mavlink_message_t* msg, mavlink_openhd_sys_load_t* openhd_sys_load)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    openhd_sys_load->target_system = mavlink_msg_openhd_sys_load_get_target_system(msg);
    openhd_sys_load->target_component = mavlink_msg_openhd_sys_load_get_target_component(msg);
    openhd_sys_load->cpuload = mavlink_msg_openhd_sys_load_get_cpuload(msg);
    openhd_sys_load->temp = mavlink_msg_openhd_sys_load_get_temp(msg);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN? msg->len : MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN;
        memset(openhd_sys_load, 0, MAVLINK_MSG_ID_OPENHD_SYS_LOAD_LEN);
    memcpy(openhd_sys_load, _MAV_PAYLOAD(msg), len);
#endif
}
