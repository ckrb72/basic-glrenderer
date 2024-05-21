#pragma once
#include <vector>
#include <string>
#include <stdint.h>
#include "Texture.h"
#include "Shader.h"
#include "../math/lnal.h"


struct Vertex
{
    lnal::vec3 position;
    lnal::vec3 color;
    lnal::vec2 tex_coords;
};

class Mesh
{
private:
    std::vector<unsigned int> m_indices;
    std::vector<Vertex> m_vertices;
    std::vector<Texture> m_textures;
    uint32_t m_gl_vertex_array, m_gl_vertex_buffer, m_gl_index_buffer;

    bool gpu_gen_mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices);

public:

    Mesh();
    ~Mesh();

    //When not loading from file
    bool load(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);

    //Draws the mesh with the given shader.
    //NOTE - DOES NOT BIND THE SHADER FOR PERFORMANCE REASONS
    //MAKE SURE TO BIND THE SHADER BEFORE ANY CALLS TO draw()
    //@param shader shader to draw with
    void draw(Shader& shader);
};