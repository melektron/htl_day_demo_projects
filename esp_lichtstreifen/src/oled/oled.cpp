#include "oled.hpp"
#include <cmath>


U8G2_SH1106_128X64_NONAME_F_HW_I2C oled::u8g2(U8G2_R0);


void oled::setup()
{
    u8g2.begin();
    u8g2.setFont(u8g2_font_ncenB08_tr);
}

void oled::update_display(double dist_perc, double max_distance)
{
    double distance = (dist_perc / 100.f) * max_distance;  // calculate distance from given angle
    u8g2.firstPage();


    // shots left
    char buff[64];
    sprintf(buff, "%02.0f cm", distance);
    u8g2.drawStr(50, 35, buff);

    u8g2.nextPage();
}


