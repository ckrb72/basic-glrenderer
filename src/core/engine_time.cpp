#include "engine_time.h"
#include <SDL2/SDL.h>

static uint64_t previous_ticks = 0;
static uint64_t current_ticks = 0;

TimeStruct Time;


uint64_t get_ticks()
{
    return SDL_GetTicks64();
}

void calc_delta()
{
    current_ticks = get_ticks();

    float delta_time = (float)(current_ticks - previous_ticks) * 0.001;
    previous_ticks = current_ticks;

    Time.delta = delta_time;
}