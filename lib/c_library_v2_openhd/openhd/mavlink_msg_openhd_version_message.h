#pragma once
// MESSAGE OPENHD_VERSION_MESSAGE PACKING

#define MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE 1261


typedef struct __mavlink_openhd_version_message_t {
 char version[30]; /*<  version string, 29 character max length since it *must* be null-terminated*/
} mavlink_openhd_version_message_t;

#define MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN 30
#define MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_MIN_LEN 30
#define MAVLINK_MSG_ID_1261_LEN 30
#define MAVLINK_MSG_ID_1261_MIN_LEN 30

#define MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_CRC 3
#define MAVLINK_MSG_ID_1261_CRC 3

#define MAVLINK_MSG_OPENHD_VERSION_MESSAGE_FIELD_VERSION_LEN 30

#if MAVLINK_COMMAND_24BIT
#define MAVLINK_MESSAGE_INFO_OPENHD_VERSION_MESSAGE { \
    1261, \
    "OPENHD_VERSION_MESSAGE", \
    1, \
    {  { "version", NULL, MAVLINK_TYPE_CHAR, 30, 0, offsetof(mavlink_openhd_version_message_t, version) }, \
         } \
}
#else
#define MAVLINK_MESSAGE_INFO_OPENHD_VERSION_MESSAGE { \
    "OPENHD_VERSION_MESSAGE", \
    1, \
    {  { "version", NULL, MAVLINK_TYPE_CHAR, 30, 0, offsetof(mavlink_openhd_version_message_t, version) }, \
         } \
}
#endif

/**
 * @brief Pack a openhd_version_message message
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 *
 * @param version  version string, 29 character max length since it *must* be null-terminated
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_openhd_version_message_pack(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg,
                               const char *version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN];

    _mav_put_char_array(buf, 0, version, 30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN);
#else
    mavlink_openhd_version_message_t packet;

    mav_array_memcpy(packet.version, version, sizeof(char)*30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE;
    return mavlink_finalize_message(msg, system_id, component_id, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_CRC);
}

/**
 * @brief Pack a openhd_version_message message on a channel
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param version  version string, 29 character max length since it *must* be null-terminated
 * @return length of the message in bytes (excluding serial stream start sign)
 */
static inline uint16_t mavlink_msg_openhd_version_message_pack_chan(uint8_t system_id, uint8_t component_id, uint8_t chan,
                               mavlink_message_t* msg,
                                   const char *version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN];

    _mav_put_char_array(buf, 0, version, 30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), buf, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN);
#else
    mavlink_openhd_version_message_t packet;

    mav_array_memcpy(packet.version, version, sizeof(char)*30);
        memcpy(_MAV_PAYLOAD_NON_CONST(msg), &packet, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN);
#endif

    msg->msgid = MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE;
    return mavlink_finalize_message_chan(msg, system_id, component_id, chan, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_CRC);
}

/**
 * @brief Encode a openhd_version_message struct
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param msg The MAVLink message to compress the data into
 * @param openhd_version_message C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_openhd_version_message_encode(uint8_t system_id, uint8_t component_id, mavlink_message_t* msg, const mavlink_openhd_version_message_t* openhd_version_message)
{
    return mavlink_msg_openhd_version_message_pack(system_id, component_id, msg, openhd_version_message->version);
}

/**
 * @brief Encode a openhd_version_message struct on a channel
 *
 * @param system_id ID of this system
 * @param component_id ID of this component (e.g. 200 for IMU)
 * @param chan The MAVLink channel this message will be sent over
 * @param msg The MAVLink message to compress the data into
 * @param openhd_version_message C-struct to read the message contents from
 */
static inline uint16_t mavlink_msg_openhd_version_message_encode_chan(uint8_t system_id, uint8_t component_id, uint8_t chan, mavlink_message_t* msg, const mavlink_openhd_version_message_t* openhd_version_message)
{
    return mavlink_msg_openhd_version_message_pack_chan(system_id, component_id, chan, msg, openhd_version_message->version);
}

/**
 * @brief Send a openhd_version_message message
 * @param chan MAVLink channel to send the message
 *
 * @param version  version string, 29 character max length since it *must* be null-terminated
 */
#ifdef MAVLINK_USE_CONVENIENCE_FUNCTIONS

static inline void mavlink_msg_openhd_version_message_send(mavlink_channel_t chan, const char *version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char buf[MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN];

    _mav_put_char_array(buf, 0, version, 30);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE, buf, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_CRC);
#else
    mavlink_openhd_version_message_t packet;

    mav_array_memcpy(packet.version, version, sizeof(char)*30);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE, (const char *)&packet, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_CRC);
#endif
}

/**
 * @brief Send a openhd_version_message message
 * @param chan MAVLink channel to send the message
 * @param struct The MAVLink struct to serialize
 */
static inline void mavlink_msg_openhd_version_message_send_struct(mavlink_channel_t chan, const mavlink_openhd_version_message_t* openhd_version_message)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_openhd_version_message_send(chan, openhd_version_message->version);
#else
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE, (const char *)openhd_version_message, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_CRC);
#endif
}

#if MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN <= MAVLINK_MAX_PAYLOAD_LEN
/*
  This variant of _send() can be used to save stack space by re-using
  memory from the receive buffer.  The caller provides a
  mavlink_message_t which is the size of a full mavlink message. This
  is usually the receive buffer for the channel, and allows a reply to an
  incoming message with minimum stack space usage.
 */
static inline void mavlink_msg_openhd_version_message_send_buf(mavlink_message_t *msgbuf, mavlink_channel_t chan,  const char *version)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    char *buf = (char *)msgbuf;

    _mav_put_char_array(buf, 0, version, 30);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE, buf, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_CRC);
#else
    mavlink_openhd_version_message_t *packet = (mavlink_openhd_version_message_t *)msgbuf;

    mav_array_memcpy(packet->version, version, sizeof(char)*30);
    _mav_finalize_message_chan_send(chan, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE, (const char *)packet, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_MIN_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_CRC);
#endif
}
#endif

#endif

// MESSAGE OPENHD_VERSION_MESSAGE UNPACKING


/**
 * @brief Get field version from openhd_version_message message
 *
 * @return  version string, 29 character max length since it *must* be null-terminated
 */
static inline uint16_t mavlink_msg_openhd_version_message_get_version(const mavlink_message_t* msg, char *version)
{
    return _MAV_RETURN_char_array(msg, version, 30,  0);
}

/**
 * @brief Decode a openhd_version_message message into a struct
 *
 * @param msg The message to decode
 * @param openhd_version_message C-struct to decode the message contents into
 */
static inline void mavlink_msg_openhd_version_message_decode(const mavlink_message_t* msg, mavlink_openhd_version_message_t* openhd_version_message)
{
#if MAVLINK_NEED_BYTE_SWAP || !MAVLINK_ALIGNED_FIELDS
    mavlink_msg_openhd_version_message_get_version(msg, openhd_version_message->version);
#else
        uint8_t len = msg->len < MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN? msg->len : MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN;
        memset(openhd_version_message, 0, MAVLINK_MSG_ID_OPENHD_VERSION_MESSAGE_LEN);
    memcpy(openhd_version_message, _MAV_PAYLOAD(msg), len);
#endif
}
