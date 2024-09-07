#include "ModelDemo.h"
#include <iostream>
#include "../core/input/input.h"
#include "../core/engine_time.h"

bool ModelDemo::init(Window* win)
{
    this->win = win;

    cam.gen_perspective(PI / 2, (float)win->get_height() / (float)win->get_width(), 0.1, 100.0);

    std::shared_ptr<Model> jupiter = std::make_shared<Model>();
    if(!jupiter->load("./assets/model/jupiter.obj"))
    {
        std::cerr << "Failed to load jupiter model" << std::endl;
        return false;
    }

    models.push_back(jupiter);

    Shader clip_space{};
    if(!clip_space.load("./shader/clip_space.vert", "./shader/clip_space.frag"))
    {
        std::cerr << "Failed to load view_space shader" << std::endl;
        return false;
    }

    shaders.push_back(clip_space);


    cur_model = models[0];
    cur_shader = &shaders[0];

    cam.position = { 0.0, 0.0, 5.0 };
    cam.forward = { 0.0, 0.0, 0.0 };
    cam.up = { 0.0, 1.0, 0.0 };

    return true;
}

void ModelDemo::draw()
{

    /* Draw currently selected model with currently selected shader */

}

void ModelDemo::frame_start()
{
    /* Set cursor to middle of screen before we do anything in the frame */
    if(!show_cursor)
        win->set_cursor_pos(win->get_width() / 2, win->get_height() / 2);
}

void ModelDemo::update()
{
    /* Update cam position */

    if(Input.Keyboard[SDL_SCANCODE_ESCAPE] == KEY_STATE_PRESSED)
        toggle_cursor();

    if(!show_cursor)
    {
        cam.yaw += Input.Mouse.dx * cam.sensitivity;
        cam.pitch -= Input.Mouse.dy * cam.sensitivity;
        if(cam.pitch > 89.0f)
            cam.pitch = 89.0f;
        if(cam.pitch < -89.0f)
            cam.pitch = -89.0f;
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



void ModelDemo::toggle_cursor()
{
    show_cursor = !show_cursor;

    /* If we want to show cursor, then we want set relative off */
    /* If we don't want to show cursor, then we want set relative on */
    win->set_cursor_relative(!show_cursor);
}