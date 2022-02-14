//
// Created by Tom on 14/02/2022.
//

#include "MotionController.h"

#include <stdio.h>
using namespace std;

void MotionController::controlMotors() {

}

MotionController::MotionController(MotorManager motorManager, Odometry odometry) :
    motorManager(motorManager),
    odometry(odometry) {

}

void MotionController::calculateOrders(Point startingPoint, Point endPoint) {

    xOrder = endPoint.getX();
    yOrder = endPoint.getY();

    // Getting current position
    double x = startingPoint.getX();
    double y = startingPoint.getY();

    //Calculating the distance between current position and end position
    double distance = sqrt((xOrder - x) * (xOrder - x) + (yOrder - y) * (yOrder - y));

    //Calculating the angle between current position and end position
    angleOrder = atan2((xOrder - x),(yOrder - y)) * 180/M_PI;

    // Cap the angle between -180° and +180°
    if (angleOrder > 180){
        angleOrder -= 360;
    } else if(angleOrder <= -180){
        angleOrder += 360;
    }

    cout << "x order : "<< xOrder << "\ty order : " << yOrder << "\tangle order : " << angleOrder << endl;
}
