/*
ELEKTRON © 2022
Written by melektron and MrFlunter
www.elektron.work
10.10.22, 14:16

Arduino entry point for led display
*/

#include <Arduino.h>

#include <FastLED.h>

#define NUM_LEDS 60

CRGB leds[NUM_LEDS];

void setup()
{
    FastLED.addLeds<NEOPIXEL, 16>(leds, NUM_LEDS);
}

void loop()
{
    leds[0] = CRGB::White;
    FastLED.show();
    delay(30);
    leds[0] = CRGB::Black;
    FastLED.show();
    delay(30);
}