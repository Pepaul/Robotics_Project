/*
Follow a "rope" (black line) until the ultransonic sensor detects a raised portion of the rope to grab
*/

#include "MeMegaPi.h"

uint8_t motorSpeed = 80;

MeLineFollower lineFinder(PORT_5); /* Line Finder module can only be connected to PORT_3, PORT_4, PORT_5, PORT_6 of base shield. */
MeUltrasonicSensor ultraSensor(PORT_7); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */

MeMegaPiDCMotor motor1(PORT1B);
MeMegaPiDCMotor motor2(PORT2B);
MeMegaPiDCMotor motor3(PORT3B);
MeMegaPiDCMotor motor4(PORT4B);

enum Direction{
  LEFT,
  RIGHT,
  STRAIGHT
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

  //Negative means clockwise
  //Forward
  motor1.run(-motorSpeed); /* value: between -255 and 255. */
  motor2.run(motorSpeed); /* value: between -255 and 255. */
  delay(500);
  motor1.stop();
  motor2.stop();
  delay(100);

  int sensorState = lineFinder.readSensors();
  switch(sensorState) //test
  {
    case S1_IN_S2_IN:
    //Serial.println("Sensor 1 and 2 are inside of black line"); break;
    case S1_IN_S2_OUT: Serial.println("Sensor 2 is outside of black line"); break;
    case S1_OUT_S2_IN: Serial.println("Sensor 1 is outside of black line"); break;
    case S1_OUT_S2_OUT: Serial.println("Sensor 1 and 2 are outside of black line"); break;
    default: break;
  }
  Serial.print("Distance : ");
  Serial.print(ultraSensor.distanceCm() );
  Serial.println(" cm");
  delay(300); /* the minimal measure interval is 100 milliseconds */
}
