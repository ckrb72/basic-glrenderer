#include "TextureDemo.h"
#include <imgui.h>
#include "../core/input/input.h"
#include "../core/engine_time.h"
#include "../math/lnal.h"
#include <cmath>
#include <iostream>
#include <graphics.h>

static unsigned int vao, vbo, ebo;

static float vertices[] = 
{
    -0.5, -0.5, 0.0,   0.0, 0.0,
    0.5, -0.5, 0.0,    1.0, 0.0,
    0.5, 0.5, 0.0,     1.0, 1.0,
    -0.5, 0.5, 0.0,    0.0, 1.0
};

static unsigned int indices[] = 
{
    0, 1, 2,
    2, 3, 0
};


bool TextureDemo::init(Window* win)
{
    this->win = win;

    cam.gen_perspective(PI / 2, ((float)win->get_width()) / ((float)win->get_height()), 0.1, 100.0);

    if(!texture_shader.load("./shader/texture.vert", "./shader/texture.frag"))
    {
        std::cerr << "Failed to load Texture Shader" << std::endl;
        return false;
    }

    if(!tex.load("./assets/img/container.jpg"))
    {
        std::cerr << "Failed to load Texture" << std::endl;
        return false;
    }

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Enable attributes 

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    cam.position = { 0.0, 0.0, 5.0 };
    cam.forward = { 0.0, 0.0, 0.0 };
    cam.up = { 0.0, 1.0, 0.0 };

    return true;
}

void TextureDemo::frame_start()
{
    /* If we aren't showing the cursor, then place it in the middle of the screen */
    if(!show_cursor)
        win->set_cursor_pos(win->get_width() / 2, win->get_height() / 2);
}

void TextureDemo::update()
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

void TextureDemo::draw()
{
    lnal::mat4 model(1.0);

    texture_shader.bind();
    texture_shader.set_mat4fv("model", model.data());
    texture_shader.set_mat4fv("view", cam.get_view());
    texture_shader.set_mat4fv("projection", cam.get_projection());
    texture_shader.set_int("container", 0);
    texture_shader.set_vec3fv("tex_color", tex_color.data());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex.get_id());

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

}

void TextureDemo::on_load()
{

}

void TextureDemo::toggle_cursor()
{
    show_cursor = !show_cursor;

    /* If we want to show cursor, then we want set relative off */
    /* If we don't want to show cursor, then we want set relative on */
    win->set_cursor_relative(!show_cursor);
}

void TextureDemo::gui_create_frame()
{
    ImGui::SeparatorText("Texture");
    ImGui::ColorEdit3("Color", tex_color.data());
}