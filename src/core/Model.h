#pragma once
#include <vector>
#include "Mesh.h"
#include "Shader.h"
#include "../math/lnal.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//Model is wrapper around Mesh.
//Can have multiple Meshes in a single model
class Model
{
private:
    std::vector<Mesh> m_meshes;
    lnal::mat4 model;

    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);


public: 

    Model();

    ~Model();

    bool load(const std::string& filepath);

    void draw(Shader& shader);
};