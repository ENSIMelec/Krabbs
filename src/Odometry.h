//
// Created by Tom on 10/02/2022.
//

#ifndef KRABBS_ODOMETRY_H
#define KRABBS_ODOMETRY_H


#include "SerialCodeurManager.h"
#include "Config.h"

class Odometry {

private:
    SerialCodeurManager codeurs;

    //Coefficient tick codeur  -> distance
    double CoeffGLong;
    double CoeffDLong;

    double CoeffAnglD, CoeffAnglG;

    int comptG, comptD;
    int ticksG, ticksD;
    int tempsLast;

    double mesure_dist, mesure_angle;

    double dX, dY;
    //Angle du robot;
    double angle;

    //Coordonnées actuelles
    double x, y;
    double vitG = 0, vitD = 0;

    bool initialized = false;
public:
    Odometry(SerialCodeurManager codeurs, Config config);
    void update();
    void init();

    std::string getPositionStr();
};


#endif //KRABBS_ODOMETRY_H
