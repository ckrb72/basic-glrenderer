#pragma once
#include "../core/Window.h"


/* Base Abstract Class for Demos to derive */
class FeatureDemo
{
public:
    virtual bool init_demo(Window* win) = 0;
    virtual void update_demo() = 0;
    virtual void draw_demo() = 0;
};