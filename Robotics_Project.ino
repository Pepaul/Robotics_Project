#include "MeMegaPi.h"

MeMegaPiDCMotor motor1(PORT1B); // Right Wheel
MeMegaPiDCMotor motor2(PORT2B); // Left Wheel
MeMegaPiDCMotor motor3(PORT3B); // Joint (Gripper Arm Movement)
MeMegaPiDCMotor motor4(PORT4B); // Gripper

MeUltrasonicSensor ultraSensor(PORT_7); // Ultrasonic sensor port

<<<<<<< Updated upstream
uint8_t motorSpeed = 90;      // Speed for forward movement
uint8_t rotationSpeed = 90;   // Speed for rotating in place
uint8_t armSpeed = 50;        // Slower speed for precise arm movement

uint16_t detectionDistanceFar = 35;   // Initial detection stage distance
uint16_t detectionDistanceClose = 12; // Final pickup distance

uint8_t leftMotorSpeed = 80;     // Adjust this to balance movement
uint8_t rightMotorSpeed = 90;    // Reduce slightly if the right motor is faster
=======
uint8_t motorSpeed = 90;     // Speed for forward movement
uint8_t rotationSpeed = 70; // Speed for rotating in place
uint8_t armSpeed = 50;       // Slower speed for precise arm movement
uint16_t detectionDistance = 25; // Object detection distance
uint16_t grippingDistance = 13; // Object close enough to grip

float alpha = 0.8; //Used for rolling average of sensor reading
float previousDistance = 400;
float averageDistance;
>>>>>>> Stashed changes

// Function to initialize arm position
void initializeArmPosition() {
    Serial.println("Initializing Arm Position...");
    motor3.run(50);
    motor4.run(80);
    delay(6000);
    motor4.stop();

    motor3.run(-50); // Controlled descent speed
    delay(3500);
    motor3.stop();

    Serial.println("Arm Initialized at Home Position");
}

// Function that executes the object pickup sequence
void objectFound() {
    motor1.stop();
    motor2.stop();

    delay(500); // Pause before gripping process

    motor3.run(-50);  
    delay(800);       
    motor3.stop();

    motor4.run(-120);  
    delay(3000);       
    motor4.stop();

    motor3.run(100); 
    delay(2500);     
    motor3.stop();

    delay(500);
    motor1.run(-rightMotorSpeed);
    motor2.run(leftMotorSpeed);
    delay(1000);
    motor1.stop();
    motor2.stop();

    delay(10000);
}

<<<<<<< Updated upstream
// Function to hone in on an object
void honeInOnObject() {
    float minDistance = 999;  // Start with an impossible high value
    int bestDirection = 0;    // Tracks the optimal direction

    // Rotate Left Slightly and Scan
    motor1.run(rightMotorSpeed);
    motor2.run(leftMotorSpeed);
    delay(300);  // Small rotation step
    float leftDistance = ultraSensor.distanceCm();
    if (leftDistance < minDistance) {
        minDistance = leftDistance;
        bestDirection = -1;  // Track left as the best path
=======
//Try to find the local minumum
void wiggle() {
  float distance = ultraSensor.distanceCm();
  float minimum = 400.0;
  while (distance >= minimum && distance < grippingDistance) {
    if (distance < minimum) {
      minimum = distance;
    }
    motor1.run(10);
    motor2.run(10);
    delay(100);
    motor1.stop();
    motor2.stop();
    //motor1.run(-rotationSpeed);
    //motor2.run(-rotationSpeed);
    //delay(150);
    //motor1.stop();
    //motor2.stop();
    distance = ultraSensor.distanceCm();
  }
}
// Function to move toward the detected object
void moveTowardObject() {
    Serial.println("Moving Toward Object...");

    motor1.run(-motorSpeed/2);
    motor2.run(motorSpeed/2);

    // Continue moving until object is 14 cm away
    while (true) {
        float distance = ultraSensor.distanceCm();
        //averageDistance = alpha*distance + (1-alpha)*previousDistance;
        
        //if (averageDistance > 0 && averageDistance <= detectionDistance) {
        if (distance > 0 && distance <= grippingDistance) {
            Serial.println("Object Reached! Engaging Pickup Process...");
            //wiggle();
            motor1.stop();
            motor2.stop();
            objectFound();
            return;
        }
        previousDistance = distance;
        delay(100);  // Delay for stable distance readings
>>>>>>> Stashed changes
    }

    // Return to Center
    motor1.run(-rightMotorSpeed);
    motor2.run(-leftMotorSpeed);
    delay(300);

    // Rotate Right Slightly and Scan
    motor1.run(-rightMotorSpeed);
    motor2.run(-leftMotorSpeed);
    delay(300);
    float rightDistance = ultraSensor.distanceCm();
    if (rightDistance < minDistance) {
        minDistance = rightDistance;
        bestDirection = 1;  // Track right as the best path
    }

    // Return to Center
    motor1.run(rightMotorSpeed);
    motor2.run(leftMotorSpeed);
    delay(300);

    // Move slightly in the optimal direction
    if (bestDirection == -1) {
        Serial.println("Moving Slightly Left to Align");
        motor1.run(rightMotorSpeed);
        motor2.run(leftMotorSpeed);
        delay(200);  // Small adjustment to the left
    } else if (bestDirection == 1) {
        Serial.println("Moving Slightly Right to Align");
        motor1.run(-rightMotorSpeed);
        motor2.run(-leftMotorSpeed);
        delay(200);  // Small adjustment to the right
    }

    // Continue moving forward until 13cm away
    Serial.println("Moving Forward to Final Pickup Position...");
    motor1.run(-rightMotorSpeed);
    motor2.run(leftMotorSpeed);

    while (ultraSensor.distanceCm() > detectionDistanceClose) {
        delay(40); // Continuously check distance
    }

    motor1.stop();
    motor2.stop();
    objectFound();
}

// Function to rotate and scan for objects
bool scanForObjects() {
    float distance;

    // Rotate Left while scanning
    Serial.println("Scanning Left...");
    motor1.run(rightMotorSpeed);
    motor2.run(leftMotorSpeed);

<<<<<<< Updated upstream
    unsigned long startTime = millis();
    while (millis() - startTime < 800) {
=======
    //unsigned long startTime = millis();  // Track how long the scan runs
    //while (millis() - startTime < 800) { // Scan for 800ms (adjust for desired turn angle)
>>>>>>> Stashed changes
        distance = ultraSensor.distanceCm();

        if (distance > 0 && distance <= detectionDistanceFar) {
            Serial.println("Object Detected (Left Side)!");
            delay(200);
            motor1.stop();
            motor2.stop();
            honeInOnObject();
            return true;
        }
<<<<<<< Updated upstream

        delay(50);  // Short delay for stability during scanning
    }

=======
        previousDistance = distance;
        delay(100);  // Short delay for stability during scanning
    //}
    /*
>>>>>>> Stashed changes
    // Return to Center
    motor1.run(-rightMotorSpeed);
    motor2.run(-leftMotorSpeed);
    delay(800); // Return to the original position

    // Rotate Right
    Serial.println("Scanning Right...");
    motor1.run(-rightMotorSpeed);
    motor2.run(-leftMotorSpeed);

    startTime = millis();
    while (millis() - startTime < 800) {
        distance = ultraSensor.distanceCm();

        if (distance > 0 && distance <= detectionDistanceFar) {
            Serial.println("Object Detected (Right Side)!");
            motor1.stop();
            motor2.stop();
            honeInOnObject();
            return true;
        }

        delay(50); // Short delay for stability during scanning
    }

    // Return to Center
    motor1.run(rightMotorSpeed);
    motor2.run(leftMotorSpeed);
    delay(800);

    // Stop momentarily
    motor1.stop();
    motor2.stop();
    delay(50);
    */
    return false; // No object detected during scanning
}

void setup() {
    Serial.begin(9600);
    initializeArmPosition();
}

void loop() {
    // Continuously move forward
<<<<<<< Updated upstream
    motor1.run(-rightMotorSpeed);
    motor2.run(leftMotorSpeed);
=======
    /*
    motor1.run(-motorSpeed);
    motor2.run(motorSpeed);
>>>>>>> Stashed changes
    delay(750);
    */
    // Check for an object directly in front
    float distance = ultraSensor.distanceCm();

    if (distance > 0 && distance <= detectionDistanceFar) {
        Serial.println("Object Detected (Initial Detection)!");
        honeInOnObject();
    } else {
        // Periodically scan the surroundings
        if (scanForObjects()) {
            delay(1000);
        }
    }

    delay(100); // Short delay to stabilize sensor readings
}
