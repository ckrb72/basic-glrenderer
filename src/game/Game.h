#pragma once
#include <types.h>
#include <string>
#include "EntityManager.h"
#include "../core/Camera.h"
#include "../core/Shader.h"
#include "../core/Window.h"


class Game
{
private:
    EntityManager m_entity_manager;

public:
    Game(const std::string& name, uint32_t width, uint32_t height);

    ~Game();
};