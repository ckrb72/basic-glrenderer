#include <graphics.h>
#include <iostream>

#include "./core/Shader.h"
#include "./core/Window.h"
#include "./core/Texture.h"
#include "./core/Mesh.h"
#include "./core/Model.h"
#include "./math/lnal.h"
#include "./core/Camera.h"

#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>

lnal::vec3 lightpos(1.0, 1.0, 1.0);

int main()
{

    SoLoud::Soloud soloud;
    SoLoud::Wav sample;

    soloud.init();
    sample.load("./assets/sounds/Lucas_Scream.wav");

    Window win("Spooky Game!!!!!", 1280, 720);

    Shader s;
    if(!s.load("./shader/test.vert", "./shader/test.frag"))
    {
        std::cout << "Failed to load shader" << std::endl;
    }

    Texture t;

    if(!t.load("./assets/img/linux_PNG12.png"))
    {
        std::cout << "Failed to load texture!" << std::endl;
    }

    Shader test;
    if(!test.load("./shader/light.vert", "./shader/light.frag"))
    {
        std::cout << "Failed to load shader" << std::endl;
    }

    Model jupiter;

    if(!jupiter.load("./assets/model/jupiter.obj"))
        std::cout << "Failed to load model" << std::endl;

    Model backpack;

    if(!backpack.load("./assets/model/backpack/backpack.obj"))
        std::cout << "Failed to load model" << std::endl;

    Camera camera;
    camera.gen_perspective(PI / 2, (float)(1280.0f / 720.0f), 0.1, 10.0);

    bool quit = false;

    float angle = 0;

    lnal::vec3 axis(0.0, -1.0, 0.0);

    /*s.set_int("container", 0);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, t.get_id());*/

    lnal::mat4 different_model(1.0);

    lnal::scale(different_model, 0.2);
    lnal::translate_relative(different_model, lnal::vec3(2.0, 0.0, 0.0));

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    

    //int handle = soloud.play(sample);


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
            
            //SDL2 keyboard input handling
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                default:
                    break;
            }
        }

        camera.lookat(lnal::vec3(0.0, 0.0, 3.0), lnal::vec3(0.0, 0.0, 0.0), lnal::vec3(0.0, 1.0, 0.0));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.3, 0.3, 0.3, 1.0);

        lnal::mat4 model(1.0);
        lnal::scale(model, 0.01);
        //lnal::rotate(model, axis, angle);
        lnal::translate_relative(model, lnal::vec3(0.0, -1.0, 0.0));

        angle += 0.001;

        lnal::vec3 lightcolor(0.5, 0.5, 0.5);

        test.bind();
        test.set_mat4fv("model", model.data());
        test.set_mat4fv("view", camera.get_view());
        test.set_mat4fv("projection", camera.get_projection());
        test.set_vec3fv("light_color", lightcolor.data());
        test.set_vec3fv("light_pos", lightpos.data());
        test.set_vec3fv("cam_pos", camera.get_position());
        jupiter.draw(test);

        test.set_mat4fv("model", different_model.data());
        backpack.draw(test);

        win.swap_buffers();
    }

    return 0;
}