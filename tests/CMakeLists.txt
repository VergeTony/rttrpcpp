cmake_minimum_required (VERSION 3.10)

set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

include_directories(
    ${GTEST_INCLUDE_DIRS}
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests/include
)

add_executable(RTTrPCppTest RTTrPCppTest.cpp)

target_link_libraries(RTTrPCppTest
    ${GTEST_LIBRARIES}
    Threads::Threads
    rttrpcpp
)

gtest_add_tests(
    TARGET  RTTrPCppTest
)