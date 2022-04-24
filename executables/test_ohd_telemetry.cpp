//
// Created by consti10 on 24.04.22.
// Test the OHD telemetry generation - this just prints the generated data to stdout.
//
#include "../src/system/OHDTelemetryGenerator.h"
#include <iostream>
#include <thread>

int main() {
    std::cout<< "OHDTelemetryGeneratorTest::start" << std::endl;

    OHDTelemetryGenerator ohdTelemetryGenerator(false);
    const auto start=std::chrono::steady_clock::now();
    while ((std::chrono::steady_clock::now()-start)<std::chrono::minutes(5)){
        const auto msg=OHDTelemetryGenerator::generateUpdate();

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout<< "OHDTelemetryGeneratorTest::end" << std::endl;
    return 0;
}
