cmake_minimum_required(VERSION 3.20)
project(XMavlinkService)

set(CMAKE_CXX_STANDARD 17)

# Build and include wifibroadcast
include(lib/wifibroadcast/WBLib.cmake)

# from https://github.com/alexott/boost-asio-examples/blob/master/CMakeLists.txt
SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE(Boost REQUIRED COMPONENTS system thread regex)
IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
    LINK_DIRECTORIES(${Boost_LIBRARY_DIRS})
ENDIF(Boost_FOUND)

SET(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY} ${WB_TARGET_LINK_LIBRARIES}
        )

add_executable(XMavlinkService main.cpp
        src/AirTelemetry.cpp
        src/GroundTelemetry.cpp
        src/endpoints/UDPEndpoint.cpp
        src/endpoints/TCPEndpoint.cpp
        src/endpoints/SerialEndpoint.cpp
        src/endpoints/WBEndpoint.cpp
        src/system/OHDTelemetryGenerator.cpp)

# Alternatively you could use ${Boost_LIBRARIES} here.
target_link_libraries(XMavlinkService ${USED_LIBS})
target_include_directories(XMavlinkService PUBLIC lib/c_library_v2_openhd)

add_executable(SerialEndpointTest test_serial_endpoint.cpp
        src/endpoints/SerialEndpoint.cpp)

target_link_libraries(SerialEndpointTest ${USED_LIBS})
target_include_directories(SerialEndpointTest PUBLIC lib/c_library_v2_openhd)

# from https://mavlink.io/en/mavgen_c/
#You can supress the warnings in CMake using
target_compile_options(XMavlinkService  INTERFACE -Wno-address-of-packed-member -Wno-cast-align)
target_compile_options(SerialEndpointTest  INTERFACE -Wno-address-of-packed-member -Wno-cast-align)