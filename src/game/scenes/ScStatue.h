#pragma once
#include "../../core/Scene.h"
#include "../../core/Model.h"
#include "../../math/lnal.h"
#include "../../core/Camera.h"


class ScStatue : public Scene
{
private:
    Camera m_camera;
    Model jupiter_bust;
    lnal::mat4 model;
    Shader shader;

public:

    ScStatue();
    ~ScStatue();

    void start() override;
    void update(float delta) override;
    void render() override;

};