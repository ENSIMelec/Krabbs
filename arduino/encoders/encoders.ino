/*
  This program is used to get the tick number for each encoder wheel for Krabbs
  see https://github.com/ENSIMelec/Krabbs

  It uses the Serial Port to communicate with the RapsberryPi.

  TODO : Depending on the speed limit, it could be nice to use the I2C bus to communicate.

  Protocol :
  // [StartByte]     [LSB][][][MSB]      [LSB][][][MSB]      [LSB][][][MSB]      [StopByte]
  //                   leftTicks           rightTicks         elapsedTime


  Author : Tom de Pasquale

  Last updated : May 14 2022
  Changing the protocol to use bytes instead of strings

*/

// Uncomment to activate debug mod
//#define DEBUG

// Interrupt pins
#define interLeftEncoder    0 //pin2 : interrupt 0 
#define interRightEncoder   1 //pin3 : interrupt 1 

#define LEFT 0
#define RIGHT 1

volatile long tickValues[2];
volatile long time;

#define COMMAND_READ_AND_RESET  0xFF
#define COMMAND_RESET           0xF0
#define START_BYTE              0xA5
#define STOP_BYTE               0x5A

void setup()
{
  Serial.begin(115200);

  // Set the tick values to be 0 at start
  reset();

  // Attach interrupt functions for each encoding wheel
  attachInterrupt(interRightEncoder, countRightTicks, RISING);
  attachInterrupt(interLeftEncoder, countLeftTicks, RISING);
}

/* Reset the tick values */
void reset()
{
  time = micros();

  tickValues[LEFT] = 0;
  tickValues[RIGHT] = 0;
}

void loop()
{

#ifdef DEBUG
  Serial.print("Left ticks : ");
  Serial.print(tickValues[LEFT]);
  Serial.print("\tRight ticks : ");
  Serial.println(tickValues[RIGHT]);
#endif

  if (Serial.available()) {
    unsigned int data = Serial.read();
    switch (data) {
      case COMMAND_READ_AND_RESET :
        time = millis();

        Serial.write(START_BYTE);
        
        Serial.write(tickValues[LEFT]);
        Serial.write(tickValues[LEFT] >> 8);
        Serial.write(tickValues[LEFT] >> 16);
        Serial.write(tickValues[LEFT] >> 24);

        Serial.write(tickValues[RIGHT]);
        Serial.write(tickValues[RIGHT] >> 8);
        Serial.write(tickValues[RIGHT] >> 16);
        Serial.write(tickValues[RIGHT] >> 24);

        Serial.write(time);
        Serial.write(time >> 8);
        Serial.write(time >> 16);
        Serial.write(time >> 24);

        Serial.write(STOP_BYTE);
        break;

      case COMMAND_RESET :
        reset();
        break;
    }
  }
}

/* Increments or decrements the right tick value */
void countRightTicks ()
{
  // Note : this has been swapped for Kiroulpa

  //if (digitalRead(CANAL_B_RIGHT) == HIGH)
  if (PINB & 0x01)
    tickValues[RIGHT]++;
  else
    tickValues[RIGHT]--;
}

/* Increments or decrements the right tick value */
void countLeftTicks ()
{
  //if (digitalRead(CANAL_B_LEFT) == HIGH)
  if (PIND & 0x80)
    tickValues[LEFT]--;
  else
    tickValues[LEFT]++;
}
