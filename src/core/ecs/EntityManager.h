#pragma once
#include <vector>
#include <map>
#include "Entity.h"

class EntityManager
{
private:

    std::vector<std::shared_ptr<Entity>> m_entities;
    std::vector<std::shared_ptr<Entity>> m_entities_to_add;
    std::map<std::string, std::vector<std::shared_ptr<Entity>>> m_entity_map;

    uint32_t m_entity_count = 0;

public:

    EntityManager();

    ~EntityManager();

    std::shared_ptr<Entity> create_entity(const std::string& type);

    void update();
};