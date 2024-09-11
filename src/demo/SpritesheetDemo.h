#pragma once
#include "FeatureDemo.h"
#include "../core/Window.h"
#include "../core/SpriteSheet.h"
#include "../core/Camera.h"

class SpritesheetDemo : public FeatureDemo
{
private:
    Camera cam{};
    Window* win = nullptr;

    SpriteSheet sprite_sheet{};

    bool show_cursor = true;
    void toggle_cursor();

    int fps = 10;
    bool paused = false;


public:

    bool init(Window* win) override;
    void frame_start() override;
    void update() override;
    void draw() override;
    void on_load() override;
    void gui_create_frame() override;

};