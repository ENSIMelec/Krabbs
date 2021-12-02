//
// Created by Tom on 02/12/2021.
//
#include <thread>

#include "Utils.h"

void Utils::sleepMillis(int millis) {
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}
