#include "./core/Window.h"
#include "./core/Model.h"
#include "./core/Shader.h"
#include "./core/Texture.h"
#include "./core/Camera.h"
#include <iostream>
#include "./gui/gui.h"
#include "./core/input/input.h"


const int WIN_WIDTH = 1920;
const int WIN_HEIGHT = 1080;

bool show_cursor = false;

static void toggle_cursor();
static void process_keyboard();

int main()
{
    Window win("Render Library Demo", WIN_WIDTH, WIN_HEIGHT);

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



    bool should_close = false;
    while(!should_close)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            gui_process_event(&event);
            switch(event.type)
            {
                case SDL_MOUSEMOTION:
                    /* Do mouse motion stuff here */
                    if(!show_cursor)
                        SDL_WarpMouseInWindow(win.get_handle(), WIN_WIDTH / 2, WIN_HEIGHT / 2);
                    break;
                case SDL_QUIT:
                    should_close = true;
                    break;
                default:
                    break;
            }
        }

        process_keyboard();

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

static void process_keyboard()
{
    update_keyboard_state();
    const KeyState* keyboard = get_keyboard_state();

    if(keyboard[SDL_SCANCODE_ESCAPE] == KEY_STATE_PRESSED)
    {
        toggle_cursor();
    }

    // If adding a keyboard interaction here, don't forget to add the in update_keyboard_state()
    if(!show_cursor)
    {
        if(keyboard[SDL_SCANCODE_A] == KEY_STATE_PRESSED)
            std::cout << "A" << std::endl;

        if(keyboard[SDL_SCANCODE_S] == KEY_STATE_PRESSED)
            std::cout << "S" << std::endl;

        if(keyboard[SDL_SCANCODE_D] == KEY_STATE_PRESSED)
            std::cout << "D" << std::endl;

        if(keyboard[SDL_SCANCODE_W] == KEY_STATE_PRESSED)
            std::cout << "W" << std::endl;
    }

}