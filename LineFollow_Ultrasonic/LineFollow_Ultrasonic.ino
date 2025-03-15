/*
Follow a "rope" (black line) until the ultransonic sensor detects a raised portion of the rope to grab
*/

#include "MeMegaPi.h"
MeLineFollower lineFinder(PORT_5); /* Line Finder module can only be connected to PORT_3, PORT_4, PORT_5, PORT_6 of base shield. */
MeUltrasonicSensor ultraSensor(PORT_7); /* Ultrasonic module can ONLY be connected to port 3, 4, 6, 7, 8 of base shield. */

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorState = lineFinder.readSensors();
  switch(sensorState)
  {
    case S1_IN_S2_IN: Serial.println("Sensor 1 and 2 are inside of black line"); break;
    case S1_IN_S2_OUT: Serial.println("Sensor 2 is outside of black line"); break;
    case S1_OUT_S2_IN: Serial.println("Sensor 1 is outside of black line"); break;
    case S1_OUT_S2_OUT: Serial.println("Sensor 1 and 2 are outside of black line"); break;
    default: break;
  }
  Serial.print("Distance : ");
  Serial.print(ultraSensor.distanceCm() );
  Serial.println(" cm");
  delay(100); /* the minimal measure interval is 100 milliseconds */
}
