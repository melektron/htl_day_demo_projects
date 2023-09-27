#include "seppl.hpp" 


double seppl::max_distance = 0;


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
    int duration = pulseIn(ECHO, HIGH, 100000);

    if (duration > 12000)
        return 0;

    double distance = duration * 0.0344 / 2;
    return (distance / max_distance) * 100; 
    
    
}