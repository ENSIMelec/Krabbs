#include <iostream>
#include <unistd.h>

#include "base/Config.h"
#include "base/MotorManager.h"
#include "base/Utils.h"
#include "base/Clock.h"
#include "base/Odometry.h"
#include "base/Point.h"
#include "base/Controller.h"
#include "base/ActionManager.h"
#include "base/StrategyParser.h"
#include "base/Strategy.h"
#include "base/Initialize.h"

using namespace std;

// Constants for all the possible exits
#define EXIT_SUCCESS    0
#define EXIT_FAIL_I2C   1

// This folder is used to load all the external resources (like configuration files)
const string RES_PATH = "/home/pi/Documents/Krabbs/res/";

int main(int argc, char **argv) {

    Config *configuration = Initialize::start();

    Strategy strategy(RES_PATH + "strategies/Jaune/", "main.strat");
    strategy.logObjectives();

    unsigned int deltaAsservTimer = configuration->getDeltaAsserv();
    timer totalTime;

    //    controller.setTargetXY(300, 300);


//    //actionManager.action(RES_PATH + "actions/simpleAX12Test.as");

//    timer asservTimer;
//    while(!strategyIsDone && totalTime.elapsed_s() < 10) {
//
//        if(asservTimer.elapsed_ms() >= deltaAsservTimer) {
////            cout << totalTime.elapsed_us() << ";";
//
//            odometry.update();
//            controller.update();
//
//            if(controller.isTargetReached()) {
//                cout << "Target reached !" << endl;
//                controller.stopMotors();
//                strategyIsDone = true;
//            }
//            asservTimer.restart();
//        }
//    }
//
////    cout << "Stopping motors " << endl;
//    controller.stopMotors();
//
////    cout << "-- Quitting the application :" << endl;
////	cout << "Free memory ... ";
//    //actionManager.close();
//    close(i2cM);
//    close(i2cS);
//    close(i2cSt);
////    cout << "done" << endl;

//	cout << "-- End of the program" << endl;
	return EXIT_SUCCESS;
}