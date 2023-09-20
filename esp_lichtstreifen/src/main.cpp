/**
 * @file main.cpp
 * @author Nilusink & MrFlunter
 * @brief taube
 * @version 2.1
 * @date 2023-09-20
 * 
 * @copyright Copyright Amogus (c) 2023
 * 
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

    for (int p = 0; p < 101; p++)
    {
        led_bar::setPercentage(p, CRGB::Green, CRGB::Red);
    }
}
