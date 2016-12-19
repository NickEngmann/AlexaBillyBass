/*
  Make a DC Motor Move to Sound.
   This example code is in the public domain.
   Created by Donald Bell, Maker Project Lab (2016).
   Based on Sound to Servo by Cenk Özdemir (2012)
   and DCMotorTest by Adafruit
*/
// include the Adafruit motor shield library
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Or, create it with a different I2C address (say for stacking)
// Adafruit_MotorShield AFMS = Adafruit_MotorShield(0x61);

// Select which 'port' M1, M2, M3 or M4. In this case, M1 for mouth and M2 for tail
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);
Adafruit_DCMotor *myOtherMotor = AFMS.getMotor(2);

// Some other Variables we need
int SoundInPin = A0;
int LedPin = 12; //in case you want an LED to activate while mouth moves

// the setup routine runs once when you press reset:
void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps


  AFMS.begin();  // create with the default frequency 1.6KHz
  //AFMS.begin(1000);  // OR with a different frequency, say 1KHz

  // Set the speed to start, from 0 (off) to 255 (max speed)
  myMotor->setSpeed(0); //mouth motor
  myMotor->run(FORWARD);
  // turn on motor
  myMotor->run(RELEASE);
  pinMode(SoundInPin, INPUT);
  pinMode(LedPin, OUTPUT);
  myOtherMotor->setSpeed(0); //tail motor
  myOtherMotor->run(FORWARD);
  // turn on motor
  myOtherMotor->run(RELEASE);
  pinMode(SoundInPin, INPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  uint8_t i;

  // read the input on analog pin 0:
  int sensorValue = analogRead(SoundInPin);
  // we Map another value of this for LED that can be a integer betwen 0..255
  int LEDValue = map(sensorValue, 0, 512, 0, 255);
  // We Map it here down to the possible range of  movement.
  sensorValue = map(sensorValue, 0, 512, 0, 180);
  // note normally the 512 is 1023 because of analog reading should go so far, but I changed that to get better readings.
  int MoveDelayValue = map(sensorValue, 0, 255, 0, sensorValue);

  // maping the same reading a little bit more down to calculate the time your motor gets
  if (sensorValue > 10) { // to cut off some static readings
    delay(1);  // a static delay to smooth things out...
    // now move the motor
    myMotor->run(FORWARD);
    for (i = 140; i < 255; i++) {
      myMotor->setSpeed(i);

    }

    //for (i=200; i!=0; i--) {
    //    myMotor->setSpeed(i);
    //    delay(10);
    //  }

    analogWrite(LedPin, sensorValue);
    // and do that move in this delay time

    myMotor->run(RELEASE);
    myOtherMotor->run(RELEASE);
    delay(1);
  } // Done.
  // turn off the led again.
  analogWrite(LedPin, 0);
  // and this repeats all the time.
}

