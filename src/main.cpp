#include <iostream>
#include <unistd.h>

#include "base/controller/MotorManager.h"
#include "base/utility/Clock.h"
#include "base/odometry/Odometry.h"
#include "base/strategy/Point.h"
#include "base/controller/Controller.h"
#include "base/actuators/ActionManager.h"
#include "base/strategy/StrategyParser.h"
#include "base/strategy/Strategy.h"
#include "base/utility/Initializer.h"
#include "base/Lidar.h"

using namespace std;

// Constants for all the possible exits
#define EXIT_SUCCESS    0
#define EXIT_FAIL_I2C   1

#define MAX_TIME 10     // The maximum time the robot will run (in seconds)

// This folder is used to load all the external resources (like configuration files)
const string RES_PATH = "/home/pi/Documents/Krabbs/res/";

int main(int argc, char **argv) {
    Configuration *configuration = Initializer::start();

    Controller * controller = Initializer::getController();
    Odometry * odometry = Initializer::getOdometry();
    ActionManager * actionManager = Initializer::getActionManager();

    unsigned int updateTime = configuration->getInt("global.update_time");
    timer totalTime;

    Strategy strategy(RES_PATH + "strategies/Forward/", "main.strategy");
    cout << "Started objective : " << strategy.getCurrentObjective()->getName() << endl;
    Point * currentPoint = strategy.getCurrentPoint();  // The current point destination

    // Set the initial location
    odometry->setPosition(currentPoint->getX(), currentPoint->getY(), currentPoint->getTheta());

    // Set first target
    currentPoint = strategy.getNextPoint();
//    controller->setTargetXY((int) currentPoint->getX(), (int) currentPoint->getY());
    controller->setNextPoint(currentPoint);

    timer updateTimer;
    while(!strategy.isDone() && totalTime.elapsed_s() < configuration->getInt("global.match_time")) {

        if(updateTimer.elapsed_ms() >= updateTime) {
            if(Lidar::isActive()){
                printf("Warning : %d | Danger : %d\n", Lidar::isWarning(), Lidar::isDanger());
            }

            odometry->update();
            odometry->debug();

            if(Lidar::isDanger()) {
                controller->stopMotors();
            } else {
                controller->update();
            }

//            controller->debug();

            if(controller->isTargetReached()) {
                cout << "Point reached !" << endl;
                controller->stopMotors();

                // Execute the action
                if(currentPoint->isActionAfterMovement()) {
                    string actionFile = currentPoint->getAction();
                    if(actionFile != "null") actionManager->action(actionFile);
                }

                // Go to the next point
                currentPoint = strategy.getNextPoint();

                if(!strategy.isDone()) {
                    controller->setTargetXY((int) currentPoint->getX(), (int) currentPoint->getY());
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