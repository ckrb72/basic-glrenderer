#pragma once
#include "../Window.h"


/*  Might want to make this a struct later on if we need 
    more data but for now this is fine
struct KeyboardState
{
    KeyState keyboard_state[SDL_NUM_SCANCODES];
};
*/



enum KeyState
{
    KEY_STATE_UNPRESSED,
    KEY_STATE_PRESSED,
    KEY_STATE_HELD
};

#define MB_LEFT 0
#define MB_RIGHT 1
#define MB_MIDDLE 3

enum MouseButtonState
{
    MB_UNPRESSED,
    MB_PRESSED
};

struct MouseState
{
    int32_t x, y;
    int32_t dx, dy;

    /* 0 - Left, 1 - Right, 2 - Middle */
    /* TODO: Not currently updating */
    MouseButtonState Button[3];
};

struct InputState
{
    MouseState Mouse;
    KeyState Keyboard[SDL_NUM_SCANCODES];
};

extern InputState Input;


void init_input(Window* window);
void input_update();