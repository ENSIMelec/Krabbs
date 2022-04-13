cmake_minimum_required(VERSION 3.18.4)
project(krabbs)

set(CMAKE_CXX_STANDARD 14)

# Linking all the libraries in the lib folder
link_directories(/usr/local/lib)
link_directories(/usr/include)
link_directories(/usr/include/c++/10)

# Adding executables
file(GLOB SRC
        # Custom files (including main.cpp)
        "src/*.h"
        "src/*.cpp"

        # Base files for the robot
        "src/base/*.h"
        "src/base/*.cpp"
        )

add_executable(krabbs ${SRC})
#        src/main.cpp
#        src/Config.cpp
#        src/MotorManager.cpp
#        src/TestMovement.cpp
#        src/Utils.cpp
#        src/Clock.h
#        src/Configuration.cpp src/Configuration.h
#        src/Odometry.cpp src/Odometry.h
#        src/SerialCodeurManager.cpp src/SerialCodeurManager.h
#        src/Point.cpp src/Point.h
#        src/Controller.cpp src/Controller.h
#        src/PID.cpp src/PID.h
#        src/QuadrampDerivate.cpp src/QuadrampDerivate.h
#        src/MathUtils.cpp src/MathUtils.h
#        src/Strategy.cpp src/Strategy.h
#        src/AX12Manager.cpp src/AX12Manager.h
#        src/ActionManager.cpp src/ActionManager.h
#        src/ActionServo.cpp src/ActionServo.h
#        src/FichierAction.cpp src/FichierAction.h
#        src/ServoManager.cpp src/ServoManager.h
#        src/pca9685.cpp src/pca9685.h)

# Linking wiringPi to the binary
target_link_libraries(krabbs wiringPi)
target_link_libraries(krabbs dxl_sbc_cpp)