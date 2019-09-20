// Imports
#include <SoftwareSerial.h>
#include <Stepper.h>

// Variables
SoftwareSerial HM10 (0,1);
const int wristSPR = 300; // change this to fit the number of steps per revolution
const int baseSPR = 300; 
Stepper baseStepper(baseSPR, 10, 11, 12, 13);
Stepper wristStepper(wristSPR, 6, 7, 8, 9);
Servo baseServo;
Servo shoulderServo;
Servo elbowServo;
Servo gripServo;
byte data;
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
  data = 0x00;
  basePos = 0;
  elbowPos = 0;
  shoulderPos = 0;
  gripPos = 0;
}

// Continous run after start
void loop() {
    exit_inner_loop: ;    
        setServoPos();
        HM10.listen(); // Listen for info
        while (true) {
            if (HM10.available() > 0) {
                data = HM10.read();
            }
            switch (data) {
                case 0x00: // BREAK WHILE LOOP
                    goto exit_inner_loop;
                case 0x01: // BASE TURN RIGHT (STEPPER)
                    int sensorReading = analogRead(A0);  // map it to a range from 0 to 100:
                    int motorSpeed = map(sensorReading, 0, 1023, 0, 100); // set the motor speed:
                    if (motorSpeed > 0) {
                        baseStepper.setSpeed(motorSpeed);   // step 1/100 of a revolution:
                        baseStepper.step(baseSPR / 100);
                        Serial.println("Base Turning Right");
                    }
                    break;
                case 0x02: // BASE TURN LEFT (STEPPER)
                    int sensorReading = analogRead(A0);   
                    int motorSpeed = map(sensorReading, 0, 1023, 0, 100);  
                    if (motorSpeed > 0) {
                        baseStepper.setSpeed(motorSpeed);   
                        baseStepper.step(-baseSPR / 100);
                        Serial.println("Base Turning Left");
                    }
                    break;
                case 0x03: // WRIST TURN RIGHT (STEPPER)
                    int sensorReading = analogRead(A0);  
                    int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
                    if (motorSpeed > 0) {
                        wristStepper.setSpeed(motorSpeed);
                        wristStepper.step(-baseSPR / 100);
                        Serial.println("Wrist Turning Right");
                    }
                    break;
                case 0x04: // WRIST TURN LEFT (STEPPER)
                    int sensorReading = analogRead(A0);
                    int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
                    if (motorSpeed > 0) {
                        wristStepper.setSpeed(motorSpeed);
                        wristStepper.step(baseSPR / 100);
                        Serial.println("Wrist Turning Left");
                    }
                    break;
                case 0x05: // ELBOW MOVEMENT FORWARD (SERVO)
                    if (elbowPos < 180) {
                        elbowPos++;
                        Serial.println("Elbow Moving Foward");
                    }
                    break;
                case 0x06: // ELBOW MOVEMENT BACK (SERVO)
                    if (elbowPos > 0) {
                        elbowPos--;
                        Serial.println("Elbow Moving Back");
                    }
                    break;
                case 0x07: // SHOULDER MOVEMENT FORWARD (SERVO)
                    if (shoulderPos < 180) {
                        shoulderPos++;
                        Serial.println("Shoulder Moving Foward");
                    }
                    break;
                case 0x08: // SHOULDER MOVEMENT BACK (SERVO)
                    if (shoulderPos > 0) {
                        shoulderPos--;
                        Serial.println("Shoulder Moving Back");
                    }
                    break;
                case 0x09: // GRIP CLOSE (SERVO)
                    if (gripPos < 180) {
                        gripPos++;
                        Serial.println("Grip Closing");
                    }
                    break;
                case 0x0A: // GRIP OPEN (SERVO)
                    if (gripPos > 0) {
                        gripPos--;
                        Serial.println("Grip Opening");
                    }
                    break;
                case 0x0B: // BASE MOVEMENT FORWARD (SERVO)
                    if (basePos < 180) {
                        basePos++;
                        Serial.println("Base Moving Foward");
                    }
                    break;
                case 0x0C: // BASE MOVEMENT BACK (SERVO)
                    if (basePos > 0) {
                        basePos--;
                        Serial.println("Base Moving Back");
                    }
                    break;
                default:
                    break;
            }
            // SET SERVO POSITIONS
            setServoPos();
        }
}


/*****************************************************************************************************/


        // Serial.println(data); // test to verify data
        // // BREAK WHILE LOOP
        // if (data == 0x00) {
        //     goto exit_inner_loop;
        // }
        // // BASE TURN RIGHT (STEPPER)
        // if (data == 0x01) {
        //     int sensorReading = analogRead(A0);  // map it to a range from 0 to 100:
        //     int motorSpeed = map(sensorReading, 0, 1023, 0, 100); // set the motor speed:
        //     if (motorSpeed > 0) {
        //         baseStepper.setSpeed(motorSpeed);   // step 1/100 of a revolution:
        //         baseStepper.step(baseSPR / 100);
        //         Serial.println("Base Turning Right");
        //     }
        // }
        // // BASE TURN LEFT (STEPPER)
        // if (data == 0x02) {
        //     int sensorReading = analogRead(A0);   
        //     int motorSpeed = map(sensorReading, 0, 1023, 0, 100);  
        //     if (motorSpeed > 0) {
        //         baseStepper.setSpeed(motorSpeed);   
        //         baseStepper.step(-baseSPR / 100);
        //         Serial.println("Base Turning Left");
        //     }
        // }
        // //WRIST TURN RIGHT (STEPPER)
        // if (data == 0x03) {
        //     int sensorReading = analogRead(A0);  
        //     int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
        //     if (motorSpeed > 0) {
        //         wristStepper.setSpeed(motorSpeed);
        //         wristStepper.step(-baseSPR / 100);
        //         Serial.println("Wrist Turning Right");
        //     }
        // }
        //WRIST TURN LEFT (STEPPER)
        // if (data == 0x04) {
        //     int sensorReading = analogRead(A0);
        //     int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
        //     if (motorSpeed > 0) {
        //         wristStepper.setSpeed(motorSpeed);
        //         wristStepper.step(baseSPR / 100);
        //         Serial.println("Wrist Turning Left");
        //     }
        // }
        // // ELBOW MOVEMENT (SERVO)
        // if (data == 0x05 && elbowPos < 180) {
        //     elbowPos++;
        //     Serial.println("Elbow Moving Foward");
        // }
        // if (data == 0x06 && elbowPos > 0) {
        //     elbowPos--;
        //     Serial.println("Elbow Moving Back");
        // }
        // // SHOULDER MOVEMENT (SERVO)
        // if (data == 0x07 && shoulderPos < 180) {
        //     shoulderPos++;
        //     Serial.println("Shoulder Moving Foward");
        // }
        // if (data == 0x08 && shoulderPos > 0) {
        //     shoulderPos--;
        //     Serial.println("Shoulder Moving Back");
        // }
        // // GRIP MOVEMENT (SERVO)
        // if (data == 0x09 && gripPos < 180) {
        //     gripPos++;
        //     Serial.println("Grip Closing");
        // }
        // if (data == 0x0A && gripPos > 0) {
        //     gripPos--;
        //     Serial.println("Grip Opening");
        // }
        // //  BASE MOVEMENT (SERVO)
        // if (data == 0x0B && basePos < 180) {
        //     basePos++;
        //     Serial.println("Base Moving Foward");
        // }
        // if (data == 0x0C && basePos > 0) {
        //     basePos--;
        //     Serial.println("Base Moving Back");
        // }
        // SET SERVO POSITIONS
//         setServoPos();
//     }
// }

    


/*****************************************************************************************************/    
    
    
// while(HM10.available() > 0 ){ // While there is info in buffer, do stuff (necessary loop)
//     byte data = HM10.read();
// }
// if (data == 0x10) {
//     digitalWrite(LED, HIGH);  
// }
// if (/*some condition*/) {
//     byte d[1] = {0x20};
//     HM10.write(d, sizeof(d)); // Communicates to the bluetooth device which will then push data to the phone
// }


//     HM10.listen(); // Listen for info
//     setServoPos();
//     if (HM10.available() > 0 ) {
//         while(HM10.available() > 0 ) {
//             data[0] = HM10.read();

//             //STEPPER CONTROL
//             {
//                 //BASE TURN RIGHT  
//                 if (data==0) {
//                     int sensorReading = analogRead(A0);  // map it to a range from 0 to 100:
//                     int motorSpeed = map(sensorReading, 0, 1023, 0, 100); // set the motor speed:
//                     if (motorSpeed > 0) {
//                         baseStepper.setSpeed(motorSpeed);   // step 1/100 of a revolution:
//                         baseStepper.step(baseSPR / 100);
//                     }
//                 }

//                 //BASE TURN LEFT
//                 if (data==1) {
//                     int sensorReading = analogRead(A0);   
//                     int motorSpeed = map(sensorReading, 0, 1023, 0, 100);  
//                     if (motorSpeed > 0) {
//                         baseStepper.setSpeed(motorSpeed);   
//                         baseStepper.step(-baseSPR / 100);
//                     }
//                 }
                
//                 //WRIST TURN LEFT
//                 if (data==2) {
//                     int sensorReading = analogRead(A0);  
//                     int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
//                     if (motorSpeed > 0) {
//                         wristStepper.setSpeed(motorSpeed);
//                         wristStepper.step(-baseSPR / 100);
//                     }
//                 }
                
//                 //WRIST TURN RIGHT 
//                 if (data==3) {
//                     int sensorReading = analogRead(A0);
//                     int motorSpeed = map(sensorReading, 0, 1023, 0, 100);
//                     if (motorSpeed > 0) {
//                         wristStepper.setSpeed(motorSpeed);
//                         wristStepper.step(baseSPR / 100);
//                     }
//                 }
//             }

//             //SERVO CONTROL
//             {
//                 if (data == 4 && elbowPos < 180) {
//                     elbowPos++;
//                 }
//                 if (data == 5 && elbowPos > 0) {
//                     elbowPos--;
//                 }
//                 //do these cases for all the servos
//                 //add in the if cases for the stepper motors
//                 setServoPos()

//             }
//         }
//    }
  
}