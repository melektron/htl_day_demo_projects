/*
ELEKTRON © 2022
Written by melektron and MrFlunter
www.elektron.work
10.10.22, 14:16

Arduino entry point for led display
*/

#include <Arduino.h>

#include <FastLED.h>
#include "matrixdriver.h"

/*
#define NUM_LEDS 60

CRGB leds[NUM_LEDS];
*/

matrixdriver<24, 8, 5> matrix;


#define RED 0b00000000000111111

void setup()
{
    Serial.begin(9600);
    //FastLED.addLeds<NEOPIXEL, 5>(leds, NUM_LEDS);
    
    matrix.begin();
    matrix.drawCircle(6, 3, 3, 0xffff);
    matrix.update();
}

void loop()
{
    for (int i = 3; i < 20; i++)
    {
        Serial.println("draw circle");
        matrix.drawCircle(i, 3, 3, RED);
        matrix.update();
        delay(500);
    }
}