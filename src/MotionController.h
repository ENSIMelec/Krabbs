//
// Created by Tom on 14/02/2022.
//

#ifndef KRABBS_MOTION_CONTROLLER_H
#define KRABBS_MOTION_CONTROLLER_H


#include "MotorManager.h"
#include "Point.h"
#include "Odometry.h"

class MotionController {

    double distanceOrder, angleOrder;

    MotorManager motorManager;
    Odometry odometry;

    double xOrder, yOrder;

public:

    MotionController(MotorManager motorManager, Odometry odometry);

    void controlMotors();


    void calculateOrders(Point startingPoint, Point endPoint);

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
