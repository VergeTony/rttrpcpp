cmake_minimum_required (VERSION 3.10)
project (RTTrPCpp CXX)

# Builds unit tests (requires GTEST installation)
option(RTTRPCPP_TESTS "Build the tests" OFF)

# Internal log level for debugging
# 1 - info messages
# 2 - info and debug messages
option(RTTRPCPP_LOG_LEVEL "Log Level" 0)

if(${RTTRPCPP_LOG_LEVEL} GREATER 0)
    add_definitions(-DRTTRPCPP_LOG_LEVEL=${RTTRPCPP_LOG_LEVEL})
endif()

add_library(rttrpcpp
    src/RTTrPM.cpp
    src/RTTrPHeader.cpp
    src/modules/Module.cpp
    src/modules/ModuleFactory.cpp
    src/modules/centroid/CentroidPos.cpp
    src/modules/centroid/CentroidPosAccVel.cpp
    src/modules/trackedpoint/TrackedPointPos.cpp
    src/modules/trackedpoint/TrackedPointPosAccVel.cpp
    src/modules/orientation/OrientationEuler.cpp
    src/modules/orientation/OrientationQuaternion.cpp
    src/modules/zone/ZoneCollision.cpp
    src/trackables/Trackable.cpp
    src/trackables/TrackableFactory.cpp
    src/trackables/TrackableDefault.cpp
)

target_include_directories(rttrpcpp
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if(RTTRPCPP_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()