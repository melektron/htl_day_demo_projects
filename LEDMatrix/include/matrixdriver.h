/*
ELEKTRON © 2022
Written by Matteo Reiter
www.elektron.work
10.10.22, 16:20

Matrix driver for FastLED matrices and Adafruit GFX

*/

#pragma once

#include <Adafruit_GFX.h>
#include <FastLED.h>

template<int w, int h, int pin>
class matrixdriver : public Adafruit_GFX
{

protected:
    
    
    CRGB leds[w*h];
    
    void drawPixel(int16_t _x, int16_t _y, uint16_t _color) override
    {
        leds[h * _x + _y] = CRGB(_color);
    }

public:

    matrixdriver()
    : Adafruit_GFX(w, h)
    {}

    void begin()
    {
        FastLED.addLeds<NEOPIXEL, pin>(leds, w*h);
    }

    void update()
    {
        FastLED.show();
    }
};