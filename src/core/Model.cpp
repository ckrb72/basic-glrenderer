#include "Model.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


Model::Model()
{}


Model::~Model()
{}

void Model::draw(Shader& shader)
{
    for(uint32_t i = 0; i < m_meshes.size(); i++)
    {
        m_meshes[i].draw(shader);
    }
}


bool Model::load(const std::string& filepath)
{
    
    //Here if we do multithreading we would send request to a queue and then have a special loader thread fulfill that

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    if(!scene)
    {
        //TODO: Added error_log function for debug purposes
        //error_log("Failed to load model");
        return false;
    }

    processNode(scene->mRootNode, scene);

    return true;
}

void Model::processNode(aiNode* node, const aiScene* scene)
{
    for(uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.push_back(processMesh(mesh, scene));
    }

    for(uint32_t i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;



    return Mesh();
}