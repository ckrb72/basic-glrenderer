#pragma once
#include <stdint.h>
#include <string>
#include "EntityManager.h"
#include "../core/audio.h"
#include "../core/Camera.h"
#include "../core/Window.h"


class Game
{
private:
    uint32_t m_width;
    uint32_t m_height;

    EntityManager m_entity_manager;
    Window m_window;
    Camera m_camera;
    //AudioManager m_audio_manager;

    SoLoud::Soloud m_audio_manager;
    

    bool m_quit = false;

    void show_splash();
    
public:
    Game(const std::string& name, uint32_t width, uint32_t height);

    ~Game();

    void run();
};