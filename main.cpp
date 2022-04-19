#include <iostream>

#include "src/GroundTelemetry.h"
#include "src/AirTelemetry.h"
#include <thread>

static constexpr auto TAG="XMAVLINK_SERVICE";
int main() {
    std::cout <<TAG<< "start" << std::endl;

    /*const bool AIR= true;
    if(AIR){
        AirTelemetry airTelemetry{};
        std::cout <<TAG<< "air start" << std::endl;
        airTelemetry.loopInfinite();
    }else{
        GroundTelemetry groundTelemetry{};
        std::cout <<TAG<< "ground start" << std::endl;
        groundTelemetry.loopInfinite();
    }*/
    std::thread air([]{
        AirTelemetry airTelemetry{};
        std::cout <<TAG<< "air start" << std::endl;
        airTelemetry.loopInfinite();
    });
    //
    GroundTelemetry groundTelemetry{};
    std::cout <<TAG<< "ground start" << std::endl;
    groundTelemetry.loopInfinite();

    return 0;
}
