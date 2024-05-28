#include "EntityManager.h"

EntityManager::EntityManager()
{

}

EntityManager::~EntityManager()
{

}

std::shared_ptr<Entity> EntityManager::create_entity(const std::string& tag)
{

    //Create entity
    std::shared_ptr<Entity> entity = std::make_shared<Entity>(m_entity_count++, tag);

    //Add to vector of entities to push back
    m_entities_to_add.push_back(entity);

    return entity;
}

void EntityManager::update()
{
    //Here is where we add entities to manager (do it here to prevent iterator invalidation)
    for(std::shared_ptr<Entity>& e : m_entities_to_add)
    {
        m_entities.push_back(e);
        m_entity_map[e->tag()].push_back(e);
    }
}
