cmake_minimum_required(VERSION 3.10)

# set the project name
project(midi-print-output)

# Additional CMake modules
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

find_package(RTMIDI REQUIRED)

# add the executable
add_executable(midi-print-output src/main.cpp)
target_link_libraries(midi-print-output PUBLIC rtmidi)
