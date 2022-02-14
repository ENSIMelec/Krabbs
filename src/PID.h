//
// Created by Tom on 14/02/2022.
//

#ifndef KRABBS_PID_H
#define KRABBS_PID_H


class PID {

private:
    double kP, kI, kD;

    double lastError = 0;
    double sumErrors = 0;
public:
    PID(double kP, double kI, double kD);
    double compute(double error);
};


#endif //KRABBS_PID_H
