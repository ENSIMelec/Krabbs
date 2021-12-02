#ifndef MOTOR_MANAGER_H_INCLUDED
#define MOTOR_MANAGER_H_INCLUDED

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <unistd.h>

enum MotorState : int {
    STOPPED,
    FORWARD,
    BACKWARD
};

class MotorManager
{

private:
    void capPWM(int *PWM);
    void sendData();

    // Speed values are between 0 and 255
    uint8_t leftSpeed;
    uint8_t rightSpeed;

    MotorState leftMotorState;
    MotorState rightMotorState;

    int i2c_fd;

    uint8_t motorStateToInt(MotorState status);
    MotorState getStateFromSign(int PWMValue);

public:
	MotorManager(int i2c);

	void setOrder(int leftOrder, int rightOrder);

	void forward();
	void backward();

	void stop();

    void debug();
};

#endif //MOTOR_MANAGER_H_INCLUDED