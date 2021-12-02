//
// Created by Tom on 23/11/2021.
//

#ifndef KRABBS_TESTMOVEMENT_H
#define KRABBS_TESTMOVEMENT_H

#include "Test.h"
#include "MotorManager.h"

class TestMovement : Test {

private:
    // --- Variables ---
    MotorManager motorManager;

public:
    // --- Methods ---
    TestMovement(MotorManager motorManager) : motorManager(motorManager) {};

    /// @brief Execute all tests
    bool test();

    /// @brief Go forward for 1 second
    bool testGoForward();

    /// @brief Turn left for 1 second
    bool testTurnRight();

    /// @brief Turn right for 1 second
    bool testTurnLeft();

    /// @brief Go backward for 1 second
    bool testGoBackward();
};

#endif //KRABBS_TESTMOVEMENT_H
