#pragma once
#include "../core/Window.h"


/* Base Abstract Class for Demos to derive */
class FeatureDemo
{
public:
    virtual bool init(Window* win) = 0;
    virtual void frame_start() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    virtual void on_load() = 0;
    virtual void gui_create_frame() = 0;
};