/**
 * @file oled.hpp
 * @author Nilusink
 * @brief utility functions for the oled
 * @version 0.8
 * @date 2023-02-17
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <U8g2lib.h>


namespace oled
{
    extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;

    /**
     * @brief setup the display
     * 
     */
    void setup();

    void update_display(double dist_perc, double max_distance);
};
