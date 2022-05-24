cmake_minimum_required(VERSION 3.18.4)
project(krabbs)

set(CMAKE_CXX_STANDARD 17)

# Linking all the libraries in the lib folder
link_directories(/usr/local/lib)
link_directories(/usr/include)
#link_directories(/usr/include/c++/10)

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

# Adding executables
file(GLOB SRC
        # Custom files (including main.cpp)
        "sc/*.h"
        "src/*.cpp"

        # Base files for the robot
        "src/base/*.h"
        "src/base/*.cpp"

        "src/base/actuators/*.cpp"
        "src/base/actuators/*.h"

        "src/base/controller/*.cpp"
        "src/base/controller/*.h"

        "src/base/odometry/*.cpp"
        "src/base/odometry/*.h"

        "src/base/lib/*.cpp"
        "src/base/lib/*.h"

        "src/base/strategy/*.cpp"
        "src/base/strategy/*.h"

        "src/base/utility/*.cpp"
        "src/base/utility/*.h"

        "src/base/ui/*.cpp"
        "src/base/ui/*.h"
        )

add_executable(krabbs ${SRC})

# Linking libraries
target_link_libraries(krabbs wiringPi)        # For GPIO
target_link_libraries(krabbs ncursesw)        # For console interface
target_link_libraries(krabbs dxl_sbc_cpp)     # For the AX12
target_link_libraries(krabbs Threads::Threads)
