#pragma once
#include <vector>
#include "Mesh.h"
#include "../math/lnal.h"

//Model is wrapper around Mesh.
//Can have multiple Meshes in a single model
class Model
{
private:
    std::vector<Mesh> m_meshes;
    lnal::mat4 model;

public: 

    Model();

    ~Model();

    bool load(const std::string& filepath);
};