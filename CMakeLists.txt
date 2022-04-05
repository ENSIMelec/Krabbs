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
        src/Utils.cpp
        src/Clock.h
        src/Configuration.cpp src/Configuration.h
        src/Odometry.cpp src/Odometry.h
        src/SerialCodeurManager.cpp src/SerialCodeurManager.h
        src/Point.cpp src/Point.h
        src/Controller.cpp src/Controller.h
        src/PID.cpp src/PID.h
        src/QuadrampDerivate.cpp src/QuadrampDerivate.h
        src/MathUtils.cpp src/MathUtils.h
        src/Strategy.cpp src/Strategy.h)

# Linking wiringPi to the binary
target_link_libraries(krabbs wiringPi)