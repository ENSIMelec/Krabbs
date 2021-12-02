#include "MotorManager.h"

// Uncomment to go in debug mod
//#define DEBUG_MOTOR_MANAGER

using namespace std;

// We don't have to initialize the motor to a stopped position because the Arduino already does it
MotorManager::MotorManager(int i2c) {
    i2c_fd = i2c;
}

void MotorManager::setOrder(int leftOrder, int rightOrder) {

    // We don't want values that are outside the range -255 to 255
    capPWM(&leftOrder);
    capPWM(&rightOrder);

    // The speed is a positive value between 0 and 255
    leftSpeed = (uint8_t) abs(leftOrder);
    rightSpeed = (uint8_t) abs(rightOrder);

    leftMotorState 	= getStateFromSign(leftOrder);
    rightMotorState = getStateFromSign(rightOrder);

    sendData();
}

void MotorManager::forward(int speed) { //Fait forward le robot
    setOrder(speed, speed);
	return;
}

void MotorManager::backward(int speed) { //Fait backward le robot
    setOrder(-speed, -speed);
	return;
}

void MotorManager::capPWM(int *PWM) {
	if(*PWM < -255)	*PWM = -255;
	else if(*PWM > 255) *PWM = 255;
}

void MotorManager::stop()
{
    leftSpeed = 0;
    rightSpeed = 0;
    leftMotorState = STOPPED;
    rightMotorState = STOPPED;

    sendData();
}

void MotorManager::sendData()
{
    // The bytes we will send
	uint8_t data[4];

	data[0] = (uint8_t) leftSpeed;
	data[1] = (uint8_t) rightSpeed;
	data[2] = (uint8_t) motorStateToInt(leftMotorState);
	data[3] = (uint8_t) motorStateToInt(rightMotorState);

#ifdef DEBUG_MOTOR_MANAGER
    cout << "Printing the content of data :" << endl;
    cout << "data[0] : " << unsigned(data[0]) << endl;
    cout << "data[1] : " << unsigned(data[1]) << endl;
    cout << "data[2] : " << unsigned(data[2]) << endl;
    cout << "data[3] : " << unsigned(data[3]) << endl;
#endif

	// Sending the byte array
	write(i2c_fd, data, 4);
}

uint8_t MotorManager::motorStateToInt(MotorState status) {
    uint8_t value;

    switch (status) {
        case STOPPED:
            value = 0;
            break;
        case FORWARD:
            value = 1;
            break;
        case BACKWARD:
            value = 2;
            break;
    }

    return (uint8_t) value;
}

MotorState MotorManager::getStateFromSign(int order) {
    MotorState status;

    if(order > 0) {
        status = FORWARD;
    } else if (order < 0) {
        status = BACKWARD;
    } else {
        status = STOPPED;
    }

    return status;
}

