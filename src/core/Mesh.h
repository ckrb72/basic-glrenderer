#pragma once
#include <vector>
#include <string>
#include <stdint.h>
#include "Texture.h"
#include "Shader.h"


class Mesh
{
private:
    std::vector<uint32_t> m_indices;
    //std::vector<Vertex> m_vertices;
    std::vector<Texture> m_textures;
    uint32_t m_vertex_array, m_vertex_buffer, m_index_buffer;

public:

    Mesh();
    ~Mesh();

    //When not loading from file
    bool load(/*std::vector<Vertex> vertices*/ std::vector<uint32_t> indices);

    //Draws the mesh with the given shader.
    //NOTE - DOES NOT BIND THE SHADER FOR PERFORMANCE REASONS
    //MAKE SURE TO BIND THE SHADER BEFORE ANY CALLS TO draw()
    //@param shader shader to draw with
    void draw(Shader& shader);
};