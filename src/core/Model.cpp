#include "Model.h"
#include "Mesh.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <iostream>


Model::Model()
{}


Model::~Model()
{}

void Model::draw(Shader& shader)
{
    for(uint32_t i = 0; i < m_meshes.size(); i++)
    {
        //std::cout << "Drawing Mesh" << std::endl;
        m_meshes[i].draw(shader);
    }
}


bool Model::load(const std::string& filepath)
{
    //Here if we do multithreading we would send request to a queue and then have a special loader thread fulfill that

    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices | aiProcess_FlipUVs);

    if(!scene)
    {
        //TODO: Added error_log function for debug purposes
        //error_log("Failed to load model");
        return false;
    }


    processNode(scene->mRootNode, scene);

    std::cout << m_meshes.size() << std::endl;

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

        /*if(mesh->mTextureCoords[0])
        {
            lnal::vec2 tex_coords;
            tex_coords[0] = mesh->mTextureCoords[0][i].x;
            tex_coords[1] = mesh->mTextureCoords[0][i].y;
            vertex.tex_coords = tex_coords;
        }
        else
        {
            vertex.tex_coords = lnal::vec2(0.0, 0.0);
        }*/

        vertex.tex_coords = lnal::vec2(0.0, 0.0);

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



    Mesh m;
    m.load(vertices, indices, textures);
    return m;
}