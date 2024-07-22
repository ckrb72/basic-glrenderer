#include "Game.h"
#include <vector>
#include "../core/Mesh.h"
#include <debug.h>
#include "../core/SpriteSheet.h"
#include "../core/engine_time.h"
#include "../core/Model.h"

#include "./scenes/ScSplash.h"

#include <iostream>
#include <graphics.h>


//Would put these in an array or something of objects to render with all the stuff needed but for now this is just a hack to see if this works
static float angle = 0;

static lnal::vec3 axis(0.0, -1.0, 0.0);
static lnal::vec3 rotation_axis(1.0, 0.0, 1.0);

static Shader default_shader;
static Model jupiter;

Game::Game(const std::string& name, uint32_t width, uint32_t height)
:m_window(name, width, height)
{
    //Start audio manager (will eventually put this in a wrapper class and put in initializer list)

    //Set up input devices


    //Set up scenes
    //scene.create.and.stuff()
    //m_scenes.push_back(&scene)

    //Generate camera projection matrix
    m_camera.gen_perspective(PI / 2, (float)((float)width / (float)height), 0.1, 10.0);
}

Game::~Game()
{

}

void Game::run()
{


    std::shared_ptr<Scene> scene = std::make_shared<ScSplash>();
    scene->start();
    scene->set_camera(m_camera);

/*

    For final engine would have a pointer to the scene class and do the following

    while(!m_quit)
    {

        if(scene_change_event)
        {
            change_scene(&new_scene);
        }

        scene->update_time();
        scene->handle_events();
        scene->update_physics();
        scene->render();
    }

*/


    /*update_time();

    show_splash();

    if(!jupiter.load("./assets/model/jupiter.obj"))
        std::cout << "Failed to load jupiter model" << std::endl;

    if(!default_shader.load("./shader/default.vert", "./shader/default.frag"))
    {
        std::cout << "Failed to load shader" << std::endl;
    }*/

    while(!m_quit)
    {
        //Update Delta Time
        //update_time();

        //Handle Input
        handle_events();

        scene->update();

        m_window.clear();

        scene->render();

        m_window.swap_buffers();

        //Do game stuff like rendering, physics, game logic

        //game_logic();
        //render();

    }
}

//Shows splash screen on startup
void Game::show_splash()
{
    Shader splash_shader;
    splash_shader.load("./shader/splash.vert", "./shader/splash.frag");

    //Audio stuff (will abstract this later)
    SoLoud::Wav boom;
    boom.load("./assets/sound/vine_boom_sound.wav");

    //Load spritesheet
    SpriteSheet splash_mesh;

    if(!splash_mesh.load("./assets/img/splashscreen.png"))
    {
        dbglog("Failed to load splash screen");
    }

    bool sheet_done = false;

    splash_shader.bind();

    lnal::mat4 model(1.0);
    lnal::translate_relative(model, lnal::vec3(0.0, 0.0, -1.0));

    splash_shader.set_mat4fv("model", model.data());
    splash_shader.set_mat4fv("projection", m_camera.get_projection());
    splash_shader.set_mat4fv("view", m_camera.get_view());
    splash_shader.set_int("sprite_sheet", 0);

    splash_mesh.set_size(256, 256);

    uint32_t x = 0;

    //Actually play the sound
    //int handle = m_audio_manager.play(boom);

    float time = 0;

    //Play frames of spritesheet
    while(!sheet_done && !m_quit)
    {
        update_time();

        //Handle basic events so window doesn't crash
        handle_events();

        splash_mesh.set_clip(x, 0);

        if(time >= 0.1)
        {
            x += 256;
            time = 0.0;
        }

        time += delta_time;

        m_window.clear();

        //Draw frames
        splash_mesh.draw();

        m_window.swap_buffers();

        if(x == 4096)
            sheet_done = true;
    }
}

void Game::update_time()
{
   delta_time = calc_delta();
}



void Game::handle_events()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                m_quit = true;
                break;

            case SDL_MOUSEMOTION:
                break;
                
            default:
                break;
        }
    }

    const uint8_t* keyboard_state = SDL_GetKeyboardState(nullptr);

    uint8_t w = keyboard_state[SDL_GetScancodeFromName("w")];

    if(w)
    {
        std::cout << "Key Pressed" << std::endl;
    }


    uint8_t esc = keyboard_state[SDL_GetScancodeFromName("escape")];

    if(esc)
    {
        m_quit = true;
    }


}

void Game::render()
{
    m_window.clear();
    
    
    //Go through entity manager and draw everything in there...
    //Or maybe have a pool somewhere that holds all things we want to draw...
    //i.e. m_entity_manager.draw    or      m_render_pool.draw
    m_camera.lookat(lnal::vec3(0.0, 0.0, 3.0), lnal::vec3(0.0, 0.0, 0.0), lnal::vec3(0.0, 1.0, 0.0));


    lnal::mat4 model(1.0);
    lnal::scale(model, 0.01);
    lnal::rotate(model, axis, angle);
    lnal::translate_relative(model, lnal::vec3(0.0, -1.0, -2.0));

    default_shader.set_mat4fv("model", model.data());
    default_shader.set_mat4fv("view", m_camera.get_view());
    default_shader.set_mat4fv("projection", m_camera.get_projection());

    angle += 0.001;

    jupiter.draw(default_shader);

    m_window.swap_buffers();
}


//in input handling make a function or something that updates camera position based on the mouse movement