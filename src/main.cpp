#include <graphics.h>
#include <iostream>

/*#include "./core/Shader.h"
#include "./core/Window.h"
#include "./core/Texture.h"
#include "./core/Mesh.h"
#include "./core/Model.h"
#include "./math/lnal.h"
#include "./core/Camera.h"
#include "./core/audio.h"
#include "./game/Game.h"*/


#include "./math/lnal.h"
#include "./game/Game.h"


lnal::vec3 lightpos(1.0, 1.0, 1.0);

int main()
{

    Game game("SPOKERJYKER GAMKERJKL", 1280, 720);
    game.run();

    //Init engine
    /*SoLoud::Soloud soloud;
    SoLoud::Wav sample;

    soloud.init();
    sample.load("./assets/sounds/Lucas_Scream.wav");

    Window win("Spooky Game!!!!!", 1280, 720);

    //Load shaders and models (possibly on separate thread while showing splash)
    Shader s;
    if(!s.load("./shader/test.vert", "./shader/test.frag"))
    {
        std::cout << "Failed to load shader" << std::endl;
    }

    Shader diffuse_map;
    if(!diffuse_map.load("./shader/mapping.vert", "./shader/mapping.frag"))
        std::cout << "Failed to load shader" << std::endl;

    Texture diffuse_texture;
    if(!diffuse_texture.load("./assets/img/container2.png"))
        std::cout << "Failed to load texture" << std::endl;

    Texture specular_texture;
    if(!specular_texture.load("./assets/img/container2_specular.png"))
        std::cout << "Failed to load texture" << std::endl;

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
    
    Model cube;
    if(!cube.load("./assets/model/cube.fbx"))
        std::cout << "Failed to load model" << std::endl;

    Camera camera;
    camera.gen_perspective(PI / 2, (float)(1280.0f / 720.0f), 0.1, 10.0);

    bool quit = false;

    float angle = 0;

    lnal::vec3 axis(0.0, -1.0, 0.0);
    lnal::vec3 rotation_axis(1.0, 0.0, 1.0);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);    

    //int handle = soloud.play(sample);

    float x = 0.0;

    //Main loop
    while(!quit)
    {

        //Handle input
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

        //Physics / Game logic


        //Render
        camera.lookat(lnal::vec3(0.0, 0.0, 3.0), lnal::vec3(x, 0.0, 0.0), lnal::vec3(0.0, 1.0, 0.0));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.3, 0.3, 0.3, 1.0);

        lnal::mat4 model(1.0);
        lnal::scale(model, 0.01);
        lnal::rotate(model, axis, angle);
        lnal::translate_relative(model, lnal::vec3(0.0, -1.0, 0.0));

        angle += 0.001;

        lnal::vec3 lightcolor(1.0, 1.0, 1.0);

        lnal::vec3 ambient(0.0, 0.0, 0.0);
        lnal::vec3 diffuse(0.55, 0.55, 0.55);
        lnal::vec3 specular(0.7, 0.7, 0.7);

        lnal::vec3 lightambient(0.2, 0.2, 0.2);
        lnal::vec3 lightdiffuse(1.0, 1.0, 1.0);
        lnal::vec3 lightspecular(0.7, 0.7, 0.7);*/

        /*test.bind();
        test.set_mat4fv("model", model.data());
        test.set_mat4fv("view", camera.get_view());
        test.set_mat4fv("projection", camera.get_projection());

        //Will eventually get rid of light_color
        test.set_vec3fv("light_color", lightcolor.data());
        test.set_vec3fv("cam_pos", &(camera.get_position())[0]);
        test.set_vec3fv("material.ambient", ambient.data());
        test.set_vec3fv("material.diffuse", diffuse.data());
        test.set_vec3fv("material.specular", specular.data());
        test.set_float("material.shininess", 128);
        test.set_vec3fv("light.position", lightpos.data());
        test.set_vec3fv("light.ambient", lightambient.data());
        test.set_vec3fv("light.diffuse", lightdiffuse.data());
        test.set_vec3fv("light.specular", lightspecular.data());
        jupiter.draw(test);*/


        /*lnal::mat4 different_model(1.0);
        lnal::scale(different_model, 0.2);
        lnal::rotate(different_model, rotation_axis, angle);
        lnal::translate_relative(different_model, lnal::vec3(2.0, 0.0, 0.0));

        test.set_mat4fv("model", different_model.data());
        backpack.draw(test);*/


        /*lnal::mat4 cube_model(1.0);
        lnal::scale(cube_model, 0.3);
        lnal::rotate(cube_model, rotation_axis, -angle);
        lnal::translate_relative(cube_model, lnal::vec3(-1.0, 0.0, 0.0));

        diffuse_map.bind();
        diffuse_map.set_mat4fv("view", camera.get_view());
        diffuse_map.set_mat4fv("projection", camera.get_projection());

        //Will eventually get rid of light_color
        diffuse_map.set_vec3fv("light_color", lightcolor.data());
        diffuse_map.set_vec3fv("cam_pos", &(camera.get_position())[0]);
        diffuse_map.set_vec3fv("material.ambient", ambient.data());
        diffuse_map.set_vec3fv("material.diffuse", diffuse.data());
        //diffuse_map.set_vec3fv("material.specular", specular.data());
        diffuse_map.set_float("material.shininess", 1.28);
        diffuse_map.set_vec3fv("light.position", lightpos.data());
        diffuse_map.set_vec3fv("light.ambient", lightambient.data());
        diffuse_map.set_vec3fv("light.diffuse", lightdiffuse.data());
        diffuse_map.set_vec3fv("light.specular", lightspecular.data());
        diffuse_map.set_mat4fv("model", cube_model.data());

        diffuse_map.set_int("material.diffuse", 0);
        diffuse_map.set_int("material.specular", 1);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, diffuse_texture.get_id());

        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, specular_texture.get_id());
        
        cube.draw(diffuse_map);

        win.swap_buffers();
    }*/

    return 0;
}