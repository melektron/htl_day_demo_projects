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
#include "distance_driver/seppl.hpp"
#include "oled/oled.hpp"



void setup()
{
    Serial.begin(115200);
    led_bar::setup();
    seppl::setup(100);
    oled::setup();
}


void loop()
{
    float distPerc = seppl::distance_percentage();

    if (distPerc > 100)
    {
        distPerc = 100;
    }

    Serial.println(distPerc);

    oled::update_display(distPerc, seppl::max_distance);
    led_bar::setPercentage(distPerc, CRGB::Green, CRGB::Blue);

    delay(20);
}
