//
// Created by Tom on 14/02/2022.
//

#include "Point.h"

Point::Point(double x, double y, double angle) {

    this->x = x;
    this->y = y;
    this->angle = angle;
}

string Point::to_string() {
    return "X: " + std::to_string(x) + "\tY: " + std::to_string(y) + "\tAngle: " + std::to_string(angle);
}
