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


    uint32_t m_width;
    uint32_t m_height;
    float delta_time;
    bool m_quit = false;

    //Handles input and events (i.e. keyboard and mouse inputs and windows events)
    EventManager m_event_manager;

    Window m_window;
    Camera m_camera;

    Scene* m_current_scene;

    //This should not use raw scene pointers since we want the scenes to destruct once they are deleted from this
    //Shared pointers are probably the best but I don't know how this affect polymorphism in c++
    std::map<std::string, std::shared_ptr<Scene>> m_scenes; 









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

    void change_scene(Scene* scene);

    Camera& get_camera();

    Window& get_window();
};