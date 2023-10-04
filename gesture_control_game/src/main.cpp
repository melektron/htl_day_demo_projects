#include <Arduino.h>

#define STEPPER_PIN_1 26
#define STEPPER_PIN_2 25
#define STEPPER_PIN_3 33
#define STEPPER_PIN_4 32
#define T1 23
#define T2 22

#define X_MAX 1000
#define Y_MAX 1000
#define FULL_TURN 100
int step_number = 0;
int current_x_position = 0; 
int current_y_position = 0; 

void setup()
{
    pinMode(STEPPER_PIN_1, OUTPUT);
    pinMode(STEPPER_PIN_2, OUTPUT);
    pinMode(STEPPER_PIN_3, OUTPUT);
    pinMode(STEPPER_PIN_4, OUTPUT);
    pinMode(T1, INPUT_PULLUP);
    pinMode(T2, INPUT_PULLUP);
}

void OneStep(bool dir)
{
    if (dir)
    {
        switch (step_number)
        {
        case 0:
            digitalWrite(STEPPER_PIN_1, HIGH);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
        case 1:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, HIGH);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
        case 2:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, HIGH);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
        case 3:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, HIGH);
            break;
        }
    }
    else
    {
        switch (step_number)
        {
        case 0:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, HIGH);
            break;
        case 1:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, HIGH);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
        case 2:
            digitalWrite(STEPPER_PIN_1, LOW);
            digitalWrite(STEPPER_PIN_2, HIGH);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
            break;
        case 3:
            digitalWrite(STEPPER_PIN_1, HIGH);
            digitalWrite(STEPPER_PIN_2, LOW);
            digitalWrite(STEPPER_PIN_3, LOW);
            digitalWrite(STEPPER_PIN_4, LOW);
        }
    }
    step_number++;
    if (step_number > 3)
    {
        step_number = 0;
    }
}


void x_axis()
{
    if (digitalRead(T1) && current_x_position <= X_MAX)
    {
        for (int a = 0; a <= FULL_TURN; a++)
        {
            OneStep(true);
            delay(2);
        }
        current_x_position+=100; 
    }
    else if (!digitalRead(T1) && current_x_position >= X_MAX * (-1))
    {
        for (int a = 0; a <= FULL_TURN; a++)
        {
            OneStep(false);
            delay(2);
        }
        current_x_position-=100; 
    }
}

void y_axis()
{
    if (digitalRead(T1) && current_y_position <= Y_MAX)
    {
        for (int a = 0; a <= FULL_TURN; a++)
        {
            OneStep(true);
            delay(2);
        }
        current_x_position+=100; 
    }
    else if (!digitalRead(T1) && current_y_position >= Y_MAX * (-1))
    {
        for (int a = 0; a <= FULL_TURN; a++)
        {
            OneStep(false);
            delay(2);
        }
        current_y_position-=100; 
    }
}



void loop()
{
    x_axis(); 
    y_axis(); 
}