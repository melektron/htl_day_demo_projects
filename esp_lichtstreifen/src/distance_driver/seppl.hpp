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

#define TRIGGER 16
#define ECHO 17 

namespace seppl
{
    extern double max_distance;

    
    void setup(double dist);
    double distance_percentage(); 
}