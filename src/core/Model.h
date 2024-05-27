#pragma once
#include "Mesh.h"
#include "Shader.h"
#include "../math/lnal.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <memory>

//Model is wrapper around Mesh.
//Can have multiple Meshes in a single model
class Model
{
private:
    std::vector<std::unique_ptr<Mesh>> m_meshes;
    lnal::mat4 model;

    bool processNode(aiNode* node, const aiScene* scene);
    std::unique_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);


public: 

    Model();

    ~Model();

    bool load(const std::string& filepath);

    void draw(Shader& shader);
};