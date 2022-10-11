/*
ELEKTRON © 2022
Written by Matteo Reiter
www.elektron.work
11.10.22, 14:16

Web interface functions
*/

#pragma once

#include <stdint.h>

namespace interface
{
    void ap_init(const char *_ssid, const char *_psk);
    void ws_init();
    void handle();
}