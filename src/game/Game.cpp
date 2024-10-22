#include "Game.h"
#include <vector>
#include <debug.h>
#include "../core/engine_time.h"

#include "./scenes/scene_list.h"

#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>

#include <iostream>

float elapsed_time = 0.0;
bool scene_switched = false;

Game::Game(const std::string& name, uint32_t width, uint32_t height)
:m_window(name, width, height)
{
    //Start audio manager (will eventually put this in a wrapper class and put in initializer list)

    //Set up input devices

    //Set up scenes
    std::shared_ptr<Scene> splashscreen = std::make_shared<ScSplash>();
    m_scenes["sc_splash"] = splashscreen;

    m_scenes["jupiter_bust"] = std::make_shared<ScStatue>();
}

Game::~Game() 
{
}

void Game::run()
{

    m_cur_scene = m_scenes["sc_splash"];

    m_cur_scene->start();

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
    while(!m_quit)
    {

        if(elapsed_time >= 3.0 && !scene_switched)
        {
            change_scene("jupiter_bust");
            scene_switched = true;
        }

        //Update Delta Time
        update_time();

        //Handle Input
        handle_events();

        m_cur_scene->update(delta_time);

        render();

        elapsed_time += delta_time;
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

    /*
        Want to make an input manager that you can query the key for
        For example, if(input.keyboard.is_pressed('a')) { ... }
        or if(input.mouse.is_pressed('left')) { ... }
    */


}

void Game::render()
{
    m_window.clear();

    m_cur_scene->render();

    m_window.swap_buffers();
}

void Game::change_scene(const std::string& scene_name)
{
    m_cur_scene = m_scenes[scene_name];

    m_cur_scene->start();
}