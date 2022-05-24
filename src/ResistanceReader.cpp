//
// Created by cleme on 26/04/2022.
//
#include "ResistanceReader.h"
#include "base/ui/UI.h"
#include <unistd.h>

using namespace std;


ResistanceReader::ResistanceReader(int address) {
    // Setup I2C communication
    fd = address;
}

int ResistanceReader::getValues(){

    // Read data from arduino
    byte buffer[4];
    read(fd, buffer, 4);

    int startByte = (int) buffer[0];
    leftRes = (int) buffer[1];
    rightRes = (int) buffer[2];
    int endByte = (int) buffer[3];

//    int startByte = wiringPiI2CRead(fd);
//    int rightRes = wiringPiI2CRead(fd);
//    int leftRes = wiringPiI2CRead(fd);
//    int endByte = wiringPiI2CRead(fd);

//    printf("%d\n", startByte);
//    printf("%d\n", rightRes);
//    printf("%d\n", leftRes);
//    printf("%d\n", endByte);

    if(startByte != START_BYTE || endByte != END_BYTE) {
        UI::logAndRefresh("[RESISTANCE READER] Incorrect message");
        return EXIT_FAILURE;
    }

    switch (leftRes) {
        case RED:
            UI::logAndRefresh("[LEFT] red");
            break;
        case PURPLE:
            UI::logAndRefresh("[LEFT] purple");
            break;
        case YELLOW:
            UI::logAndRefresh("[LEFT] yellow");
            break;
        default:
            UI::logAndRefresh("[LEFT] undefined");
            break;
    }

    switch (rightRes) {
        case RED:
            UI::logAndRefresh("[RIGHT] red");
            break;
        case PURPLE:
            UI::logAndRefresh("[RIGHT] purple");
            break;
        case YELLOW:
            UI::logAndRefresh("[RIGHT] yellow");
            break;
        default:
            UI::logAndRefresh("[RIGHT] undefined");
            break;
    }


    return 0;
}

void ResistanceReader::printBuffer(const byte *buffer) const {
    printf("Printing buffer : ");
    printf("%");
}

int ResistanceReader::getStrategyIndexFromValues() {
    if(leftRes == NONE || rightRes == NONE) {
        return -1;
    }

    if(leftRes == RED) {
        if(rightRes == PURPLE) return 0;
        if(rightRes == YELLOW) return 2;
    } else {
        if(rightRes == PURPLE) return 3;
        if(rightRes == YELLOW) return 1;
    }

    return 4;
}
