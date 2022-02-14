//
// Created by Tom on 14/02/2022.
//

#include "MotionController.h"
#include "Utils.h"

#include <stdio.h>

using namespace std;

MotionController::MotionController(MotorManager *motorManager, Odometry *odometry) :
    motorManager(motorManager),
    odometry(odometry) {

    cout << "Odometry : ref = " << to_string((int) &odometry) << endl;

}

void MotionController::controlMotors() {
    // Calculate the wanted speed
    calculateWantedSpeeds();

    cout << "[Wanted] Left speed : " << to_string(leftWantedSpeed) << "\tRight speed : " << to_string(rightWantedSpeed) << endl;


    // Updating the speed depending on the errors
    double leftSpeed = odometry->getLeftSpeed();
    double leftSpeedError = leftWantedSpeed - leftSpeed;

    double rightSpeed = odometry->getRightSpeed();
    double rightSpeedError = rightWantedSpeed - rightSpeed;

    cout << "[Real] Left speed : " << to_string(leftSpeed) << "\tRight speed : " << to_string(rightSpeed) << endl;

    leftSpeed = leftSpeedPID.compute(leftSpeedError);
    rightSpeed = rightSpeedPID.compute(rightSpeedError);

    cout << "[Corrected] Left speed : " << to_string(leftSpeed) << "\tRight speed : " << to_string(rightSpeed) << endl;
    motorManager->setOrder(leftSpeed, rightSpeed);
}

void MotionController::calculateOrders(Point startingPoint, Point endPoint) {

    xOrder = endPoint.getX();
    yOrder = endPoint.getY();

    // Getting current position
    double x = startingPoint.getX();
    double y = startingPoint.getY();

    //Calculating the distance between current position and end position
    distanceToDestination = sqrt((xOrder - x) * (xOrder - x) + (yOrder - y) * (yOrder - y));

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

void MotionController::setDestination(Point _destination) {
    this->destination = _destination;
}

/**
 * Calculate the left and right speeds depending on the distance to the destination point
 * There are 3 phases :
 * - Phase 1, from 0 to d/4 : acceleration phase
 * - Phase 2, from d/4 to 3/4d : maximum velocity reached, acceleration is null
 * - Phase 3, from 3/4d to d : deceleration phase
 * Where d is the distance between the starting point and the end point
 *
 * @param leftWantedSpeed
 * @param rightWantedSpeed
 */
void MotionController::calculateWantedSpeeds() {
    double distance = calculateCurrentDistanceFromStart();
    cout << "Current distance : " << distance << endl;

    const double maxSpeed = 20;
    const double acceleration = 1;

    double point1 = distanceToDestination * 1/4;
    double point2 = distanceToDestination * 3/4;

    // Phase 1
    if(distance <= point1) {
        leftWantedSpeed += acceleration;
        rightWantedSpeed += acceleration;
    }
    // Phase 2
    else if(distance > point1 && distance <= point2) {
        // Speeds stay the same
    }
    // Phase 3
    else if(distance > point2) {
        leftWantedSpeed -= acceleration;
        rightWantedSpeed -= acceleration;
    }

    leftWantedSpeed = Utils::clamp(leftWantedSpeed, 0, maxSpeed);
    rightWantedSpeed = Utils::clamp(rightWantedSpeed, 0, maxSpeed);
}

double MotionController::calculateCurrentDistanceFromStart() {

    double x = odometry->getX();
    double y = odometry->getY();

    cout << "x: " << x << " y: " << y << " x': " << xOrder << " y':" << yOrder << endl;

    // This is the norm of the vector defined by the current position and the destination position
    double currentDistanceToDestination = sqrt((xOrder - x) * (xOrder - x) + (yOrder - y) * (yOrder - y));
    return distanceToDestination - currentDistanceToDestination;
}
