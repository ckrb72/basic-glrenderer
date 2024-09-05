#include "ScSplash.h"
#include <iostream>

static float x = 0.0;

ScSplash::ScSplash()
:Scene()
{

}

ScSplash::~ScSplash()
{

}

void ScSplash::start()
{

    // Want to get a window pointer here for the width and height but still need to figure out how to pass the data over to scenes
    m_camera.gen_perspective(PI / 2, (float)(1920.0 / 1080.0), 0.1, 10.0);

    if(!m_shader.load("./shader/splash.vert", "./shader/splash.frag"))
    {
        std::cerr << "Failed to load Splash Screen Shader" << std::endl;
    }

    if(!m_splash.load("./assets/img/splashscreen.png"))
    {
        std::cerr << "Failed to load Splash Screen SpriteSheet" << std::endl;
    }

    m_splash.set_size(256, 256);
    m_time = 0.0;

    m_splash.set_clip(0, 0);

}

void ScSplash::update(float delta)
{

    if(m_time >= 0.1)
    {
        x += 256;
        m_splash.set_clip(x, 0);
        m_time = 0.0;
    }

    m_time += delta;
}

void ScSplash::render()
{
    m_shader.bind();
    lnal::mat4 model(1.0);
    lnal::translate_relative(model, lnal::vec3(0.0, 0.0, -1.0));

    m_shader.set_mat4fv("model", model.data());
    m_shader.set_mat4fv("projection", m_camera.get_projection());
    m_shader.set_mat4fv("view", m_camera.get_view());
    m_shader.set_int("sprite_sheet", 0);


    m_splash.draw();
}
