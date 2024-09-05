#pragma once
#include "../../core/Scene.h"
#include "../../core/SpriteSheet.h"
#include "../../core/Camera.h"
#include "../../math/lnal.h"
#include "../../core/Shader.h"

class ScSplash : public Scene
{
private:
    SpriteSheet m_splash;
    Shader m_shader;
    Camera m_camera;

    float m_time;

public:

    ScSplash();
    ~ScSplash();

    void start() override;
    void update(float delta) override;
    void render() override;
};  