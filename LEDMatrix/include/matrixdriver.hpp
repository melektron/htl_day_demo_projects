/*
ELEKTRON © 2022
Written by Matteo Reiter
WWW.elektron.Work
10.10.22, 16:20

Matrix driver for FastLED matrices and Adafruit GFX

*/

#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <FastLED.h>

template<int _W, int _H, int _Pin>
class matrixdriver : public Adafruit_GFX
{

protected:
    // display LEDs
    CRGB leds[_W*_H];

    bool mirrorx = false;
    bool mirrory = false;
    

public:

    matrixdriver()
    : Adafruit_GFX(_W, _H)
    {}
    
    // initializes FastLED strip
    void begin()
    {
        FastLED.addLeds<NEOPIXEL, _Pin>(leds, _W*_H);
    }

    // sets FastLED global brightness (FastLED.setBrightness())
    void set_brightness(uint8_t _scale)
    {
        FastLED.setBrightness(_scale);
    }

    // updates the LED matrix (= pushes out color values to matrix)
    // FastLED.show()
    void update()
    {
        FastLED.show();
    }

    void set_mirror(bool _x, bool _y)
    {
        mirrorx = _x;
        mirrory = _y;
    }
    
    void drawPixel(int16_t _x, int16_t _y, uint16_t _color) override
    {
        int16_t x = mirrorx ? (_W - (1 + _x)) : _x;
        int16_t y = mirrory ? (_H - (1 + _y)) : _y;
        if (x > _W - 1 || x < 0) return;
        if (y > _H - 1 || y < 0) return;
        // convert RGB565 to RGB24
        leds[_H * x + y].setRGB(
            ((_color >> 11) & 63) << 3,
            ((_color >> 5) & 127) << 2,
            ((_color) & 63) << 3
        );
    }
};