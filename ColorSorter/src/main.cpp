#include <Arduino.h>
#include <ESP32Servo.h>

#include "colors.h"


int color;

Servo myservo;  // create servo object to control a servo
Servo sortToServo;
// 16 servo objects can be created on the ESP32

// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
// Possible PWM GPIO pins on the ESP32-S2: 0(used by on-board button),1-17,18(used by on-board LED),19-21,26,33-42
#define servoPin 26
#define servoPin 26
#define sortToServoPin 27

#define pos0 95
#define pos1 125
#define pos2 62
#define pos3 30
#define pos4 160

#define actual_zero 5


void setup() {
	// Allow allocation of all timers
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(servoPin, 500, 2430); // attaches the servo on pin 18 to the servo object
    sortToServo.setPeriodHertz(50);
    sortToServo.attach(sortToServoPin, 500, 2400);

    pin_setup();
    Serial.begin(9600);

    myservo.write(actual_zero);
    delay(1000);
}


void loop() {
	for (int pos = actual_zero; pos <= 90; pos += 1)
    { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(15);             // waits 15ms for the servo to reach the position
	}

    Serial.println("detecting");
    delay(100);
    color = detect_color(10);
    Serial.print("detected: "); Serial.println(color);

    // move sorting servo
    switch (color)
    {
    case 0:  // green
        sortToServo.write(pos0);
        break;
    
    case 1: // yellow    
        sortToServo.write(pos1);
        break;

    case 2: // orange
        sortToServo.write(pos2);
        break;
    
    case 3: // red
        sortToServo.write(pos3);
        break;
    
    case 4: // nothing / dark red
        sortToServo.write(pos4);
        break;

    default:
        break;
    }
	for (int pos = 90; pos <= 165; pos += 1)
    { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(15);             // waits 15ms for the servo to reach the position
	}

	for (int pos = 165; pos <= 175; pos += 1)
    { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(30);             // waits 15ms for the servo to reach the position
	}

    delay(300);
	for (int pos = 175; pos >= actual_zero; pos --)
    { // goes from 180 degrees to 0 degrees
		myservo.write(pos);    // tell servo to go to position in variable 'pos'
		delay(8);             // waits 15ms for the servo to reach the position
	}
    delay(100);
}
