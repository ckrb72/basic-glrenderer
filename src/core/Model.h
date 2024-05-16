#pragma once
#include <vector>
#include "Mesh.h"

//Model is wrapper around Mesh.
//Can have multiple Meshes in a single model
class Model
{
private:
    std::vector<Mesh> m_meshes;

public: 

    Model();

    ~Model();

    void load();
};