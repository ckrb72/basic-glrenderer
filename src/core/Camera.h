#pragma once
#include "../math/lnal.h"

class Camera
{
private:
    lnal::mat4 m_projection;
    lnal::mat4 m_view;

public:

    Camera();

    ~Camera();

    void lookat(lnal::vec3 cam_pos, lnal::vec3 cam_lookat, lnal::vec3 temp_up);
    void gen_perspective(float fovx, float aspect_ratio, float near, float far);
    void gen_orthographic(float left, float right, float bottom, float top, float near, float far);
    
    float* get_projection();
    float* get_view();
};