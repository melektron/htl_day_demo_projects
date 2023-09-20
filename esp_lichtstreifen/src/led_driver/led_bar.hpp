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
#include <FastLED.h>

#define DATA_PIN 21
#define NUM_LEDS 10


namespace led_bar
{
    CRGB leds[NUM_LEDS];

    /**
     * @brief setup the leds (and sett all to white)
     * 
     */
    void setup(const CRGB &default_color = CRGB::Black);

    void setAll(const CRGB &_color);
    void colorSpan();

    void setPercentage(float distPerc, const CRGB &on_color, const CRGB &off_color);
}
