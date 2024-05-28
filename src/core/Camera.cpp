#include "Camera.h"

Camera::Camera()
:m_projection(1.0), m_view(1.0), m_position(0.0, 0.0, 0.0)
{}

Camera::~Camera()
{}

void Camera::lookat(lnal::vec3 cam_pos, lnal::vec3 cam_lookat, lnal::vec3 temp_up)
{
    m_position = cam_pos;
    
    lnal::lookat(m_view, cam_pos, cam_lookat, temp_up);
}

void Camera::gen_perspective(float fovx, float aspect_ratio, float near, float far)
{
    lnal::gen_perspective_proj(m_projection, fovx, aspect_ratio, near, far);
}

void Camera::gen_orthographic(float left, float right, float bottom, float top, float near, float far)
{
    lnal::gen_orthographic_proj(m_projection, left, right, bottom, top, near, far);
}

float* Camera::get_projection()
{
    return m_projection.data();
}

float* Camera::get_view()
{
    return m_view.data();
}

float* Camera::get_position()
{
    return m_position.data();
}