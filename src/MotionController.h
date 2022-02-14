//
// Created by Tom on 14/02/2022.
//

#ifndef KRABBS_MOTION_CONTROLLER_H
#define KRABBS_MOTION_CONTROLLER_H


#include "MotorManager.h"
#include "Point.h"
#include "Odometry.h"
#include "PID.h"

class MotionController {

    Point destination = {0, 0, 0};
    double distanceOrder, angleOrder;

    PID leftSpeedPID = {1, 0, 0};
    PID rightSpeedPID = {1, 0, 0};

    MotorManager *motorManager;
    Odometry *odometry;

    double leftWantedSpeed = 0, rightWantedSpeed = 0;
    double distanceToDestination = 0;
    double xOrder, yOrder;

public:

    MotionController(MotorManager *motorManager, Odometry *odometry);

    void setDestination(Point point);
    void controlMotors();

    void calculateWantedSpeeds();
    void calculateOrders(Point startingPoint, Point endPoint);

    double calculateCurrentDistanceFromStart();

    // Getters & Setters
    void setOrderXYAngle(double x, double y, double angle) {
        xOrder = x;
        yOrder = y;
        angleOrder = angle;
    }

    void setOrders(double distance, double angle) {
        distanceOrder = distance;
        angleOrder = angle;
    };
};


#endif //KRABBS_MOTION_CONTROLLER_H
