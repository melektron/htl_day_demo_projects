#include <Arduino.h>

#define X_STEPPER_PIN_1 26
#define X_STEPPER_PIN_2 25
#define X_STEPPER_PIN_3 33
#define X_STEPPER_PIN_4 32

#define Y_STEPPER_PIN_1 17
#define Y_STEPPER_PIN_2 18
#define Y_STEPPER_PIN_3 19
#define Y_STEPPER_PIN_4 27

#define T1 23
#define T2 22

#define X_MAX 1000
#define Y_MAX 1000
#define FULL_TURN 100

int step_number_x = 0;
int step_number_y = 0;
int current_x_position = 0; 
int current_y_position = 0; 

void setup()
{
    pinMode(X_STEPPER_PIN_2, OUTPUT);
    pinMode(X_STEPPER_PIN_3, OUTPUT);
    pinMode(X_STEPPER_PIN_1, OUTPUT);
    pinMode(X_STEPPER_PIN_4, OUTPUT);

    pinMode(Y_STEPPER_PIN_2, OUTPUT);
    pinMode(Y_STEPPER_PIN_3, OUTPUT);
    pinMode(Y_STEPPER_PIN_1, OUTPUT);
    pinMode(Y_STEPPER_PIN_4, OUTPUT);

    pinMode(T1, INPUT_PULLUP);
    pinMode(T2, INPUT_PULLUP);
    Serial.begin(115200);
}

void OneStep_X(bool dir)
{
    if (dir)
    {
        switch (step_number_x)
        {
        case 0:
            digitalWrite(X_STEPPER_PIN_1, HIGH);
            digitalWrite(X_STEPPER_PIN_2, LOW);
            digitalWrite(X_STEPPER_PIN_3, LOW);
            digitalWrite(X_STEPPER_PIN_4, LOW);
            break;
        case 1:
            digitalWrite(X_STEPPER_PIN_1, LOW);
            digitalWrite(X_STEPPER_PIN_2, HIGH);
            digitalWrite(X_STEPPER_PIN_3, LOW);
            digitalWrite(X_STEPPER_PIN_4, LOW);
            break;
        case 2:
            digitalWrite(X_STEPPER_PIN_1, LOW);
            digitalWrite(X_STEPPER_PIN_2, LOW);
            digitalWrite(X_STEPPER_PIN_3, HIGH);
            digitalWrite(X_STEPPER_PIN_4, LOW);
            break;
        case 3:
            digitalWrite(X_STEPPER_PIN_1, LOW);
            digitalWrite(X_STEPPER_PIN_2, LOW);
            digitalWrite(X_STEPPER_PIN_3, LOW);
            digitalWrite(X_STEPPER_PIN_4, HIGH);
            break;
        }
    }
    else
    {
        switch (step_number_x)
        {
        case 0:
            digitalWrite(X_STEPPER_PIN_1, LOW);
            digitalWrite(X_STEPPER_PIN_2, LOW);
            digitalWrite(X_STEPPER_PIN_3, LOW);
            digitalWrite(X_STEPPER_PIN_4, HIGH);
            break;
        case 1:
            digitalWrite(X_STEPPER_PIN_1, LOW);
            digitalWrite(X_STEPPER_PIN_2, LOW);
            digitalWrite(X_STEPPER_PIN_3, HIGH);
            digitalWrite(X_STEPPER_PIN_4, LOW);
            break;
        case 2:
            digitalWrite(X_STEPPER_PIN_1, LOW);
            digitalWrite(X_STEPPER_PIN_2, HIGH);
            digitalWrite(X_STEPPER_PIN_3, LOW);
            digitalWrite(X_STEPPER_PIN_4, LOW);
            break;
        case 3:
            digitalWrite(X_STEPPER_PIN_1, HIGH);
            digitalWrite(X_STEPPER_PIN_2, LOW);
            digitalWrite(X_STEPPER_PIN_3, LOW);
            digitalWrite(X_STEPPER_PIN_4, LOW);
        }
    }
    step_number_x++;
    if (step_number_x > 3)
    {
        step_number_x = 0;
    }
}

void OneStep_Y(bool dir)
{
    if (dir)
    {
        switch (step_number_y)
        {
        case 0:
            digitalWrite(Y_STEPPER_PIN_1, HIGH);
            digitalWrite(Y_STEPPER_PIN_2, LOW);
            digitalWrite(Y_STEPPER_PIN_3, LOW);
            digitalWrite(Y_STEPPER_PIN_4, LOW);
            break;
        case 1:
            digitalWrite(Y_STEPPER_PIN_1, LOW);
            digitalWrite(Y_STEPPER_PIN_2, HIGH);
            digitalWrite(Y_STEPPER_PIN_3, LOW);
            digitalWrite(Y_STEPPER_PIN_4, LOW);
            break;
        case 2:
            digitalWrite(Y_STEPPER_PIN_1, LOW);
            digitalWrite(Y_STEPPER_PIN_2, LOW);
            digitalWrite(Y_STEPPER_PIN_3, HIGH);
            digitalWrite(Y_STEPPER_PIN_4, LOW);
            break;
        case 3:
            digitalWrite(Y_STEPPER_PIN_1, LOW);
            digitalWrite(Y_STEPPER_PIN_2, LOW);
            digitalWrite(Y_STEPPER_PIN_3, LOW);
            digitalWrite(Y_STEPPER_PIN_4, HIGH);
            break;
        }
    }
    else
    {
        switch (step_number_y)
        {
        case 0:
            digitalWrite(Y_STEPPER_PIN_1, LOW);
            digitalWrite(Y_STEPPER_PIN_2, LOW);
            digitalWrite(Y_STEPPER_PIN_3, LOW);
            digitalWrite(Y_STEPPER_PIN_4, HIGH);
            break;
        case 1:
            digitalWrite(Y_STEPPER_PIN_1, LOW);
            digitalWrite(Y_STEPPER_PIN_2, LOW);
            digitalWrite(Y_STEPPER_PIN_3, HIGH);
            digitalWrite(Y_STEPPER_PIN_4, LOW);
            break;
        case 2:
            digitalWrite(Y_STEPPER_PIN_1, LOW);
            digitalWrite(Y_STEPPER_PIN_2, HIGH);
            digitalWrite(Y_STEPPER_PIN_3, LOW);
            digitalWrite(Y_STEPPER_PIN_4, LOW);
            break;
        case 3:
            digitalWrite(Y_STEPPER_PIN_1, HIGH);
            digitalWrite(Y_STEPPER_PIN_2, LOW);
            digitalWrite(Y_STEPPER_PIN_3, LOW);
            digitalWrite(Y_STEPPER_PIN_4, LOW);
        }
    }
    step_number_y++;
    if (step_number_y > 3)
    {
        step_number_y = 0;
    }
}


void x_axis()
{
    if (digitalRead(T1) && current_x_position <= X_MAX)
    {
        for (int a = 0; a <= FULL_TURN; a++)
        {
            OneStep_X(true);
            delay(2);
        }
        current_x_position+=100; 
    }
    else if (!digitalRead(T1) && current_x_position >= X_MAX * (-1))
    {
        for (int a = 0; a <= FULL_TURN; a++)
        {
            OneStep_X(false);
            delay(2);
        }
        current_x_position-=100; 
    }
}

void y_axis()
{
    if (digitalRead(T2) && current_y_position <= Y_MAX)
    {
        for (int a = 0; a <= FULL_TURN; a++)
        {
            OneStep_Y(true);
            delay(2);
        }
        current_y_position+=100; 
    }
    else if (!digitalRead(T2) && current_y_position >= Y_MAX * (-1))
    {
        for (int a = 0; a <= FULL_TURN; a++)
        {
            OneStep_Y(false);
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