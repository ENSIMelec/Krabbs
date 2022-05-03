cmake_minimum_required(VERSION 3.18.4)
project(krabbs)

set(CMAKE_CXX_STANDARD 17)

# Linking all the libraries in the lib folder
link_directories(/usr/local/lib)
link_directories(/usr/include)
#link_directories(/usr/include/c++/10)

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

# Linking wiringPi to the binary
target_link_libraries(krabbs wiringPi)
target_link_libraries(krabbs dxl_sbc_cpp)