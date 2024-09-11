#pragma once
#include "FeatureDemo.h"
#include "../core/Camera.h"
#include "../core/Window.h"
#include "../core/Texture.h"
#include "../core/Shader.h"

class TextureDemo : public FeatureDemo
{
private:
    Camera cam;
    Window* win = nullptr;

    Shader texture_shader{};

    void toggle_cursor();

    bool show_cursor = true;

public:

    bool init(Window* win) override;
    void frame_start() override;
    void update() override;
    void draw() override;
    void on_load() override;
    void gui_create_frame() override;

};