//
// Created by Tom on 06/12/2021.
//

#include "Coordinate.h"

/**
 * @brief Depending on the side, this will return the correct position
 * We keep the origin at the same position (bottom left hand corner of the table) and we translate the x position
 * depending of the side.
 * The positions are mirrored on each side.
 */
int Coordinate::getAbsoluteX() {
    if(side == YELLOW) {
        return x;
    } else {
        return TABLE_WIDTH - x;
    }
}

int Coordinate::getAbsoluteY() {
    return y;
}

void Coordinate::initialize(int currentSide) {
    if(currentSide == 0) {
        Coordinate::side = YELLOW;
    } else {
        Coordinate::side = PURPLE;
    }
}
