#include <iostream>
#include <unistd.h>

#include "base/Config.h"
#include "base/MotorManager.h"
#include "base/Clock.h"
#include "base/Odometry.h"
#include "base/Point.h"
#include "base/Controller.h"
#include "base/ActionManager.h"
#include "base/StrategyParser.h"
#include "base/Strategy.h"
#include "base/Initializer.h"

using namespace std;

// Constants for all the possible exits
#define EXIT_SUCCESS    0
#define EXIT_FAIL_I2C   1

#define MAX_TIME 10     // The maximum time the robot will run (in seconds)

// This folder is used to load all the external resources (like configuration files)
const string RES_PATH = "/home/pi/Documents/Krabbs/res/";

int main(int argc, char **argv) {

    Config *configuration = Initializer::start();

    Strategy strategy(RES_PATH + "strategies/Jaune/", "main.strat");
    strategy.logObjectives();

    Controller * controller = Initializer::getController();
    Odometry * odometry = Initializer::getOdometry();

    unsigned int updateTime = configuration->getDeltaAsserv();
    timer totalTime;

    cout << "Started objective : " << strategy.getCurrentObjective()->getName() << endl;
    Point * nextPoint = strategy.getCurrentPoint();  // The current point destination
    nextPoint->logTargetInformation();

    timer updateTimer;
    while(!strategy.isDone() && totalTime.elapsed_s() < MAX_TIME) {

        if(updateTimer.elapsed_ms() >= updateTime) {
//            odometry->update();
//            controller->update();

            if(controller->isTargetReached()) {
                cout << "Point reached !" << endl;
//                controller->stopMotors();

                // Go to the next point
                nextPoint = strategy.getNextPoint();

                if(!strategy.isDone()) {
                    controller->setTargetPoint(nextPoint);
                }
            }
            updateTimer.restart();
        }
    }

    // Quitting the application
    Initializer::end();

	cout << "-- End of the program" << endl;
	return EXIT_SUCCESS;
}