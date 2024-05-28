#pragma once
#include <memory>
#include "../core/Model.h"


class Entity
{
private:
    uint32_t m_id;
    const std::string m_tag;

public:

    //Might want this to be unique_ptr but probably not
    //since we might want to have an optimization where multiple entites share
    //the same model
    std::shared_ptr<Model> model = nullptr;

    Entity(uint32_t id, const std::string& tag);

    ~Entity();

    const std::string& tag();

};