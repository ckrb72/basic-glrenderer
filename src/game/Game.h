#pragma once
#include <stdint.h>
#include <string>
#include <map>
#include "../core/audio.h"
#include "../core/Camera.h"
#include "../core/Window.h"
#include "../core/EventManager.h"
#include "Scene.h"


/*
    Need to add audio
*/

class Game
{
private:
    bool m_quit = false;

    //Handles input and events (i.e. keyboard and mouse inputs and windows events)
    EventManager m_event_manager;

    Window m_window;
    Camera m_camera;

    Scene* m_current_scene;
    std::map<std::string, std::shared_ptr<Scene>> m_scenes; 

    //Timing
    void update_time();

    //Input
    void handle_events();

    //Rendering
    void render();

    //FIXME: WILL DELETE THIS ONCE SCENES ARE IMPLEMENTED
    //Splash screen fun!!!
    void show_splash();
    
public:
    Game(const std::string& name, uint32_t width, uint32_t height);

    ~Game();

    float delta_time;

    void run();

    void change_scene(Scene* scene);
};