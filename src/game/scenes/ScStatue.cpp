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
    // Want to get window pointer here for width and height but still need to figure out how to pass data to scenes
    m_camera.gen_perspective(PI / 2, (float)(1920.0 / 1080.0), 0.1, 10.0);
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

    // Want to put these things in a UBO because they are used across many different programs
    shader.bind();

    shader.set_mat4fv("model", model.data());
    shader.set_mat4fv("projection", m_camera.get_projection());
    shader.set_mat4fv("view", m_camera.get_view());

    // Want to make a UBO for light sources as well and set those here


    jupiter_bust.draw(shader);
}