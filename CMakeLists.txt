cmake_minimum_required(VERSION 3.18.4)
project(krabbs)

set(CMAKE_CXX_STANDARD 14)

# Linking all the libraries in the lib folder
link_directories(/usr/local/lib)

# Adding executables
add_executable(krabbs
        src/main.cpp
        src/Config.cpp
        src/MotorManager.cpp
        src/TestMovement.cpp
        src/Utils.cpp src/Utils.h
        src/Coordinate.cpp src/Coordinate.h)

# Linking wiringPi to the binary
target_link_libraries(krabbs wiringPi)