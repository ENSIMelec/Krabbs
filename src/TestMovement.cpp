//
// Created by Tom on 23/11/2021.
//

using namespace std;

#include <unistd.h>
#include <thread>

#include "Utils.h"

#include "TestMovement.h"

bool TestMovement::test() {
    cout << "Testing the movement :" << endl;
    return testGoForward() && testGoBackward() && testTurnLeft() && testTurnRight();
}

bool TestMovement::testGoForward() {
    cout << "Testing : go Forward" << endl;

    motorManager.forward(50);
    Utils::sleepMillis(1000);
    motorManager.stop();

    return true;
}

bool TestMovement::testTurnRight() {
    cout << "Testing : turn right" << endl;

    motorManager.setOrder(40, -40);
    Utils::sleepMillis(1000);
    motorManager.stop();

    return true;
}

bool TestMovement::testTurnLeft() {

    cout << "Testing : turn left" << endl;

    motorManager.setOrder(-40, 40);
    Utils::sleepMillis(1000);
    motorManager.stop();

    return true;
}

bool TestMovement::testGoBackward() {

    cout << "Testing : go backward" << endl;

    motorManager.backward(50);
    Utils::sleepMillis(1000);
    motorManager.stop();

    return true;
}