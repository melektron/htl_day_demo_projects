#include "stepper.hpp"
#include <math.h>


using namespace stepper;

const bool stepper::steps[4][4] = {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
};


Stepper::Stepper(
    stepper_pins_t pins,
    double speed,
    int starting_position
)
    : p(pins), s(speed), current_position(starting_position)
{
    target_position = current_position;

    pinMode(p.a, OUTPUT);
    pinMode(p.b, OUTPUT);
    pinMode(p.c, OUTPUT);
    pinMode(p.d, OUTPUT);
};


int modulu(int value, int m)
{
    // return ((value < 0) ? m-1 : 0) + value % m;
    // return (int)((int)(value) % m);
	unsigned int tmp = *((unsigned int*) &value) % m;  // may only work on xtensa 32 LX6
	return *((int*) &tmp);
}


void Stepper::stepOnce(bool direction)
{
    current_position += direction ? -1 : 1;

    for (int pin_index = 0; pin_index < 4; pin_index++)
    {
        digitalWrite(p.as_array[pin_index], steps[modulu(current_position, 4)][pin_index]);
    }

    delay(4  / s);
}


void Stepper::update()
{
    int diff = target_position - current_position;
    diff = (diff > 0) ? max(diff, max_steps_per_update) : min(diff, -max_steps_per_update);

    step(diff);
}


void Stepper::step(int n)
{
    for (int i = 0; i < n; i++)
    {
        stepOnce();
    };

    for (int i = 0; i > n; i--)
    {
        stepOnce(true);
    };
}


void Stepper::setPosition(int position)
{
    current_position = position;
}

void Stepper::setMaxStepsPerUpdate(int steps)
{
    max_steps_per_update = steps;
}

int Stepper::getPosition()
{
    return current_position;
}

int Stepper::getTargetPosition()
{
    return target_position;
}

