#pragma once
#include "FeatureDemo.h"
#include "../core/Window.h"
#include "../core/SpriteSheet.h"
#include "../core/Camera.h"
#include "../core/Shader.h"

class SpritesheetDemo : public FeatureDemo
{
private:
    Camera cam{};
    Window* win = nullptr;

    SpriteSheet sprite_sheet{};
    Shader sprite_shader{};

    bool show_cursor = true;
    void toggle_cursor();

    lnal::mat4 model{};

    int fps = 10.0;
    bool paused = false;
    float time = 0.0;

    int clip_width = 33;
    int clip_height = 31;

    int clip_x = 0;
    int clip_y = 0;


public:

    bool init(Window* win) override;
    void frame_start() override;
    void update() override;
    void draw() override;
    void on_load() override;
    void gui_create_frame() override;

};