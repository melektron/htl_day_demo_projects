/**
 * @file led_bar.hpp
 * @author Nilusink
 * @brief Driver for the LED-bar
 * @version 1.0
 * @date 2023-09-20
 * 
 * @copyright Copyright Nilusink (c) 2023
 * 
 */
#pragma once
#include <FastLED.h>

#define DATA_PIN 23
#define NUM_LEDS 50


namespace led_bar
{
    extern CRGB leds[NUM_LEDS];

    /**
     * @brief setup the leds (and sett all to white)
     * 
     */
    void setup(const CRGB &default_color = CRGB::Black);

    /**
     * @brief set the color of all leds
     * 
     * @param _color color to set
     */
    void setAll(const CRGB &_color);

    /**
     * @brief sweeps all colors
     * 
     */
    void colorSpan();

    /**
     * @brief Set the Percentage object
     * 
     * @param distPerc how many to set
     * @param on_color color of on leds
     * @param off_color color of off leds
     */
    void setPercentage(double distPerc, const CRGB &on_color, const CRGB &off_color);
}
