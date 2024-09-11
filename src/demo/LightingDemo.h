#pragma once
#include "FeatureDemo.h"
#include "../core/Camera.h"
#include "../core/Model.h"
#include "../core/Window.h"
#include "../core/Shader.h"
#include "../math/lnal.h"


class LightingDemo : public FeatureDemo
{
private:
    Camera cam{};
    Shader light_shader{};
    Model jupiter{};
    Window* win = nullptr;

    lnal::mat4 model{};

    //lnal::vec3 light_color{ 0.1, 0.1, 1.0};
    lnal::vec3 light_pos{1.0, 0.0, 1.0};
    lnal::vec3 light_ambient{1.0, 1.0, 1.0};
    lnal::vec3 light_diffuse{0.2, 0.2, 0.2};
    lnal::vec3 light_specular{0.1, 0.1, 0.1};

    lnal::vec3 model_ambient{0.5, 0.5, 0.5};
    lnal::vec3 model_diffuse{0.55, 0.55, 0.55};
    lnal::vec3 model_specular{0.5, 0.5, 0.5};
    float model_shininess = 8.0;

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