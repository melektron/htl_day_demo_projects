



#pragma once

#include <Arduino.h>


#define S0 17
#define S1 18
#define S2 19
#define S3 23
#define sensorOut 25


namespace colors
{
    void pins_init();

    int detect_color(int detail);
}

