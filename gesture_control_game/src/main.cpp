#include <Arduino.h>
#include "stepper/stepper.hpp"

#define T1 23
#define T2 22

#define MAX 1024
#define FULL_TURN 100

stepper::Stepper x_stepper({26, 25, 33, 32}, 2);
stepper::Stepper y_stepper({17, 18, 19, 27}, 2);


void setup()
{
    pinMode(T1, INPUT_PULLUP);
    pinMode(T2, INPUT_PULLUP);

    Serial.begin(115200);
    delay(3000);
    Serial.println("starting");
}


void x_axis()
{
    if (digitalRead(T1) && x_stepper.getPosition() <= MAX)
    {
        x_stepper.step(1);
    }
    else if (x_stepper.getPosition() >= -MAX)
    {
        x_stepper.step(-1);
    }
}


void y_axis()
{
    if (digitalRead(T2) && y_stepper.getPosition() <= MAX)
    {
        y_stepper.step(1);
    }
    else if (y_stepper.getPosition() >= -MAX)
    {
        y_stepper.step(-1);
    }
}



void loop()
{
    x_axis(); 
    y_axis();
}