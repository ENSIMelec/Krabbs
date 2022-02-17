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
#include "SerialCodeurManager.h"

using namespace std;

// Constants for all the possible exits
#define EXIT_SUCCESS    0
#define EXIT_FAIL_I2C   1

// This folder is used to load all the external resources (like configuration files)
const string RES_PATH = "/home/pi/Documents/Krabbs/res/";

int main(int argc, char **argv) {
	cout << "-- Starting Krabbs :" << endl;

    cout << "Loading the configuration ... ";
    Config config;
    config.loadFromFile(RES_PATH + "config.info");

    unsigned int deltaAsservTimer = config.getDeltaAsserv();

    // TODO : add this constant to the config.info
    int I2C_MOTORS = 8;
    cout << "done" << endl;

	cout << "Initializing the GPIO ... ";
	wiringPiSetupGpio();
    int i2cM = wiringPiI2CSetup(I2C_MOTORS);

    // TODO : find what these are for
    int i2cS = wiringPiI2CSetup(config.get_I2C_SERVOS());
    int i2cSt = wiringPiI2CSetup(9);

    // If not initialized, the addresses are negative
    if(i2cS < 0 || i2cSt < 0 || i2cM < 0)
        return EXIT_FAIL_I2C;
    cout << "done" << endl;

    cout << "Initializing the motor manager ... ";
	MotorManager motorManager(i2cM);
    cout << "done" << endl;

    cout << "Start is done !" << endl;

    timer totalTime;

    SerialCodeurManager serialCodeurManager;
    Odometry odometry(serialCodeurManager);
    Controller controller(serialCodeurManager, motorManager, config);

    timer asservTimer;
    controller.setPosition(0, 0, 0);
    controller.set_trajectory(Controller::XY_ABSOLU);
    controller.set_point(300, 0, 0);

    bool strategyIsDone = false;
    while(!strategyIsDone && totalTime.elapsed_s() < 4) {
        if(asservTimer.elapsed_ms() >= deltaAsservTimer) {
            controller.update();

            asservTimer.restart();

            if(controller.is_target_reached()) {
                cout << "Target reached !" << endl;
                motorManager.stop();
                strategyIsDone = true;
            }
        }
    }

    Utils::sleepMillis(10);

    cout << "Stopping motors " << endl;
    motorManager.stop();

    cout << "-- Quitting the application :" << endl;
	cout << "Free memory ... ";
    close(i2cM);
    close(i2cS);
    close(i2cSt);
    cout << "done" << endl;

	cout << "-- End of the program" << endl;
	return EXIT_SUCCESS;
}