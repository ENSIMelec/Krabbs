//
// Created by Tom on 14/02/2022.
//

#ifndef KRABBS_POINT_H
#define KRABBS_POINT_H

#include <string>
using namespace std;

class Point {

private:
    double x, y;
    double angle;

public:
    // Constructor
    Point(double x, double y, double angle);


    // Getters & Setters
    double getX() { return x; }
    double getY() { return y; }
    double getAngle() { return angle; }

    string to_string();
};

#endif //KRABBS_POINT_H
