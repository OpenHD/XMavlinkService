//
// Created by consti10 on 19.04.22.
//

#ifndef XMAVLINKSERVICE_OHDTELEMETRYGENERATOR_H
#define XMAVLINKSERVICE_OHDTELEMETRYGENERATOR_H

#include "../mav_helper.h"

// The purpose of this class is to generate all the OpenHD specific telemetry that can be sent
// in a fire and forget manner. For example, to report the CPU usage on the air station,
// one can read out the cpu usage in regular intervalls and send it out (perhaps together with other
// telemetry values)
class OHDTelemetryGenerator {
public:
    OHDTelemetryGenerator();
    MavlinkMessage generateUpdate();
};


#endif //XMAVLINKSERVICE_OHDTELEMETRYGENERATOR_H
