#include <iostream>

#include "src/GroundTelemetry.h"
#include "src/AirTelemetry.h"

static constexpr auto TAG="XMAVLINK_SERVICE";
int main() {
    std::cout <<TAG<< "start" << std::endl;

    const bool AIR= false;
    if(AIR){
        AirTelemetry airTelemetry{};
        std::cout <<TAG<< "air start" << std::endl;
        airTelemetry.loopInfinite();
    }else{
        GroundTelemetry groundTelemetry{};
        std::cout <<TAG<< "ground start" << std::endl;
        groundTelemetry.loopInfinite();
    }
    return 0;
}
