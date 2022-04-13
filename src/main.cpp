#include <iostream>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include "Config.h"
#include "MotorManager.h"
#include "Utils.h"
#include "Clock.h"
#include "Odometry.h"
#include "Point.h"
#include "Controller.h"
#include "Strategy.h"
#include "AX12Manager.h"
#include "ActionManager.h"
#include "ServoManager.h"

using namespace std;

// Constants for all the possible exits
#define EXIT_SUCCESS    0
#define EXIT_FAIL_I2C   1

// This folder is used to load all the external resources (like configuration files)
const string RES_PATH = "/home/pi/Documents/Krabbs/res/";

int main(int argc, char **argv) {
//	cout << "-- Starting Krabbs :" << endl;

//    cout << "Loading the configuration ... ";
    Config config;
    config.loadFromFile(RES_PATH + "config.info");

    unsigned int deltaAsservTimer = config.getDeltaAsserv();

    // TODO : add this constant to the config.info
    int I2C_MOTORS = 8;
//    cout << "done" << endl;

//	cout << "Initializing the GPIO ... ";
	wiringPiSetupGpio();
    int i2cM = wiringPiI2CSetup(I2C_MOTORS);

    // TODO : find what these are for
    int i2cS = wiringPiI2CSetup(config.get_I2C_SERVOS());
    int i2cSt = wiringPiI2CSetup(9);

    // If not initialized, the addresses are negative
    if(i2cS < 0 || i2cSt < 0 || i2cM < 0)
        return EXIT_FAIL_I2C;
//    cout << "done" << endl;

//    cout << "Initializing the motor manager ... ";
	MotorManager motorManager(i2cM);
//    cout << "done" << endl;

//    cout << "Start is done !" << endl;

    timer totalTime;

    SerialCodeurManager serialCodeurManager;

    Odometry odometry(serialCodeurManager);
    odometry.setPosition(0, 0, 0);

    Controller controller(&odometry, &motorManager, &config);
    //controller.setTargetXY(300, 300);

    ActionManager actionManager(i2cS, 2);
    actionManager.action(RES_PATH + "actions/simpleAX12Test.as");

    bool strategyIsDone = false;

    timer asservTimer;
    while(!strategyIsDone && totalTime.elapsed_s() < 4) {

        if(asservTimer.elapsed_ms() >= deltaAsservTimer) {
//            cout << totalTime.elapsed_us() << ";";

            odometry.update();
            controller.update();

            if(controller.isTargetReached()) {
                cout << "Target reached !" << endl;
                controller.stopMotors();
                strategyIsDone = true;
            }
            asservTimer.restart();
        }
    }

    Utils::sleepMillis(20);

//    cout << "Stopping motors " << endl;
    controller.stopMotors();

//    cout << "-- Quitting the application :" << endl;
//	cout << "Free memory ... ";
    actionManager.close();
    close(i2cM);
    close(i2cS);
    close(i2cSt);
//    cout << "done" << endl;

//	cout << "-- End of the program" << endl;
	return EXIT_SUCCESS;
}