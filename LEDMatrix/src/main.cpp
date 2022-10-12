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

uint16_t toco16(const CRGB &_col)
{
    return (
        ((_col.r << 8) & (63 << 11)) | 
        ((_col.g << 3) & (127 << 5)) |
        (_col.b >> 3)
    );
}

#define MSPF 180 // ms per frame

void blackscreen()
{
    matrix.fillScreen(0);
}

void scroll_text(const char *_text, int16_t _x, int16_t _y)
{
    // get text length
    uint16_t iters;
    int16_t grb;
    uint16_t ugrb;
    matrix.getTextBounds(_text, _x, _y, &grb, &grb, &iters, &ugrb);
    matrix.setTextColor(BLUE);

    // scroll text all the way off the screen (text length + screen width (= 24 px))
    for (uint16_t i = 0; i < iters + 24; i++)
    {
        matrix.setCursor(_x - i, _y);
        matrix.print(_text);
        matrix.update(); 
        delay(MSPF);
        matrix.fillScreen(0);
    }
}

void stationary_circle()
{
    matrix.drawCircle(17, 4, 3, RED);
    matrix.update();
    
    matrix.drawCircle(6, 4, 3, GREEN);
    matrix.update();
}
    
void smiley()
{   
    for (int i = 6; i < 20; i+=11)
    {
        matrix.drawCircle(i, 4, 3, RED);
        matrix.update();
        matrix.drawPixel(i-1, 3, BLUE);
        matrix.drawPixel(i+1, 3, BLUE);
        matrix.drawLine(i-1, 5, i+1, 5, GREEN);
    }
        
    
}

void moving_circle()
{
    for (int i = 3; i < 21; i++)        //for (int i = 19; i > 3; i--)  -->  other direction 
    {
        matrix.drawCircle(i, 4, 3, toco16(CHSV(128, 255, 255)));
        matrix.update();
        delay(MSPF);
        matrix.drawCircle(i, 4, 3, 0);
        matrix.update();
    }
}
    
void creating_sinus()
{
    for (int i = 0; i < 24; i++)
    {
        matrix.drawPixel(i, round(3 + 2*sin(i)), GREEN);
        matrix.update();
        delay(MSPF);
    }
}

void snake_line()
{
    int y = 1;
    for (int x = 0; x < 23; x++)
    {
        matrix.drawPixel(x, y, GREEN);
        matrix.update();
        delay(MSPF);
    }
    matrix.drawPixel(22, y+1, GREEN);
    matrix.update();
    delay(MSPF);
    y+=2;

    for (int x = 22; x > 1; x--)
    {
        matrix.drawPixel(x, y, GREEN);
        matrix.update();
        delay(MSPF);
    }
    matrix.drawPixel(2, y+1, GREEN);
    matrix.update();
    delay(MSPF);
    y+=2;

    for (int x = 2; x < 23; x++)
    {
        matrix.drawPixel(x, y, GREEN);
        matrix.update();
        delay(MSPF);
    }
    matrix.drawPixel(22, y+1, GREEN);
    matrix.update();
    delay(MSPF);
    y+=2;

    for (int x = 22; x > -1; x--)
    {
        matrix.drawPixel(x, y, GREEN);
        matrix.update();
        delay(MSPF);
    }
    
    for (int i = y; i > 0; i--)
    {
        matrix.drawPixel(0, i, GREEN);
        matrix.update();
        delay(MSPF);
    }
        
}

void reverse_snake_line()
{
    int y = 1;
    for (int x = 0; x < 23; x++)
    {
        matrix.drawPixel(x, y, 0);
        matrix.update();
        delay(MSPF/2);
    }
    matrix.drawPixel(22, y+1, 0);
    matrix.update();
    delay(MSPF/2);
    y+=2;

    for (int x = 22; x > 1; x--)
    {
        matrix.drawPixel(x, y, 0);
        matrix.update();
        delay(MSPF/2);
    }
    matrix.drawPixel(2, y+1, 0);
    matrix.update();
    delay(MSPF/2);
    y+=2;

    for (int x = 2; x < 23; x++)
    {
        matrix.drawPixel(x, y, 0);
        matrix.update();
        delay(MSPF/2);
    }
    matrix.drawPixel(22, y+1, 0);
    matrix.update();
    delay(MSPF/2);
    y+=2;

    for (int x = 22; x > -1; x--)
    {
        matrix.drawPixel(x, y, 0);
        matrix.update();
        delay(MSPF/2);
    }
    
    for (int i = y; i > 0; i--)
    {
        matrix.drawPixel(0, i, 0);
        matrix.update();
        delay(MSPF/2);
    }
        
}

void triangle()
{   
    for (int i = 0; i < 3; i++)
    {
        int x1 = random(0,24);
        int x2 = random(0,24);
        int x3 = random(0,24);

        int y1 = random(0,8);
        int y2 = random(0,8);
        int y3 = random(0,8);

        matrix.drawTriangle(x1,y1,x2,y2,x3,y3, random16(-1));
        matrix.update();
        delay(MSPF*10);
    }
    
}

void random_object()
{   
    for (int i = 0; i < 3; i++)
    {
        int x1 = random(0,24);
        int x2 = random(0,24);
        int x3 = random(0,24);

        int y1 = random(0,8);
        int y2 = random(0,8);
        int y3 = random(0,8);

        int r1 = random(1,7);

        //put the object you wanna draw here
        
        matrix.update();
        delay(MSPF*10);

        //Examples: 
        /*
        matrix.drawTriangle(x1,y1,x2,y2,x3,y3, random16(-1));
        
        matrix.drawCircle(x1,y1,r1,random16(-1));

        matrix.drawRect(x1,y1,x2,y2,random16(-1));

        matrix.drawLine(x1,y1,x2,y2,random16(-1));
        */
       
    }
    
}

void setup()
{
    Serial.begin(9600);
    
    matrix.begin();
    matrix.set_brightness(5);
    matrix.set_mirror(true, false);
    matrix.setTextSize(1);
    matrix.setTextWrap(0);

}



void loop()
{
    
}
