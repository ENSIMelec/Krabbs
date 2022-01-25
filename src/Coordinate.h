//
// Created by Tom on 06/12/2021.
//

#ifndef KRABBS_COORDINATE_H
#define KRABBS_COORDINATE_H

#define YELLOW 0
#define PURPLE 1

// We use millimeter as base unit
// 1 millimeter = 1 unit
#define TABLE_WIDTH 3000
#define TABLE_HEIGHT 2000

/**
 * The coordinates are stored with default yellow side.
 * Given that the table is symmetrical, we only need instructions for the yellow side and it will automatically convert
 * them to the correct absolute position on the purple side.
 */

class Coordinate {

private:
    int side = YELLOW;
public:
    // ***** VARIABLES *****
    int x, y;

    Coordinate(int x, int y) : x(x), y(y) {

    }

    // ***** METHODS *****
    /// @brief Initialize on which side the robot is. It is yellow by default
    void initialize(int currentSide);

    // ----- Getters & Setters -----
    /// @brief Returns the absolute x position in millimeters
    int getAbsoluteX();

    /// @brief Returns the absolute y position in millimeters
    int getAbsoluteY();
};

#endif //KRABBS_COORDINATE_H
