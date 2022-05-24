/*
   This program is used to control the motors for Krabbs
   see https://github.com/ENSIMelec/Krabbs

   It uses an I2C bus to communicate with the RapsberryPi.
   The board send a PWM value between -255 and 255 for each motors.

   Last updated : March 01 2022
   Author : Tom de Pasquale
*/

#include <Wire.h>

// Comment or uncomment to activate
//#define DEBUG // Used to print informations to the serial port
//#define TEST  // Used to activate the motors on startup.

// Left motor
#define ENABLE_LEFT   9   // Brown
#define INPUT_2_LEFT 10   // Red
#define INPUT_1_LEFT 11   // Black

// Right motor
#define ENABLE_RIGHT  6   // Yellow
#define INPUT_2_RIGHT 8   // Orange
#define INPUT_1_RIGHT 7   // Green

// I2C address
#define ADDR_I2C   8


// Timeout
#define TIMEOUT_DELAY_MS 1000
uint16_t timeout_timer;

void setup() {

#ifdef DEBUG
  Serial.begin(9600);
#endif

  // Setup the pins to OUTPUT
  pinMode(ENABLE_LEFT, OUTPUT);
  pinMode(INPUT_2_LEFT, OUTPUT);
  pinMode(INPUT_1_LEFT, OUTPUT);

  pinMode(ENABLE_RIGHT, OUTPUT);
  pinMode(INPUT_2_RIGHT, OUTPUT);
  pinMode(INPUT_1_RIGHT, OUTPUT);

  // Make sure the motors are stopped
  stop();

#ifdef TEST
  // Simple forward then backward
  forward(40);
  delay(1000);

  backward(40);
  delay(1000);

  stop();
#endif

  // Start I2C
  Wire.begin(ADDR_I2C);

  // Add interrupt function
  Wire.onReceive(recv);
}


/* Empty loop function. We wait for an interruption to do something. */
void loop() {
  if(millis() > timeout_timer){
    #ifdef DEBUG
      Serial.println("TIMEOUT !!! Emergency stop");
    #endif
    //stop();
    
  }
}

/* Function that stop the motors */
void stop() {
  analogWrite(ENABLE_RIGHT, LOW);
  digitalWrite(INPUT_1_RIGHT, LOW);
  digitalWrite(INPUT_2_RIGHT, LOW);

  analogWrite(ENABLE_LEFT, LOW);
  digitalWrite(INPUT_1_LEFT, LOW);
  digitalWrite(INPUT_2_LEFT, LOW);
}

#ifdef TEST
void forward(uint8_t speed) {
  digitalWrite(INPUT_1_LEFT, LOW);
  digitalWrite(INPUT_2_LEFT, HIGH);

  digitalWrite(INPUT_1_RIGHT, LOW);
  digitalWrite(INPUT_2_RIGHT, HIGH);

  analogWrite(ENABLE_RIGHT, speed);
  analogWrite(ENABLE_LEFT, speed);
}

void backward(uint8_t speed) {
  digitalWrite(INPUT_1_LEFT, HIGH);
  digitalWrite(INPUT_2_LEFT, LOW);

  digitalWrite(INPUT_1_RIGHT, HIGH);
  digitalWrite(INPUT_2_RIGHT, LOW);

  analogWrite(ENABLE_RIGHT, speed);
  analogWrite(ENABLE_LEFT, speed);
}
#endif

/* Function that send an order to the right motor */
void orderLeft(uint8_t direction, uint8_t speed) {
  switch (direction) {
    case 0:
      // Stopping motors
      digitalWrite(INPUT_1_LEFT, LOW);
      digitalWrite(INPUT_2_LEFT, LOW);

      analogWrite(ENABLE_LEFT, 0);
      break;
    case 1:
      // Forward
      digitalWrite(INPUT_1_LEFT, LOW);
      digitalWrite(INPUT_2_LEFT, HIGH);

      analogWrite(ENABLE_LEFT, speed);
      break;
    case 2:
      // Backward
      digitalWrite(INPUT_1_LEFT, HIGH);
      digitalWrite(INPUT_2_LEFT, LOW);

      analogWrite(ENABLE_LEFT, speed);
      break;
  }
}

/* Function that send an order to the right motor */
void orderRight(uint8_t direction, uint8_t speed) {
  switch (direction) {
    case 0:
      // Stopping motors
      digitalWrite(INPUT_1_RIGHT, LOW);
      digitalWrite(INPUT_2_RIGHT, LOW);

      analogWrite(ENABLE_RIGHT, 0);
      break;
    case 1:
      // Forward
      digitalWrite(INPUT_1_RIGHT, LOW);
      digitalWrite(INPUT_2_RIGHT, HIGH);

      analogWrite(ENABLE_RIGHT, speed);
      break;
    case 2:
      // Backward
      digitalWrite(INPUT_1_RIGHT, HIGH);
      digitalWrite(INPUT_2_RIGHT, LOW);

      analogWrite(ENABLE_RIGHT, speed);
      break;
  }
}

/* Function that receive the bytes from the I2C */
void recv(int numBytes) {

#ifdef DEBUG
  Serial.println("Reading some data ...");
#endif

  // We should receive 4 bytes from the Rasp
  if (numBytes == 4) {
    Serial.println("Receiving new packet");

    uint8_t PWM_Left = Wire.read();
    uint8_t PWM_Right = Wire.read();
    uint8_t leftDirection = Wire.read();
    uint8_t rightDirection = Wire.read();

    timeout_timer = millis() + TIMEOUT_DELAY_MS;
#ifdef DEBUG
    Serial.print("PWM_Left : ");
    Serial.println(PWM_Left);

    Serial.print("PWM_Right : ");
    Serial.println(PWM_Right);

    Serial.print("leftDirection : ");
    Serial.println(leftDirection);

    Serial.print("rightDirection : ");
    Serial.println(rightDirection);
#endif

    orderLeft(leftDirection, PWM_Left);
    orderRight(rightDirection, PWM_Right);
  }

  Wire.flush();
  while (Wire.available()) Wire.read();
}
