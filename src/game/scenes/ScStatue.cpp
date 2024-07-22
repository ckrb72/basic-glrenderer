#include "ScStatue.h"
#include <iostream>

ScStatue::ScStatue()
:Scene()
{

}

ScStatue::~ScStatue()
{

}


void ScStatue::start()
{
    if(!jupiter_bust.load("./assets/model/jupiter.obj"))
    {
        std::cerr << "Failed to load jupiter bust" << std::endl;
    }

    if(!shader.load("./shader/default.vert", "./shader/default.frag"))
    {
        std::cerr << "Failed to load jupiter shader" << std::endl;
    }

    lnal::scale(model, 0.01);
    lnal::translate_relative(model, lnal::vec3(0.0, -1.0, -2.0));
}

void ScStatue::update(float delta)
{
    // Update model here
}

void ScStatue::render()
{
    shader.bind();

    shader.set_mat4fv("model", model.data());
    shader.set_mat4fv("projection", m_camera->get_projection());
    shader.set_mat4fv("view", m_camera->get_view());

    jupiter_bust.draw(shader);
}