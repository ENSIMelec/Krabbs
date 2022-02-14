//
// Created by Tom on 14/02/2022.
//

#include "PID.h"

PID::PID(double kP, double kI, double kD) {
    this->kP = kP;
    this->kI = kI;
    this->kD = kD;
}

double PID::compute(double error) {
    sumErrors += error;

    double P = error * kP;
    double I = sumErrors * kI;
    double D = (error - lastError) * kD;

    lastError = error;

    return P + I + D;
}


