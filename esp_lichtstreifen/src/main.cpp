/*
ELEKTRON © 2022
Written by melektron
www.elektron.work
08.05.23, 14:07

Demo project of how to control a WS2812B/WS2813-based LED-Strip.
*/

#include <Arduino.h>
#include "led_driver/led_bar.hpp"



void setup()
{
    Serial.begin(115200);
    led_bar::setup();
}


void loop()
{
    float distPerc = 0;
}
