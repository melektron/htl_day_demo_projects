#include <FastLED.h>

#define DATA_PIN 14
#define NUM_LEDS 8

CRGB leds[NUM_LEDS];


namespace led_bar
{
    void setup();
    void setAll(const CRGB &_color);
    void colorSpan();
}
