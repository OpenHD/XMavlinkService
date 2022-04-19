//
// Created by consti10 on 19.04.22.
//

#ifndef XMAVLINKSERVICE_HANDLEPOWERCOMMANDS_H
#define XMAVLINKSERVICE_HANDLEPOWERCOMMANDS_H

#include <utility>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <chrono>
#include <iostream>

#include "../Helper.hpp"

// convenient utils to handle the shutdown or reboot commands for OpenHD.
// based on
// https://github.com/OpenHD/Open.HD/blob/4dc8d09b3f8067a2f44eea3f7b1079acef842412/openhd-power/src/powermicroservice.cpp
namespace RebootUtil {
    // either shut down or reboot
    static void handlePowerCommand(bool shutdownOnly) {
        if (shutdownOnly) {
            std::cout << "handlePowerCommand()-shutdown\n";
            boost::process::child c_systemctl_shutdown(
                    boost::process::search_path("systemctl"),
                    std::vector<std::string>{"start", "poweroff.target"},
                    m_io_service);
            c_systemctl_shutdown.detach();
        } else {
            std::cout << "handlePowerCommand()-reboot\n";
            boost::process::child c_systemctl_reboot(
                    boost::process::search_path("systemctl"),
                    std::vector<std::string>{"start", "reboot.target"},
                    m_io_service);
            c_systemctl_reboot.detach();
        }
    }

}
#endif //XMAVLINKSERVICE_HANDLEPOWERCOMMANDS_H
