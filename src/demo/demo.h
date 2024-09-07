#pragma once
#include "../core/Window.h"

enum DemoType
{
    DEMO_MODEL,
    DEMO_LIGHTING,
    DEMO_SPRITESHEET,
    DEMO_TEXTURE
};


bool demo_init(Window* win);

/* Internal state machine. Tells demo which specific demo to use */
void load_demo(DemoType type);

void demo_update();

void demo_draw();

void demo_destroy();