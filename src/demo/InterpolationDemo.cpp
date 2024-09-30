#include "InterpolationDemo.h"
#include <iostream>
#include "../core/input/input.h"
#include "../core/engine_time.h"
#include <imgui.h>
#include <graphics.h>

bool InterpolationDemo::init(Window* win)
{
    this->win = win;


    float aspect_ratio = (float)win->get_width() / (float)win->get_height();

    cam.gen_perspective(PI / 2, (float)1920.0/ (float)1080.0, 0.1, 100.0);

    if(!m.load("./assets/model/jupiter.obj"))
    {
        std::cerr << "Failed to load model" << std::endl;
        return false;
    }

    if(!s.load("./shader/normals.vert", "./shader/normals.frag"))
    {
        std::cerr << "Failed to load shader" << std::endl;
        return false;
    }

    cam.position = { 0.0, 0.0, 6.0 };
    cam.forward = { 0.0, 0.0, 0.0 };
    cam.up = { 0.0, 1.0, 0.0 };

    return true;
}

void InterpolationDemo::draw()
{

    lnal::mat4 model(1.0);
    lnal::scale(model, model_scale);
    lnal::rotate(model, model_rotate_axis, lnal::radians(model_rotate_angle));
    lnal::translate_relative(model, model_pos);

    s.bind();
    s.set_mat4fv("model", model.data());
    s.set_mat4fv("view", cam.get_view());
    s.set_mat4fv("projection", cam.get_projection());
    m.draw(s);

}

void InterpolationDemo::frame_start()
{
    /* If we aren't showing the cursor, then place it in the middle of the screen */
    if(!show_cursor)
        win->set_cursor_pos(win->get_width() / 2, win->get_height() / 2);
}

void InterpolationDemo::update()
{
    /* Update cam position */

    /* Want to make this so it goes back and forth */
    model_pos = lerp(start, end, interpolation_time / interpolation_length);

    if(interpolation_time <= 2.0)
        interpolation_time += Time.delta;

    if(!show_cursor)
    {
        cam.yaw += Input.Mouse.dx * cam.sensitivity;
        cam.pitch -= Input.Mouse.dy * cam.sensitivity;
        if(cam.pitch > 89.0f)
            cam.pitch = 89.0f;
        if(cam.pitch < -89.0f)
            cam.pitch = -89.0f;
    }

    if(Input.Keyboard[SDL_SCANCODE_ESCAPE] == KEY_STATE_PRESSED)
    {
        toggle_cursor();
    }

    // Camera look direction based on mouse movement
    lnal::vec3 look_dir{};
    look_dir[0] = cos(lnal::radians(cam.yaw)) * cos(lnal::radians(cam.pitch));
    look_dir[1] = sin(lnal::radians(cam.pitch));
    look_dir[2] = sin(lnal::radians(cam.yaw)) * cos(lnal::radians(cam.pitch));

    look_dir.normalize();

    // If adding a keyboard interaction here, don't forget to add in update_keyboard_state()
    if(!show_cursor)
    {
        if(Input.Keyboard[SDL_SCANCODE_A] == KEY_STATE_HELD)
            cam.position -= Time.delta * lnal::cross(look_dir, cam.up);

        if(Input.Keyboard[SDL_SCANCODE_S] == KEY_STATE_HELD)
            cam.position -= Time.delta * look_dir;

        if(Input.Keyboard[SDL_SCANCODE_D] == KEY_STATE_HELD)
            cam.position += Time.delta * lnal::cross(look_dir, cam.up);

        if(Input.Keyboard[SDL_SCANCODE_W] == KEY_STATE_HELD)
            cam.position += Time.delta * look_dir;

        if(Input.Keyboard[SDL_SCANCODE_SPACE] == KEY_STATE_HELD)
            cam.position += Time.delta * cam.up;

        if(Input.Keyboard[SDL_SCANCODE_LSHIFT] == KEY_STATE_HELD)
            cam.position -= Time.delta * cam.up;

    }
    cam.forward = cam.position + look_dir;
    cam.lookat();
    
}



void InterpolationDemo::toggle_cursor()
{
    show_cursor = !show_cursor;

    /* If we want to show cursor, then we want set relative off */
    /* If we don't want to show cursor, then we want set relative on */
    win->set_cursor_relative(!show_cursor);
}

void InterpolationDemo::on_load()
{

}

void InterpolationDemo::gui_create_frame()
{
    /* Choose models here */
    /* Choose shaders too */
    /* Set scale and stuff too */

    ImGui::Spacing();

    ImGui::DragFloat3("Position", model_pos.data(), 0.05, -100.0f, 100.0f, "%.3f", ImGuiSliderFlags_None);
    ImGui::DragFloat("Scale", &model_scale, 0.001, 0.001f, 5.0f, "%.3f", ImGuiSliderFlags_None);

    ImGui::Spacing();

    ImGui::DragFloat("Rotation", &model_rotate_angle, 0.5, 0.0f, 360.0f, "%.3f", ImGuiSliderFlags_WrapAround);
    ImGui::DragFloat3("Rotation Axis", model_rotate_axis.data(), 0.05, 0.0, 10.0, "%.3f", ImGuiSliderFlags_None);

    if(ImGui::Checkbox("Wireframe", &wireframe))
    {
        toggle_wireframe();
    }
}

void InterpolationDemo::toggle_wireframe()
{
    if(wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

lnal::vec3 InterpolationDemo::lerp(lnal::vec3& a, lnal::vec3& b, float t)
{
    return a + (b - a) * t;
}