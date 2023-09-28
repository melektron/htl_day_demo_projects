#include "seppl.hpp" 


double seppl::max_distance;
double seppl::last_distance = 0;


void seppl::setup(double dist)
{
    pinMode(TRIGGER, OUTPUT); 
    pinMode(ECHO, INPUT);

    max_distance = dist;
}

double seppl::distance_percentage()
{
    digitalWrite(TRIGGER, HIGH); 
    delayMicroseconds(3); 
    digitalWrite(TRIGGER, LOW); 
    int duration = pulseIn(ECHO, HIGH, 8000);

    if (duration == 0)
        return seppl::last_distance;

    seppl::last_distance = duration * 0.0344 / 2;
    seppl::last_distance = (seppl::last_distance / max_distance) * 100;
    return seppl::last_distance;
}