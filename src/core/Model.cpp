#include "Model.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


Model::Model()
{}


Model::~Model()
{}


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

    return true;
}