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


led_bar::FlowAnimation anim(2);
led_bar::ConstantAnimation green(CRGB::Green);
led_bar::ConstantAnimation red(CRGB::Red);


void setup()
{
    Serial.begin(115200);
    seppl::setup(100);
    led_bar::setup();
    oled::setup();
}


void loop()
{
    anim.stepPercent(10);
    float distPerc = seppl::distance_percentage();

    if (distPerc > 100) {distPerc = 100;}

    oled::update_display(distPerc, seppl::max_distance);
    led_bar::setPercentageAnimation(
        distPerc, green, red
        );


    delay(10);
}
