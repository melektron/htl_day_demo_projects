/*
ELEKTRON © 2022
Written by Matteo Reiter
www.elektron.work
11.10.22, 14:55

sorter thread
*/

#include <ESP32Servo.h>
#include "sorter.h"
#include "colors.h"

namespace sorter
{
    void thread_fn(void *_args);

    TaskHandle_t sorter_thread_h;

    bool currently_running = false;

    int color = 4;
};

Servo myservo;
Servo sortToServo;

#define servoPin 26
#define sortToServoPin 27

#define pos0 95
#define pos1 125
#define pos2 62
#define pos3 30
#define pos4 160

#define actual_zero 10

void sorter::init()
{
    // Allow allocation of all timers
    myservo.setPeriodHertz(50);          // standard 50 hz servo
    myservo.attach(servoPin, 550, 2430); // attaches the servo on pin 18 to the servo object
    sortToServo.setPeriodHertz(50);
    sortToServo.attach(sortToServoPin, 500, 2400);
    myservo.write(actual_zero);
}

void sorter::start_thread()
{
    xTaskCreatePinnedToCore(
        thread_fn,
        "sorter",
        10000,
        nullptr,
        1,
        &sorter_thread_h,
        1);
}

void sorter::thread_fn(void *_args)
{
    for (;;)
    {
        if (!currently_running)
        {
            delay(100); // thread timeout
            continue;
        };

        delay(1000);

        for (int pos = actual_zero; pos <= 95; pos += 1)
        { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            myservo.write(pos); // tell servo to go to position in variable 'pos'
            delay(15);          // waits 15ms for the servo to reach the position
        }

        delay(500);

        color = colors::detect_color(10);
        //Serial.print("detected: ");
        //Serial.println(color);

        delay(500);

        // move sorting servo
        switch (color)
        {
        case 0: // green
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
            myservo.write(pos); // tell servo to go to position in variable 'pos'
            delay(15);          // waits 15ms for the servo to reach the position
        }

        for (int pos = 165; pos <= 180; pos += 1)
        { // goes from 0 degrees to 180 degrees
            // in steps of 1 degree
            myservo.write(pos); // tell servo to go to position in variable 'pos'
            delay(30);          // waits 15ms for the servo to reach the position
        }

        delay(300);
        for (int pos = 175; pos >= actual_zero; pos--)
        {                       // goes from 180 degrees to 0 degrees
            myservo.write(pos); // tell servo to go to position in variable 'pos'
            delay(8);           // waits 15ms for the servo to reach the position
        }
        delay(100);
    }

    vTaskDelete(NULL);
}

void sorter::on()
{
    currently_running = true;
}

void sorter::off()
{
    currently_running = false;
}

int sorter::get_last_color()
{
    return color;
}