//
// Created by Taoufik on 12/11/2019.
//

#ifndef ROBOT_CONTROLLER_H
#define ROBOT_CONTROLLER_H


#include "PID.h"
#include "SerialCodeurManager.h"
#include "Odometry.h"
#include "MotorManager.h"
#include "MathUtils.h"
#include "Config.h"
#include "QuadrampDerivate.h"
#include "Trajectory.h"
#include "Point.h"

class Controller {

#define DISTANCE_TRESHOLD 5

public:
    /**
     * Initialisation de l'asservisement
     * @param codeurs
     * @param motor
     * @param config
    */
    Controller(Odometry * odometry_, MotorManager * motorManager_, Config * config_) {
        this->odometry = odometry_;
        this->motorManager = motorManager_;
        this->config = config_;
    }

    void update();
    void setTarget(int x, int y);
    void stopMotors();
    bool isTargetReached();
private:

    // Target position
    Position targetPosition;

    double angleError;

    //Odometry
    Odometry * odometry;

    // MoteurManager
    MotorManager * motorManager;

    //Config
    Config * config;

    double calculateAngleError();
    double getDistanceToTarget();

    void setConsign(double distance, double angle);

    struct {
        double distance = 0;
        double angle = 0;
    } consign;
};


#endif //ROBOT_CONTROLLER_H
