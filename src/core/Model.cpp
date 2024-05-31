#include "Model.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <debug.h>


Model::Model()
{}

Model::~Model()
{}

void Model::draw(Shader& shader)
{
    for(uint32_t i = 0; i < m_meshes.size(); i++)
    {
        m_meshes[i]->draw(shader);
    }
}


bool Model::load(const std::string& filepath)
{
    //Here if we do multithreading we would send request to a queue and then have a special loader thread fulfill that

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

    if(!scene)
    {
        error_log("Failed to load model");
        return false;
    }
    dbglog("Model loaded...");


    processNode(scene->mRootNode, scene);

    return true;
}

bool Model::processNode(aiNode* node, const aiScene* scene)
{

    for(uint32_t i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

        std::unique_ptr<Mesh> m = processMesh(mesh, scene);

        if(m == nullptr)
        {
            dbglog("Failed to process mesh");
            return false;
        }
        
        m_meshes.push_back(std::move(m));
    }

    for(uint32_t i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

    return true;
}

std::unique_ptr<Mesh> Model::processMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    std::unique_ptr<Mesh> m = std::make_unique<Mesh>();

    //process vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;

        lnal::vec3 vector;

        vector[0] = mesh->mVertices[i].x;
        vector[1] = mesh->mVertices[i].y;
        vector[2] = mesh->mVertices[i].z;

        vertex.position = vector;

        vector[0] = mesh->mNormals[i].x;
        vector[1] = mesh->mNormals[i].y;
        vector[2] = mesh->mNormals[i].z;

        vertex.normal = vector;

        if(mesh->mTextureCoords[0])
        {
            lnal::vec2 tex_coords;
            tex_coords[0] = mesh->mTextureCoords[0][i].x;
            tex_coords[1] = mesh->mTextureCoords[0][i].y;
            vertex.tex_coords = tex_coords;
        }
        else
        {
            vertex.tex_coords = lnal::vec2(0.0, 0.0);
        }

        vertices.push_back(vertex);
    }

    //process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for(unsigned int j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    //process materials
    if(mesh->mMaterialIndex >= 0)
    {
        
    }

    if(!m->load(vertices, indices, textures))
        return nullptr;

    return m;
}