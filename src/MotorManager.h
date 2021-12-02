#ifndef MOTOR_MANAGER_H_INCLUDED
#define MOTOR_MANAGER_H_INCLUDED

#include <cstdint>
#include <cstdio>
#include <iostream>
#include <unistd.h>

/**
 * The Arduino will receive 4 unsigned 8 bit integer values from the i2c bus.
 * The first two values are for the speed (PWM). The last two are for the direction of the motors.
 * There is 3 possible values :
 *  - 0 : STOPPED
 *  - 1 : FORWARD
 *  - 2 : BACKWARD
 *
 *  Note : the speed of the motors should not be over 100
 */

/// @brief This enum is used to indicate the state of the motor
enum MotorState : int {
    STOPPED,
    FORWARD,
    BACKWARD
};

class MotorManager
{
private:
    // Speed values are between 0 and 255, they should not be over 100 for the safety of the robot
    uint8_t leftSpeed{};
    uint8_t rightSpeed{};

    MotorState leftMotorState;
    MotorState rightMotorState;

    int i2c_fd;

    /** @brief Convert the motor status to an integer value
     * 0 : STOPPED
     * 1 : FORWARD
     * 2 : BACKWARD
     */
    uint8_t motorStateToInt(MotorState status);

    /**
     * @brief Get the motor state from the command value
     * Negative : BACKWARD
     * Positive : FORWARD
     * Null : STOPPED
     */
    MotorState getStateFromSign(int PWMValue);

    /// @brief Cap the value between -255 and 255
    void capPWM(int *PWM);

    /// @brief Send the data using I2C
    void sendData();

public:
    /// @brief Default constructor
	explicit MotorManager(int i2c);

    /**
     * @brief Load the order for the motors
     * The absolute value of each order affect the speed. The sign of the order changes the direction.
     * A null value means that the motor is stopped.
     */
    void setOrder(int leftOrder, int rightOrder);

    /// @brief Shortcut to go forward
    void forward(int speed);

    /// @brief Shortcut to go backward
    void backward(int speed);

    /// @brief Stop all the motors
    void stop();
};

#endif //MOTOR_MANAGER_H_INCLUDED