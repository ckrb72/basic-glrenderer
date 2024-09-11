#include "LightingDemo.h"
#include <iostream>
#include "../core/input/input.h"
#include "../core/engine_time.h"
#include <imgui.h>

/*
FIXME:
Want to put demo specific gui stuff in here so we have access to the variables. I guess thats the best way to do it.

*/


bool LightingDemo::init(Window* win)
{
    this->win = win;

    cam.gen_perspective(PI / 2, (float)1920.0/ (float)1080.0, 0.1, 100.0);

    if(!jupiter.load("./assets/model/jupiter.obj"))
    {
        std::cerr << "Failed to load jupiter model" << std::endl;
        return false;
    }

    if(!light_shader.load("./shader/light.vert", "./shader/light.frag"))
    {
        std::cerr << "Failed to load Lighting Shader" << std::endl;
        return false;
    }



    cam.position = { 0.0, 0.0, 5.0 };
    cam.forward = { 0.0, 0.0, 0.0 };
    cam.up = { 0.0, 1.0, 0.0 };

    lnal::scale(model, 0.01);
    lnal::translate_relative(model, lnal::vec3(0.0, -1.0, 0.0));

    return true;
}

void LightingDemo::frame_start()
{
    /* If we aren't showing the cursor, then place it in the middle of the screen */
    if(!show_cursor)
        win->set_cursor_pos(win->get_width() / 2, win->get_height() / 2);
}

void LightingDemo::update()
{
/* Update cam position */

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

    // If adding a keyboard interaction here, don't forget to add the in update_keyboard_state()
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

void LightingDemo::draw()
{

    light_shader.bind();
    light_shader.set_mat4fv("model", model.data());
    light_shader.set_mat4fv("view", cam.get_view());
    light_shader.set_mat4fv("projection", cam.get_projection());

    //light_shader.set_vec3fv("light_color", light_color.data());
    light_shader.set_vec3fv("cam_pos", cam.position.data());

    light_shader.set_vec3fv("material.ambient", model_ambient.data());
    light_shader.set_vec3fv("material.diffuse", model_diffuse.data());
    light_shader.set_vec3fv("material.specular", model_specular.data());
    light_shader.set_float("material.shininess", model_shininess);

    light_shader.set_vec3fv("light.position", light_pos.data());
    light_shader.set_vec3fv("light.ambient", light_ambient.data());
    light_shader.set_vec3fv("light.diffuse", light_diffuse.data());
    light_shader.set_vec3fv("light.specular", light_specular.data());
    jupiter.draw(light_shader);
}

void LightingDemo::toggle_cursor()
{
    show_cursor = !show_cursor;

    /* If we want to show cursor, then we want set relative off */
    /* If we don't want to show cursor, then we want set relative on */
    win->set_cursor_relative(!show_cursor);
}

void LightingDemo::on_load()
{

}

void LightingDemo::gui_create_frame()
{
    static float f_scalar = 0.0f;
    static float f_vec[3];
    static float light_color[3];

    ImGui::SeparatorText("Model");
    ImGui::DragFloat3("Position", f_vec, 0.05, -100.0f, 100.0f, "%.3f", ImGuiSliderFlags_None);
    ImGui::DragFloat("Rotation", &f_scalar, 0.1, -360.0f, 360.0f, "%.3f", ImGuiSliderFlags_None);

    ImGui::SeparatorText("Light");
    ImGui::DragFloat("Position", &f_scalar, 0.1, -360.0f, 360.0f, "%.3f", ImGuiSliderFlags_None);
    ImGui::ColorEdit3("Color", light_color);
}