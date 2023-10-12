/*
ELEKTRON © 2022
Written by melektron and MrFlunter
www.elektron.work
10.10.22, 14:16

Arduino entry point for led display
*/

#include <Arduino.h>
#include "matrixdriver.hpp"

// x y pin
matrixdriver<32, 8, 19> matrix;

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

#define MSPF 120 // ms per frame

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
    for (uint16_t i = 0; i < iters + 32; i++)
    {
        matrix.setCursor(_x - i, _y);
        matrix.print(_text);
        matrix.update(); 
        delay(MSPF);
        matrix.fillScreen(0);
    }
}

void scroll_text_multicolor(const char *_text, int16_t _x, int16_t _y)
{
    // get text length
    uint16_t iters;
    int16_t grb;
    uint16_t ugrb;
    matrix.getTextBounds(_text, _x, _y, &grb, &grb, &iters, &ugrb);
    matrix.setTextColor(toco16(CHSV(0, 255, 255)));

    // scroll text all the way off the screen (text length + screen width (= 24 px))
    for (uint16_t i = 0; i < iters + 32; i++)
    {
        matrix.setCursor(_x - i, _y);
        matrix.print(_text);
        matrix.update(); 
        delay(MSPF);
        matrix.fillScreen(0);
        matrix.setTextColor(toco16(CHSV(i*(255/iters), 255, 255)));
    }
}

void stationary_circle()
{
    for (int i=0; i < 10; i++)
    {
        matrix.drawCircle(17, 4, 3, toco16(CHSV(random(0,255), 255, 255)));
        matrix.update();
        
        matrix.drawCircle(6, 4, 3, toco16(CHSV(random(0,255), 255, 255)));
        matrix.update();
        delay(MSPF*20);
    }
    
}
    
void smiley()
{   
    for (int i = 6; i < 20; i+=11)
    {
        matrix.drawCircle(i, 4, 3, RED);
        matrix.drawPixel(i-1, 3, BLUE);
        matrix.drawPixel(i+1, 3, BLUE);
        matrix.drawLine(i-1, 5, i+1, 5, GREEN);
        matrix.update();
    }
        
    
}

void moving_circle()
{
    for (int i = 3; i < 30; i++)        //for (int i = 19; i > 3; i--)  -->  other direction 
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
    for (int i = 0; i < 32; i++)
    {
        matrix.drawPixel(i, round(3 + 2*sin(i)), GREEN);
        matrix.update();
        delay(MSPF);
    }
}

void reversed_sinus()
{
    for (int i = 31; i > -1; i--)
    {
        matrix.drawPixel(i+3, round(3 + 2*sin(i)), RED);
        matrix.update();
        delay(MSPF);
    }
}

void creating_cosinus()
{
    for (int i = 0; i < 32; i++)
    {
        matrix.drawPixel(i, round(3 + 2*cos(i)), RED);
        matrix.update();
        delay(MSPF);
    }
}

void snake_line()
{
    int y = 1;
    for (int x = 0; x < 31; x++)
    {
        matrix.drawPixel(x, y, GREEN);
        matrix.update();
        delay(MSPF);
    }
    matrix.drawPixel(30, y+1, GREEN);
    matrix.update();
    delay(MSPF);
    y+=2;

    for (int x = 30; x > 1; x--)
    {
        matrix.drawPixel(x, y, GREEN);
        matrix.update();
        delay(MSPF);
    }
    matrix.drawPixel(2, y+1, GREEN);
    matrix.update();
    delay(MSPF);
    y+=2;

    for (int x = 2; x < 31; x++)
    {
        matrix.drawPixel(x, y, GREEN);
        matrix.update();
        delay(MSPF);
    }
    matrix.drawPixel(30, y+1, GREEN);
    matrix.update();
    delay(MSPF);
    y+=2;

    for (int x = 30; x > -1; x--)
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
    for (int x = 0; x < 31; x++)
    {
        matrix.drawPixel(x, y, 0);
        matrix.update();
        delay(MSPF/2);
    }
    matrix.drawPixel(30, y+1, 0);
    matrix.update();
    delay(MSPF/3);
    y+=2;

    for (int x = 30; x > 1; x--)
    {
        matrix.drawPixel(x, y, 0);
        matrix.update();
        delay(MSPF/2);
    }
    matrix.drawPixel(2, y+1, 0);
    matrix.update();
    delay(MSPF/2);
    y+=2;

    for (int x = 2; x < 31; x++)
    {
        matrix.drawPixel(x, y, 0);
        matrix.update();
        delay(MSPF/2);
    }
    matrix.drawPixel(30, y+1, 0);
    matrix.update();
    delay(MSPF/2);
    y+=2;

    for (int x = 30; x > -1; x--)
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
    for (int i = 0; i < 100; i++)
    {
        int x1 = random(0,32);
        int x2 = random(0,32);
        int x3 = random(0,32);

        int y1 = random(0,8);
        int y2 = random(0,8);
        int y3 = random(0,8);

        matrix.drawTriangle(x1,y1,x2,y2,x3,y3, random16(-1));
        matrix.update();
        delay(MSPF/10);
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
        matrix.drawRect(x1,y1,x2,y2,random16(-1));
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
    matrix.set_brightness(20);
    matrix.set_mirror(true, false);
    matrix.setTextSize(1);
    matrix.setTextWrap(0);

}

void main_loop()
{
    scroll_text("HALLO",23,0);
    scroll_text("Herzlich Willkommen an den HTL Tagen!",23,0);
    smiley();
    delay(MSPF*50);
    blackscreen();
    stationary_circle();
    delay(MSPF*10);
    blackscreen();
    triangle();
    delay(MSPF*30);
    blackscreen();
    creating_sinus();
    reversed_sinus();
    delay(MSPF*20);
    blackscreen();
    snake_line();
    reverse_snake_line();
    blackscreen();
    for (int i=0; i < 3; i++)
    {
        random_object();
        blackscreen();
    }
    scroll_text("Competence Center  HTL Anichstraße",23,0);

}

void loop()
{
    scroll_text_multicolor("HTL Tage",31,0);
}
