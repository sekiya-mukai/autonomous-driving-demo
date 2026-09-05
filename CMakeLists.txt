cmake_minimum_required(VERSION 3.16)

project(
    AutonomousDrivingDemo
    VERSION 1.0.0
    DESCRIPTION "Simple Autonomous Driving Demo"
    LANGUAGES CXX
)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ===== Main executable =====

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

# ===== Tests (optional) =====

enable_testing()