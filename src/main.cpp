#include <graphics.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>

#include "./core/Shader.h"
#include "./core/Window.h"

int main()
{
    Window win("Spooky Game!!!!!", 1280, 720);
    glEnable(GL_DEPTH_TEST);

    Shader s;
    if(!s.load("./test.vert", "./test.frag"))
    {
        std::cout << "Failed to load shader" << std::endl;
    }


    bool quit = false;

    while(!quit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor(0.3, 0.3, 0.3, 1.0);


        win.swap_buffers();
    }

    return 0;
}