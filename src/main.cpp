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


const int WIN_WIDTH = 1500;
const int WIN_HEIGHT = 844;


float elapsed_time = 0.0;
uint64_t previous_time = 0;

/* If FPS == 0.0 then no cap and engine runs as fast as possible */
float FPS = 60.0;


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
    
    previous_time = get_ticks();

    while(!win.is_closed())
    {

        uint64_t current_time = get_ticks();
        elapsed_time += (float)(current_time - previous_time) * 0.001;
        previous_time = current_time;

        if(elapsed_time >= (1 / FPS) || FPS == 0.0)
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

            elapsed_time = 0.0;
        }
    }
    gui_shutdown();
}