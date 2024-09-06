#include "./core/Window.h"
#include "./core/Model.h"
#include "./core/Shader.h"
#include "./core/Texture.h"
#include "./core/Camera.h"
#include <iostream>
#include "./gui/gui.h"
#include "./core/input/input.h"
#include "./core/engine_time.h"


const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;

bool show_cursor = false;

static void toggle_cursor();

float delta = 0.0f;

lnal::vec3 cam_pos = { 0.0f, 0.0f, 5.0f};
lnal::vec3 cam_up = { 0.0f, 1.0f, 0.0f };

int main()
{
    Window win("Render Library Demo", WIN_WIDTH, WIN_HEIGHT);

    SDL_GL_SetSwapInterval(0);

    init_input();

    gui_setup(win);

    Shader shader{};
    if (!shader.load("./shader/default.vert", "./shader/default.frag"))
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
    cam.lookat(pos, lookat, up);


    // Start demo with cursor not showing
    SDL_SetRelativeMouseMode(SDL_TRUE);


    delta = calc_delta();


    bool should_close = false;

    float yaw = -90.0f;
    float pitch = 0.0f;
    float sensitivity = 0.1f;


    while(!should_close)
    {
        delta = calc_delta();


        /* Handle Input */
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            gui_process_event(&event);
            switch(event.type)
            {
                case SDL_MOUSEMOTION:
                    /* Do mouse motion stuff here */
                    if(!show_cursor)
                    {
                        SDL_WarpMouseInWindow(win.get_handle(), WIN_WIDTH / 2, WIN_HEIGHT / 2);
                        yaw += event.motion.xrel * sensitivity;
                        pitch -= event.motion.yrel * sensitivity;
                        if(pitch > 89.0f)
                            pitch = 89.0f;
                        if(pitch < -89.0f)
                            pitch = -89.0f;
                    }
                    break;
                case SDL_QUIT:
                    should_close = true;
                    break;
                default:
                    break;
            }
        }

        update_keyboard_state();
        const KeyState* keyboard = get_keyboard_state();

        if(keyboard[SDL_SCANCODE_ESCAPE] == KEY_STATE_PRESSED)
        {
            toggle_cursor();
        }



        // Camera look direction based on mouse movement
        lnal::vec3 look_dir{};
        look_dir[0] = cos(lnal::radians(yaw)) * cos(lnal::radians(pitch));
        look_dir[1] = sin(lnal::radians(pitch));
        look_dir[2] = sin(lnal::radians(yaw)) * cos(lnal::radians(pitch));

        look_dir.normalize();


        // If adding a keyboard interaction here, don't forget to add the in update_keyboard_state()
        if(!show_cursor)
        {
            if(keyboard[SDL_SCANCODE_A] == KEY_STATE_HELD)
                cam_pos -= delta * lnal::cross(look_dir, cam_up);

            if(keyboard[SDL_SCANCODE_S] == KEY_STATE_HELD)
                cam_pos -= delta * look_dir;

            if(keyboard[SDL_SCANCODE_D] == KEY_STATE_HELD)
                cam_pos += delta * lnal::cross(look_dir, cam_up);

            if(keyboard[SDL_SCANCODE_W] == KEY_STATE_HELD)
                cam_pos += delta * look_dir;

            if(keyboard[SDL_SCANCODE_SPACE] == KEY_STATE_HELD)
                cam_pos += delta * cam_up;

            if(keyboard[SDL_SCANCODE_LSHIFT] == KEY_STATE_HELD)
                cam_pos -= delta * cam_up;
        }

        cam.lookat(cam_pos, cam_pos + look_dir, cam_up);


        /* Draw Stuff */
        gui_create_frame();

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


static void toggle_cursor()
{
    show_cursor = !show_cursor;
    SDL_bool show;
    if(show_cursor)
        show = SDL_FALSE;
    else
        show = SDL_TRUE;
    
    SDL_SetRelativeMouseMode(show);
}
