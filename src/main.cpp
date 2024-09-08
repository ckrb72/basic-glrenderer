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


int main()
{
    Window win("Render Library Demo", WIN_WIDTH, WIN_HEIGHT);


    init_input(&win);

    gui_setup(win);

    if(!demo_init(&win))
    {
        return -1;
    }


    win.set_cursor_relative(true);
    calc_delta();
    

    while(!win.is_closed())
    {
        calc_delta();

        demo_frame_start();


        input_update();

        demo_update();

        gui_create_frame();

        /* Draw Stuff */

        win.clear();

        demo_draw();
        gui_draw();

        win.swap_buffers();
    }
    gui_shutdown();
}