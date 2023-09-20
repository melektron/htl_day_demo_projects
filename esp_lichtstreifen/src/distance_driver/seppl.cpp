#include "seppl.hpp" 


void seppl::setup(double dist)
{
    pinMode(TRIGGER, INPUT); 
    pinMode(ECHO, OUTPUT);

    max_distance = dist;
}

double seppl::distance_percentage()
{
    digitalWrite(TRIGGER, HIGH); 
    delayMicroseconds(3); 
    digitalWrite(TRIGGER, LOW); 
    int duration = pulseIn(ECHO, HIGH); 
    double distance = duration * 0.0344 / 2;
    return (distance / max_distance) * 100; 
    
    
}