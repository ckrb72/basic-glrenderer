#pragma once
#include "../Scene.h"
#include "../../core/SpriteSheet.h"

class ScSplash : public Scene
{
private:
    SpriteSheet m_splash;
    Shader m_shader;

    float m_time;

public:

    ScSplash();
    ~ScSplash();

    void start();
    void update(float delta);
    void render();
};  