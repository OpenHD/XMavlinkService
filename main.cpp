#include <iostream>

#include "src/GroundTelemetry.h"
#include "src/AirTelemetry.h"
#include <thread>

static constexpr auto TAG="XMAVLINK_SERVICE";
int main() {
    std::cout <<TAG<< "start" << std::endl;

    /*const bool AIR= false;
    if(AIR){
        AirTelemetry airTelemetry{};
        airTelemetry.loopInfinite();
    }else{
        GroundTelemetry groundTelemetry{};
        groundTelemetry.loopInfinite();
    }*/
    std::thread air([]{
        AirTelemetry airTelemetry{};
        airTelemetry.loopInfinite();
    });
    //
    GroundTelemetry groundTelemetry{};
    groundTelemetry.loopInfinite();

    return 0;
}
