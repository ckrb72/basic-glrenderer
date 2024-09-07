#include "Camera.h"

Camera::Camera()
:m_projection(1.0), m_view(1.0), position(0.0, 0.0, 0.0), forward(0.0, 0.0, 1.0), up(0.0, 1.0, 0.0)
{}

Camera::~Camera()
{}

void Camera::lookat()
{   
    lnal::lookat(m_view, position, forward, up);
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

lnal::vec3 Camera::get_position()
{
    return position;
}