  /*
   This program is used to get the tick number for each encoder wheel for Krabbs
   see https://github.com/ENSIMelec/Krabbs

   It uses the Serial Port to communicate with the RapsberryPi.

   TODO : Depending on the speed limit, it could be nice to use the I2C bus to communicate.

   Author : Tom de Pasquale

   Last updated : March 03 2022
   Reformating the code to match with recomandations and adding comments.

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
    char data = Serial.read();
    switch (data) {
      case 'C' :
        time = micros();
        Serial.print("?");
        Serial.print(tickValues[LEFT]);
        Serial.print(",");
        Serial.print(tickValues[RIGHT]);
        Serial.print(":");
        Serial.print(time);
        Serial.print(";");
        break;

      case 'R' :
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
