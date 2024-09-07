#include "./core/Window.h"
#include "./core/Model.h"
#include "./core/Shader.h"
#include "./core/Texture.h"
#include "./core/Camera.h"
#include <iostream>
#include "./gui/gui.h"
#include "./core/input/input.h"
#include "./core/engine_time.h"
#include <graphics.h>
#include "./demo/demo.h"


const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;

bool show_cursor = false;

static void toggle_cursor(Window& win);

lnal::vec3 cam_pos = { 0.0f, 0.0f, 5.0f};
lnal::vec3 cam_up = { 0.0f, 1.0f, 0.0f };

int main()
{
    Window win("Render Library Demo", WIN_WIDTH, WIN_HEIGHT);

    init_input(&win);

    gui_setup(win);

    if(!demo_init(&win))
    {
        return -1;
    }


    Shader shader{};
    if (!shader.load("./shader/clip_space.vert", "./shader/clip_space.frag"))
    {
        std::cerr << "Failed to load shader" << std::endl;
    }


    Model jupiter{};
    if (!jupiter.load("./assets/model/jupiter.obj"))
    {
        std::cerr << "Failed to load model" << std::endl;
    }

    Camera cam{};

    cam.gen_perspective(PI / 2, (float)WIN_WIDTH / (float)WIN_HEIGHT, 0.1, 100.0);

    lnal::vec3 pos = { 0.0, 0.0, 3.0 };
    lnal::vec3 lookat = { 0.0, 0.0 ,0.0 };
    lnal::vec3 up = { 0.0, 1.0, 0.0 };
    cam.lookat();


    win.set_cursor_relative(true);


    calc_delta();
    

    while(!win.is_closed())
    {
        calc_delta();

        // demo_frame_start();

        /* If we aren't showing the cursor, then place it in the middle of the screen */
        if(!show_cursor)
            win.set_cursor_pos(WIN_WIDTH / 2, WIN_HEIGHT / 2);


        input_update();

        // demo_update();

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
            toggle_cursor(win);
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
        
        gui_create_frame();

        /* Draw Stuff */

        // demo_draw();

        win.clear();

        lnal::mat4 model(1.0);
        lnal::scale(model, 0.01);
        lnal::translate_relative(model, lnal::vec3(0.0, -1.0, -2.0));

        shader.bind();
        shader.set_mat4fv("model", model.data());
        shader.set_mat4fv("view", cam.get_view());
        shader.set_mat4fv("projection", cam.get_projection());
        jupiter.draw(shader);

        gui_draw();

        win.swap_buffers();
    }
    gui_shutdown();
}


static void toggle_cursor(Window& win)
{
    show_cursor = !show_cursor;

    /* If we want to show cursor, then we want set relative off */
    /* If we don't want to show cursor, then we want set relative on */
    win.set_cursor_relative(!show_cursor);
}
