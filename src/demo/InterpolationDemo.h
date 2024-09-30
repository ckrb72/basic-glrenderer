#pragma once
#include "FeatureDemo.h"
#include "../core/Camera.h"
#include "../core/Model.h"
#include "../core/Window.h"
#include "../core/Shader.h"
#include "../math/lnal.h"
#include <vector>


class InterpolationDemo : public FeatureDemo
{
private:
    
    Camera cam{};

    bool show_cursor = false;

    Model m;

    Shader s;

    Window* win = nullptr;

    lnal::vec3 model_pos{ 0.0, -1.0, 0.0 };
    float model_scale = 0.01;
    float model_rotate_angle = 0.0f;
    lnal::vec3 model_rotate_axis{ 0.0, 1.0, 0.0 };

    lnal::vec3 start = { 0.0, 0.0, 0.0 };
    lnal::vec3 end = { 2.0, 2.0, 0.0 };

    float interpolation_time = 0.0;
    bool move_forward = true;

    float interpolation_length = 2.0;

    bool wireframe = false;

    void toggle_cursor();
    void toggle_wireframe();

    lnal::vec3 lerp(lnal::vec3& a, lnal::vec3& b, float t);

public: 

    bool init(Window* win) override;
    void frame_start() override;
    void update() override;
    void draw() override;
    void on_load() override;
    void gui_create_frame() override;
};