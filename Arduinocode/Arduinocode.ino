// Imports
#include <SoftwareSerial.h>
#include <Stepper.h>
#include <Servo.h>

// Variables
SoftwareSerial HM10 (0,1);
const float wristSPR = 300;
const float baseSPR = 300; 
Stepper baseStepper(baseSPR, 10, 12, 11, 13);
Stepper wristStepper(wristSPR, 6, 8, 7, 9);
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo gripServo;
int data;
int basePos;
int elbowPos;
int shoulderPos;
int gripPos;


// Utility function
void setServoPos() {
    gripServo.write(gripPos);
    elbowServo.write(elbowPos);
    shoulderServo.write(shoulderPos);
    baseServo.write(basePos);
}

// Run at start
void setup() {
    Serial.begin(9600);
    HM10.begin(9600);
    data = 0;
    basePos = 90;
    elbowPos = 90;
    shoulderPos = 90;
    gripPos = 90;
    baseServo.attach(5);
    shoulderServo.attach(4); 
    elbowServo.attach(3);
    gripServo.attach(2);
}

// Continous run after start
void loop() {
    setServoPos();
    while (true) {
        HM10.listen(); // Listen for info
        if (HM10.available() > 0) {
            data = HM10.read();
        }
        Serial.println(data); // test to verify data
        // BREAK WHILE LOOP
        if (data == 0) {
            break;
        }
        // BASE TURN RIGHT (STEPPER)
        else if (data == 1) {
            int sensorReading = analogRead(A0);  // map it to a range from 0 to 100:
            int motorSpeed = map(sensorReading, 0, 1023, 0, 100); // set the motor speed:
            if (motorSpeed > 0) {
                baseStepper.setSpeed(motorSpeed);   // step 1/100 of a revolution:
                baseStepper.step(baseSPR / 100);
                Serial.println("Base Turning Right");
            }
            Serial.println("Base Turning Right");
        }
        // BASE TURN LEFT (STEPPER)
        else if (data == 2) {
            int sensorReading = analogRead(A0);   
            int motorSpeed = map(sensorReading, 0, 1023, 0, 100);  
            if (motorSpeed > 0) {
                baseStepper.setSpeed(motorSpeed);   
                baseStepper.step(-baseSPR / 100);
                Serial.println("Base Turning Left");
            }
            Serial.println("Base Turning Left");
        }
        // WRIST TURN RIGHT (STEPPER)
        else if (data == 3) {
             int sensorReading = analogRead(A0);  
             int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
             if (motorSpeed > 0) {
                 wristStepper.setSpeed(motorSpeed);
                 wristStepper.step(baseSPR / 100);
                 Serial.println("Wrist Turning Right");
             }
            Serial.println("Wrist Turning Right");
        }
        // WRIST TURN LEFT (STEPPER)
        else if (data == 4) {
             int sensorReading = analogRead(A0);
             int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
             if (motorSpeed > 0) {
                 wristStepper.setSpeed(motorSpeed);
                 wristStepper.step(-baseSPR / 100);
                 Serial.println("Wrist Turning Left");
             }
            Serial.println("Wrist Turning Left");
        }
        // ELBOW MOVEMENT (SERVO)
        else if (data == 5 && elbowPos < 180) {
            elbowPos++;
            Serial.println("Elbow Moving Foward");
        }
        else if (data == 6 && elbowPos > 0) {
            elbowPos--;
            Serial.println("Elbow Moving Back");
        }
        // SHOULDER MOVEMENT (SERVO)
        else if (data == 7 && shoulderPos < 180) {
            shoulderPos++;
            Serial.println("Shoulder Moving Foward");
        }
        else if (data == 8 && shoulderPos > 0) {
            shoulderPos--;
            Serial.println("Shoulder Moving Back");
        }
        // GRIP MOVEMENT (SERVO)
        else if (data == 9 && gripPos < 180) {
            gripPos++;
            Serial.println("Grip Closing");
        }
        else if (data == 10 && gripPos > 0) {
            gripPos--;
            Serial.println("Grip Opening");
        }
        // BASE MOVEMENT (SERVO)
        else if (data == 11 && basePos < 180) {
            basePos++;
            Serial.println("Base Moving Foward");
        }
        else if (data == 12 && basePos > 0) {
            basePos--;
            Serial.println("Base Moving Back");
        }
        // DISCONNECTED
        else if (data == 84) {
            setServoPos();
        }
        // SET SERVO POSITIONS
        setServoPos();
    }
}
