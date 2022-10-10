/*
ELEKTRON © 2022
Written by melektron and MrFlunter
www.elektron.work
10.10.22, 14:16

Arduino entry point for led display
*/

#include <Arduino.h>
#include "matrixdriver.hpp"

matrixdriver<24, 8, 5> matrix;

//              0brrrrrggggggbbbbb
#define RED     0b1111100000000000
#define GREEN   0b0000011111100000
#define BLUE    0b0000000000011111


#define MSPF 60 // ms per frame


void setup()
{
    Serial.begin(9600);
    
    matrix.begin();
    matrix.set_brightness(1);
    matrix.set_mirror(true, false);

}

void loop()
{
    for (int i = 3; i < 21; i++)
    {
        matrix.drawCircle(i, 3, 4, RED);
        matrix.update();
        delay(MSPF);
        matrix.drawCircle(i, 3, 4, 0);
        matrix.update();
    }
    for (int i = 19; i > 3; i--)
    {
        matrix.drawCircle(i, 3, 5, GREEN);
        matrix.update();
        delay(MSPF);
        matrix.drawCircle(i, 3, 5, 0);
        matrix.update();
    }
    for (int i = 0; i < 24; i++)
    {
        matrix.drawPixel(i, round(3 + 2*sin(i)), GREEN);
        matrix.update();
        delay(MSPF);
    }
    matrix.fillScreen(0);
    matrix.setTextColor(BLUE);
    matrix.setTextSize(1);
    matrix.setTextWrap(0);
    static const char* text_to_show = "HTL-Tage! Yeah! HTL! Come and remove the word 'Freetime' from your brain.";

    // get text length
    uint16_t iters;
    int16_t grb;
    uint16_t ugrb;
    matrix.getTextBounds(text_to_show, 0, 0, &grb, &grb, &iters, &ugrb);

    // scroll text all the way off the screen (text length + screen width (= 24 px))
    for (uint16_t i = 0; i < iters + 24; i++)
    {
        matrix.setCursor(0 - i, 0);
        matrix.print(text_to_show);
        matrix.update(); 
        delay(MSPF);
        matrix.fillScreen(0);
    }
    delay(500);
}