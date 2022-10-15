



#pragma once

#include <Arduino.h>


#define S0 23
#define S1 19
#define S2 18
#define S3 17
#define sensorOut 16


namespace colors
{
    void pins_init();

    int detect_color(int detail);
}

