#include "Entity.h"


Entity::Entity(uint32_t id, const std::string& tag)
:m_tag(tag), m_id(id)
{}

Entity::~Entity()
{}

const std::string& Entity::tag()
{
    return m_tag;
}