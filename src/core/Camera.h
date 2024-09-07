#pragma once
#include "../math/lnal.h"

class Camera
{
private:
    lnal::mat4 m_projection;
    lnal::mat4 m_view;

public:

    lnal::vec3 position;
    lnal::vec3 up;
    lnal::vec3 forward;

    Camera();

    ~Camera();

    void lookat();
    void gen_perspective(float fovx, float aspect_ratio, float near, float far);
    void gen_orthographic(float left, float right, float bottom, float top, float near, float far);
    
    float* get_projection();
    float* get_view();
    lnal::vec3 get_position();
};