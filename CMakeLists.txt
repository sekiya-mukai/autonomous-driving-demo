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
# Common Settings
# =====================================================

set(COMMON_COMPILE_OPTIONS
    -Wall
    -Wextra
    -Wpedantic
)

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
        ${COMMON_COMPILE_OPTIONS}
)

# =====================================================
# GoogleTest
# =====================================================

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(googletest)

enable_testing()

# =====================================================
# Collision Detector Test
# =====================================================

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

target_compile_options(
    collision_detector_test
    PRIVATE
        ${COMMON_COMPILE_OPTIONS}
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

# =====================================================
# Adaptive Cruise Control Test
# =====================================================

add_executable(
    adaptive_cruise_control_test
    tests/AdaptiveCruiseControlTest.cpp
    src/AdaptiveCruiseControl.cpp
)

target_include_directories(
    adaptive_cruise_control_test
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

target_compile_options(
    adaptive_cruise_control_test
    PRIVATE
        ${COMMON_COMPILE_OPTIONS}
)

target_link_libraries(
    adaptive_cruise_control_test
    PRIVATE
        GTest::gtest_main
)

gtest_discover_tests(
    adaptive_cruise_control_test
)
