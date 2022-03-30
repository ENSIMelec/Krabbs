#include "Controller.h"

#define DEBUG_CONTROLLER
//#define CSV_PRINT

void Controller::update() {

    double Pk_angle = 200;
    double Pk_distance = 1;

    // Move forward if the angle error is low
    double distance = getDistanceToTarget() * Pk_distance;
    int distanceCommand = MathUtils::constrain(distance, 0, 100);

    angleError = calculateAngleError();
    double angleCommand = angleError * Pk_angle;

    // Apply commands
    motorManager->setOrder(distanceCommand - angleCommand, distanceCommand + angleCommand);

#ifdef CSV_PRINT
    cout << consign.angle << ";" << odometry->getTheta() << endl;
#endif

#ifdef DEBUG_CONTROLLER
    Position pos = odometry->getPosition();
    cout << "[POSITION] X: " << pos.x << "\tY: " << pos.y << "\tTheta: " << pos.theta << "(" << MathUtils::rad2deg(pos.theta) << "°)" << endl;
    cout << "[CONTROLLER] Consigne distance : " << consign.distance << "\tConsigne angle : " << consign.angle << endl;

    cout << "[CONTROLLER] Angle error : " << angleError << endl;
    cout << "[CONTROLLER] Angle command : " << angleCommand << "\tDistance command : " << distanceCommand << endl;
#endif
}

void Controller::setConsign(double distance, double angle) {
    consign.distance = distance;
    consign.angle = angle;
}

void Controller::setTarget(int x, int y) {
    targetPosition.x = x;
    targetPosition.y = y;

    Position pos = odometry->getPosition();
    double dX = pos.x - x;
    double dY = pos.y - y;
    double distance = sqrt(dX * dX + dY * dY);

    consign.distance = distance;
    consign.angle = acos(dX / distance);

    if(y < pos.y) consign.angle *= -1;
}

void Controller::stopMotors() {
    motorManager->stop();
}

bool Controller::isTargetReached() {

    // Get the distance between actual position and target
    double distance = getDistanceToTarget();
    return distance < DISTANCE_TRESHOLD;
}

double Controller::calculateAngleError() {

    // Calculate the angle error
    Position currentPosition = odometry->getPosition();
    double dX = targetPosition.x - currentPosition.x;
    double dY = targetPosition.y - currentPosition.y;

    double targetAngle = atan(dY / dX);

    cout << "[ANGLE CALCULATION] dx : " << dX << " dy : " << dY << endl;
    cout << "[ANGLE CALCULATION] target angle : " << targetAngle << endl;
    cout << "[ANGLE CALCULATION] distance : " << sqrt(dX * dX + dY * dY) << endl;
    if(targetAngle < - M_PI) {
        targetAngle += M_2_PI;
    } else if(targetAngle > M_PI) {
        targetAngle -= M_2_PI;
    }

    return targetAngle - currentPosition.theta;
}

/**
 * Get the distance between the current position and target
 */
double Controller::getDistanceToTarget() {

    Position currentPosition = odometry->getPosition();

    double dX = currentPosition.x - targetPosition.x;
    double dY = currentPosition.y - targetPosition.y;

    return sqrt(dX * dX + dY * dY);
}
