#include "MotorManager.h"

using namespace std;

// Constructeur par défaut : on stoppe les moteurs
MotorManager::MotorManager(int i2c) {
    leftSpeed = 0;
    rightSpeed = 0;

    leftMotorState = STOPPED;
    rightMotorState = STOPPED;

    i2c_fd = i2c;

    sendData();
}

/*
L'arduino va recevoir des valeurs entre 0 et 255 pour la commande de PWM (vitesse)
Une fois à la suite pour chaque roue
Puis elle reçoit également le sens (1 = marche avant // 2 = marche arrière // 0 = arrêt des moteurs)
Elle va alors changer IN1/IN2 en fonction du sens, et ENA en fonction de la commande
*/

/// @brief Load the order for the motors
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

/// @brief Shortcut to go forward
void MotorManager::forward() { //Fait forward le robot
    setOrder(10, 10);
	return;
}

/// @brief Shortcut to go backward
void MotorManager::backward() { //Fait backward le robot
    setOrder(-100, -100);
	return;
}

/// @brief Cap the value between -255 and 255
void MotorManager::capPWM(int *PWM) {
	if(*PWM < -255)	*PWM = -255;
	else if(*PWM > 255) *PWM = 255;
}

/// @brief Stop all the motors
void MotorManager::stop()
{
    leftSpeed = 0;
    rightSpeed = 0;
    leftMotorState = STOPPED;
    rightMotorState = STOPPED;
    sendData();
}

/// @brief Send the data using I2C
void MotorManager::sendData()
{
    // The bytes we will send
	uint8_t data[4];

	data[0] = leftSpeed;
	data[1] = rightSpeed;
	data[2] = motorStateToInt(leftMotorState);
	data[3] = motorStateToInt(rightMotorState);

	// Sending the byte array
	write(i2c_fd, data, 4);
}

/**
 * Simple debug function
 */
void MotorManager::debug() {

    uint8_t data[4];

    data[0] = 0;
    data[1] = 0;
    data[2] = 0;
    data[3] = 0;

    write(i2c_fd, data, 4);
}

/** @brief Convert the motor status to an integer value
 * 0 : STOPPED
 * 1 : FORWARD
 * 2 : BACKWARD
 */
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

    return value;
}

/**
 * @brief Get the motor state from the command value
 * Negative : BACKWARD
 * Positive : FORWARD
 * Null : STOPPED
 */
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

