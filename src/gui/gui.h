#pragma once
#include "../core/Window.h"


void gui_setup(Window& win);
void gui_process_event(void* event);
void gui_create_frame();
void gui_draw();
void gui_shutdown();