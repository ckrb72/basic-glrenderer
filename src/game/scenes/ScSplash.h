#pragma once
#include "../Scene.h"
#include "../../core/SpriteSheet.h"

class ScSplash : Scene
{
private:
    SpriteSheet m_animation;
    Shader m_shader;



public:

    ScSplash() {}
    ~ScSplash() {}

};  