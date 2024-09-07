#include "ModelDemo.h"
#include <iostream>
#include "../core/input/input.h"

bool ModelDemo::init_demo(Window* win)
{
    this->win = win;

    cam.gen_perspective(PI / 2, (float)win->get_height() / (float)win->get_width(), 0.1, 100.0);

    std::shared_ptr<Model> jupiter = std::make_shared<Model>();
    if(!jupiter->load("./assets/model/jupiter.obj"))
    {
        std::cerr << "Failed to load jupiter model" << std::endl;
        return false;
    }

    models.push_back(jupiter);

    Shader clip_space{};
    if(!clip_space.load("./shader/clip_space.vert", "./shader/clip_space.frag"))
    {
        std::cerr << "Failed to load view_space shader" << std::endl;
        return false;
    }

    shaders.push_back(clip_space);


    cur_model = models[0];
    cur_shader = &shaders[0];

    return true;
}

void ModelDemo::draw_demo()
{

    /* Draw currently selected model with currently selected shader */

}

void ModelDemo::update_demo()
{
    /* Update cam position */
    
}



void ModelDemo::toggle_cursor(Window& win)
{
    show_cursor = !show_cursor;

    /* If we want to show cursor, then we want set relative off */
    /* If we don't want to show cursor, then we want set relative on */
    win.set_cursor_relative(!show_cursor);
}