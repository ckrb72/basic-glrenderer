#pragma once

enum KeyState
{
    KEY_STATE_UNPRESSED,
    KEY_STATE_PRESSED,
    KEY_STATE_HELD
};

void init_input();
void update_keyboard_state();
const KeyState* get_keyboard_state();