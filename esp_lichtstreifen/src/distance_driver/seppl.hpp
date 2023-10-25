/**
 * @file led_bar.hpp
 * @author Nilusink
 * @brief Driver for the LED-bar
 * @version 1.0
 * @date 2023-09-20
 * 
 * @copyright Copyright Nilusink (c) 2023
 * 
 */
#include <Arduino.h> 

#define TRIGGER 17
#define ECHO 16


namespace seppl
{
    extern double max_distance;
    extern double last_distance;

    void setup(double dist);
    double distance_percentage(bool &updated);
}
