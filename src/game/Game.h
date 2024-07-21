#pragma once
#include <stdint.h>
#include <string>
#include "EntityManager.h"
#include "../core/audio.h"
#include "../core/Camera.h"
#include "../core/Window.h"
#include "../core/EventManager.h"
#include "Scene.h"


class Game
{
private:
    uint32_t m_width;
    uint32_t m_height;
    float delta_time;
    bool m_quit = false;

    //Need to think about if I want to use pointers and what kind to use (unique, shared, raw!!!!, etc.)
    std::vector<std::shared_ptr<Scene>> m_scenes;

    EntityManager m_entity_manager;

    //Handles input and events (i.e. keyboard and mouse inputs and windows events)
    EventManager m_event_manager;

    Window m_window;
    Camera m_camera;

    //AudioManager m_audio_manager;
    SoLoud::Soloud m_audio_manager;


    //These functions are now going to be in the individual scene but if I change this right
    //now everything will break so I'm going to leave this for now
    

    //The splash screen will actually be it's own scene once I have that implemented
    //but right now this is fine
    //Splash screen fun!!!
    void show_splash();

    //Timing
    void update_time();

    //Input
    void handle_events();

    //Physics
    void newtons_nightmare();

    //Rendering
    void render();
    
public:
    Game(const std::string& name, uint32_t width, uint32_t height);

    ~Game();

    void run();
};