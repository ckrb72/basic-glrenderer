#pragma once
#include <stdint.h>


struct TimeStruct
{
    float delta;
};

extern TimeStruct Time;


//Returns ticks (ms) since start of program
uint64_t get_ticks();

void calc_delta();