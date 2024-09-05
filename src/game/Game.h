#pragma once
#include <stdint.h>
#include <string>
#include <map>
#include <memory>
#include "../core/Camera.h"
#include "../core/Window.h"
#include "../core/input/input.h"
#include "../core/Scene.h"


/*
    Need to add audio
*/

class Game
{
private:
    bool m_quit = false;

    Window m_window;
    InputManager m_input;

    std::shared_ptr<Scene> m_cur_scene;
    std::map<std::string, std::shared_ptr<Scene>> m_scenes; 

    //Timing
    void update_time();

    //Input
    void handle_events();

    //Rendering
    void render();
    
public:
    Game(const std::string& name, uint32_t width, uint32_t height);

    ~Game();

    float delta_time;

    void run();

    //This will go into a scene manager
    void change_scene(const std::string& scene_name);
};