#pragma once
#include "FeatureDemo.h"
#include "../core/Camera.h"
#include "../core/Model.h"
#include "../core/Window.h"
#include "../core/Shader.h"
#include "../math/lnal.h"
#include <vector>


class ModelDemo : public FeatureDemo
{
private:
    
    Camera cam{};

    bool show_cursor = false;

    /* Needs to be a vector of unique_ptr because copy constructor isn't */
    /* defined so otherwise we get massive errors */
    std::vector<std::shared_ptr<Model>> models{};
    std::shared_ptr<Model> cur_model = nullptr;

    std::vector<std::shared_ptr<Shader>> shaders{};
    std::shared_ptr<Shader> cur_shader;

    Window* win = nullptr;

    lnal::mat4 model{};

    void toggle_cursor();

public: 

    bool init(Window* win) override;
    void frame_start() override;
    void update() override;
    void draw() override;
    void on_load() override;
    void gui_create_frame() override;
};