//
// Created by Tom on 23/11/2021.
//

#include <unistd.h>

#include "TestMovement.h"
#include "TestMovement.h"

bool TestMovement::test() {
    // All tests have to return true
    return testGoForward() && testGoBackward() && testTurnLeft() && testTurnRight();
}

/// @brief Go forward for 1 second
bool TestMovement::testGoForward() {

    motorManager.forward();
    usleep(1000);
    motorManager.stop();

    return true;
}

bool TestMovement::testTurnRight() {
    //motorManager.turnRight(90);
    return true;
}

bool TestMovement::testTurnLeft() {
    //motorManager.turnLeft(90);
    return true;
}

/// @brief Go backward for 1 second
bool TestMovement::testGoBackward() {

    motorManager.backward();
    usleep(1000);
    motorManager.stop();

    return true;
}

