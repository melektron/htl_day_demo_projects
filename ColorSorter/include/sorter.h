/*
ELEKTRON © 2022
Written by Matteo Reiter
www.elektron.work
11.10.22, 14:51

sorter thread
*/

#pragma once

namespace sorter
{
    void init();

    void start_thread();
    
    void on();
    void off();
    int get_last_color();
};

