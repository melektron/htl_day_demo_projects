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


// constants
#define IDLE_TIME 5  // when idling starts (in sec)
#define ANIM_TOGGLE_BUTTON 0
#define DEFAULT_BRIGHTNESS 100

// global variables
int last_updated_time = 0;
bool anim_on = false;
bool last_btn_value = false;
bool dist_updated, curr_btn_value;

// class instances
led_bar::FlowAnimation anim(1);
led_bar::ConstantAnimation green(CRGB::Green);
led_bar::ConstantAnimation red(CRGB::Red);


void setup()
{
    // setup pins
    pinMode(ANIM_TOGGLE_BUTTON, INPUT_PULLUP);

    // initialize stuff
    Serial.begin(115200);
    seppl::setup(100);
    led_bar::setup();
    oled::setup();
}


void loop()
{
    // turn on default brightness
    FastLED.setBrightness(DEFAULT_BRIGHTNESS);

    // step animation
    anim.stepPercent(.2);

    // toggle button
    curr_btn_value = digitalRead(ANIM_TOGGLE_BUTTON);
    if (!last_btn_value && curr_btn_value)
        anim_on = !anim_on;

    last_btn_value = curr_btn_value;

    // update leds & display
    float distPerc = seppl::distance_percentage(dist_updated);

    // no obstacle detected
    if (!dist_updated)
    {
        // idle
        if (millis() - last_updated_time > IDLE_TIME * 1000)
        {
            // render animation if on
            if (anim_on)
                anim.renderToStrip(led_bar::leds);

            // turn off leds if not
            else
            {
                FastLED.setBrightness(0);
                FastLED.show();
            }
        }
        delay(10);
        return;
    }

    // obstacle detected
    oled::update_display(distPerc, seppl::max_distance);
    led_bar::setPercentageAnimation(
        distPerc, green, red
    );

    last_updated_time = millis();
    delay(10);
}
