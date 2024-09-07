#include "input.h"
#include "../../gui/gui.h"
#include <SDL2/SDL.h>
#include <iostream>


/* In a real library would want to add getters for keyboard input
   i.e. if(Input.Keyboard.is_pressed(SCANCODE_A)) or if(Input.Keyboard.get_state(SCANCODE_A) == KEY_PRESSED)
   Want to do this so you can't modify the values of the KeyStates.
   Not doing that here because this is just for the demo anyway
*/


static Window* win = nullptr;

/* Want this to be accessed outside of this file (wherever we include input.h)*/
/* So not making this static */
InputState Input;

static void update_keyboard_state();;
static void update_key_state(const uint8_t* state, SDL_Scancode code);

void init_input(Window* window)
{
    win = window;
}

void input_update()
{

    int32_t dx, dy;
    bool mouse_motion = false;

    /* Handle Input */
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        gui_process_event(&event);
        switch(event.type)
        {

            case SDL_MOUSEMOTION:
                mouse_motion = true;
                dx = event.motion.xrel;
                dy = event.motion.yrel;
                break;

            case SDL_QUIT:
                win->set_close(true);
                break;

            default:
                break;
        }
    }

    if(!mouse_motion)
    {
        dx = 0;
        dy = 0;
    }

    Input.Mouse.dx = dx;
    Input.Mouse.dy = dy;

    /* Update the keyboard */
    update_keyboard_state();
}

static void update_keyboard_state()
{
    /* Get keyboard state from SDL2 */
    const uint8_t* cur_keyboard = SDL_GetKeyboardState(NULL);

    /* Update all watched keys */
    update_key_state(cur_keyboard, SDL_SCANCODE_ESCAPE);
    update_key_state(cur_keyboard, SDL_SCANCODE_A);
    update_key_state(cur_keyboard, SDL_SCANCODE_W);
    update_key_state(cur_keyboard, SDL_SCANCODE_S);
    update_key_state(cur_keyboard, SDL_SCANCODE_D);
    update_key_state(cur_keyboard, SDL_SCANCODE_SPACE);
    update_key_state(cur_keyboard, SDL_SCANCODE_LSHIFT);
    update_key_state(cur_keyboard, SDL_SCANCODE_1);

}

static void update_key_state(const uint8_t* state, SDL_Scancode code)
{
    /* If the key is down, update accordingly */
    /* else: if the key is up, set to unpressed*/
    if (state[code])
    {
        /* If the key is unpressed, set it to pressed*/
        /* else: if the key is already pressed, set it to held */
        if (Input.Keyboard[code] == KEY_STATE_UNPRESSED)
        {
            Input.Keyboard[code] = KEY_STATE_PRESSED;
        }
        else
        {
            Input.Keyboard[code] = KEY_STATE_HELD;
        }
    }
    else
    {
        Input.Keyboard[code] = KEY_STATE_UNPRESSED;
    }
}