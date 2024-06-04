#include "Game.h"
#include <vector>
#include "../core/Mesh.h"
#include <debug.h>
#include "../core/SpriteSheet.h"
#include "../core/engine_time.h"

#include <iostream>
#include <graphics.h>

Game::Game(const std::string& name, uint32_t width, uint32_t height)
:m_window(name, width, height), m_width(width), m_height(height)
{
    //Start audio manager (will eventually put this in a wrapper class and put in initializer list)
    m_audio_manager.init();

    //Set up input devices

    //Generate camera projection matrix
    m_camera.gen_perspective(PI / 2, (float)((float)m_width / (float)m_height), 0.1, 10.0);
}

Game::~Game()
{
    m_audio_manager.deinit();
}

void Game::run()
{
    update_time();
    show_splash();
    
    while(!m_quit)
    {
        //Update Delta Time
        update_time();

        //Handle Input
        handle_events();

        //Do game stuff like rendering, physics, game logic


        //game_logic();


        render();

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
            default:
                break;
        }
    }

    const uint8_t* keyboard_state = SDL_GetKeyboardState(nullptr);

    uint8_t w = keyboard_state[SDL_GetScancodeFromName("w")];


}

void Game::render()
{
    m_window.clear();
    
    
    //Go through entity manager and draw everything in there...
    //Or maybe have a pool somewhere that holds all things we want to draw...


    m_window.swap_buffers();
}