#include "seppl.hpp" 


double seppl::max_distance;
double seppl::last_distance = 0;


void seppl::setup(double dist)
{
    pinMode(TRIGGER, OUTPUT); 
    pinMode(ECHO, INPUT);

    max_distance = dist;
}

double seppl::distance_percentage(bool &updated)
{
    updated = true;

    digitalWrite(TRIGGER, HIGH); 
    delayMicroseconds(3); 
    digitalWrite(TRIGGER, LOW); 
    int duration = pulseIn(ECHO, HIGH, 8000);

    if (duration == 0)
    {
        updated = false;
        return last_distance;
    }

    last_distance = duration * 0.0344 / 2;
    last_distance = (last_distance / max_distance) * 100;

    return last_distance;
}