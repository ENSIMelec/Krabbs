//
// Created by Tom on 23/11/2021.
//

#ifndef KRABBS_TESTMOVEMENT_H
#define KRABBS_TESTMOVEMENT_H

#include "Test.h"
#include "MotorManager.h"

class TestMovement : Test {

public:
    // --- Variables ---
    MotorManager motorManager;

    // --- Methods ---
    TestMovement(MotorManager motorManager) : motorManager(motorManager) {};

    /// @brief Execute all tests
    bool test();

    bool testGoForward();
    bool testTurnRight();
    bool testTurnLeft();
    bool testGoBackward();

};

#endif //KRABBS_TESTMOVEMENT_H
