cmake_minimum_required(VERSION 3.16)

project(
    AutonomousDrivingDemo
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# =====================================================
# Main Application
# =====================================================

add_executable(
    autonomous_demo
    src/main.cpp
    src/AdaptiveCruiseControl.cpp
    src/CollisionDetector.cpp
)

target_include_directories(
    autonomous_demo
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(
    autonomous_demo
    PRIVATE
        -Wall
        -Wextra
        -Wpedantic
)

# =====================================================
# GoogleTest
# =====================================================

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    collision_detector_test
    tests/CollisionDetectorTest.cpp
    src/CollisionDetector.cpp
)

target_include_directories(
    collision_detector_test
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(
    collision_detector_test
    PRIVATE
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(
    collision_detector_test
)