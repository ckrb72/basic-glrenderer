#include "input.h"
#include <SDL2/SDL.h>
#include <iostream>

KeyState keyboard_state[SDL_NUM_SCANCODES];


static void update_state(const uint8_t* state, SDL_Scancode code);

void init_input()
{

}

void update_keyboard_state()
{
    const uint8_t* cur_keyboard = SDL_GetKeyboardState(NULL);

    update_state(cur_keyboard, SDL_SCANCODE_ESCAPE);
    update_state(cur_keyboard, SDL_SCANCODE_A);
    update_state(cur_keyboard, SDL_SCANCODE_W);
    update_state(cur_keyboard, SDL_SCANCODE_S);
    update_state(cur_keyboard, SDL_SCANCODE_D);

}

const KeyState* get_keyboard_state()
{
    return keyboard_state;
}

static void update_state(const uint8_t* state, SDL_Scancode code)
{
    if (state[code])
    {
        if (keyboard_state[code] == KEY_STATE_UNPRESSED)
        {
            keyboard_state[code] = KEY_STATE_PRESSED;
        }
        else
        {
            keyboard_state[code] = KEY_STATE_HELD;
        }
    }
    else
    {
        keyboard_state[code] = KEY_STATE_UNPRESSED;
    }
}