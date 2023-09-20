/*
ELEKTRON © 2022
Written by melektron
www.elektron.work
08.05.23, 14:07

Demo project of how to control a WS2812B/WS2813-based LED-Strip.
*/

#include <Arduino.h>
#include <FastLED.h>

#define DATA_PIN 14
#define BTN_PIN 19

#define NUM_LEDS 8


CRGB leds[NUM_LEDS];



void awaitButton()
{
    while (digitalRead(BTN_PIN));
    delay(100);
    while (!digitalRead(BTN_PIN));
}

void setAll(const CRGB &_color)
{
    for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = _color;
    
    FastLED.show();
}

void colorSpan()
{
    for (int i = 0; i < NUM_LEDS; i++)
        leds[i] = CHSV(map(i, 0, NUM_LEDS - 1, 60, 255), 255, 255);

    FastLED.show();
}


void setup()
{
    Serial.begin(115200);

    pinMode(BTN_PIN, INPUT_PULLUP);

    FastLED.addLeds<WS2813, DATA_PIN, GBR>(leds, NUM_LEDS);

    // global brightness scaling
    FastLED.setBrightness(75);

    // set default color
    setAll(CRGB::White);
}


void loop()
{
    awaitButton();
    setAll(CRGB::Green);
    Serial.println("Green");
    
    awaitButton();
    setAll(CRGB::Red);
    Serial.println("Red");

    awaitButton();
    setAll(CRGB::Blue);
    Serial.println("Blue");

    awaitButton();
    colorSpan();
    Serial.println("Span");

    awaitButton();
    setAll(CRGB::White);
    Serial.println("White");
}
