#include "ModelDemo.h"
#include <iostream>
#include "../core/input/input.h"
#include "../core/engine_time.h"

bool ModelDemo::init(Window* win)
{
    this->win = win;


    float aspect_ratio = (float)win->get_width() / (float)win->get_height();

    cam.gen_perspective(PI / 2, (float)1920.0/ (float)1080.0, 0.1, 100.0);

    std::shared_ptr<Model> jupiter = std::make_shared<Model>();
    if(!jupiter->load("./assets/model/jupiter.obj"))
    {
        std::cerr << "Failed to load jupiter model" << std::endl;
        return false;
    }

    models.push_back(jupiter);

    std::shared_ptr<Shader> normals = std::make_shared<Shader>();
    if(!normals->load("./shader/normals.vert", "./shader/normals.frag"))
    {
        std::cerr << "Failed to load normals shader" << std::endl;
        return false;
    }

    shaders.push_back(normals);

    std::shared_ptr<Shader> world_space = std::make_shared<Shader>();
    if(!world_space->load("./shader/world_space.vert", "./shader/world_space.frag"))
    {
        std::cerr << "Failed to load world_space shader" << std::endl;
        return false;
    }

    shaders.push_back(world_space);


    cur_model = models[0];
    cur_shader = shaders[0];

    cam.position = { 0.0, 0.0, 3.0 };
    cam.forward = { 0.0, 0.0, 0.0 };
    cam.up = { 0.0, 1.0, 0.0 };

    lnal::scale(model, 0.01);

    return true;
}

void ModelDemo::draw()
{

    /* Draw currently selected model with currently selected shader */

    lnal::mat4 model(1.0);
    lnal::scale(model, 0.01);
    lnal::translate_relative(model, lnal::vec3(0.0, -1.0, -2.0));

    cur_shader->bind();
    cur_shader->set_mat4fv("model", model.data());
    cur_shader->set_mat4fv("view", cam.get_view());
    cur_shader->set_mat4fv("projection", cam.get_projection());
    cur_model->draw(*cur_shader);

}

void ModelDemo::frame_start()
{
    /* If we aren't showing the cursor, then place it in the middle of the screen */
    if(!show_cursor)
        win->set_cursor_pos(win->get_width() / 2, win->get_height() / 2);
}

void ModelDemo::update()
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



void ModelDemo::toggle_cursor()
{
    show_cursor = !show_cursor;

    /* If we want to show cursor, then we want set relative off */
    /* If we don't want to show cursor, then we want set relative on */
    win->set_cursor_relative(!show_cursor);
}