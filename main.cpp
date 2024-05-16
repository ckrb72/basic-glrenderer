#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

int main()
{
    
    Assimp::Importer importer;

    std::cout << "Importer made" << std::endl;

    const aiScene* scene = importer.ReadFile("./assets/utah_teapot.obj", aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    if(nullptr == scene || !scene->mRootNode)
    {
        std::cout << importer.GetErrorString() << std::endl;
        return -1;
    }

    aiNode* root_node = scene->mRootNode;

    //Go through all children of root node
    for(int i = 0; i < root_node->mNumChildren; i++)
    {
        aiNode* node = root_node->mChildren[i];

        //Go through each mesh of each child
        for(int j = 0; j < node->mNumMeshes; j++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[j]];

            //Print out vertices of each mesh of each child
            for(int k = 0; k < mesh->mNumVertices; k++)
            {
                std::cout << mesh->mVertices[k].x << " " << mesh->mVertices[k].y << " " << mesh->mVertices[k].z << std::endl;
            }

            //This is messed up right now but should load the indices
            for(int a = 0; a < mesh->mNumFaces; a++)
            {
                aiFace face = mesh->mFaces[a];
                for(int b = 0; b < face.mNumIndices; b++)
                    std::cout << face.mIndices[b] << " ";
                std::cout << std::endl;
            }              

        }
    }

    return 0;
}