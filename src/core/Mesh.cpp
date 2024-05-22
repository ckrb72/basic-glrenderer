#include "Mesh.h"
#include <graphics.h>
#include <iostream>

Mesh::Mesh()
:m_vao(0), m_vbo(0), m_ebo(0)
{}


Mesh::~Mesh()
{
    //Vectors are RAII so no need to free them here


    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
}

void Mesh::draw(Shader& shader)
{
    //Set up uniforms


    //For batch rendering this would be completely different but we probably won't do that until we get
    //text rendering going and stuff
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);

}

bool Mesh::load(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    //Generate the mesh on GPU
    if(!gpu_gen_mesh(vertices, indices))
        return false;

    std::cout << m_vao << std::endl;

    //If everything went well set member variables
    this->m_vertices = vertices;
    this->m_indices = indices;
    this->m_textures = textures;

    return true;
}

bool Mesh::gpu_gen_mesh(const std::vector<Vertex>& vertices,const std::vector<unsigned int>& indices)
{

    uint32_t vao, vbo, ebo;

    //Generate the buffers
    glGenVertexArrays(1, &vao);
    //std::cout << vao << std::endl;

    glGenBuffers(1, &vbo);
    //std::cout << vbo << std::endl;
    glGenBuffers(1, &ebo);
    //std::cout << ebo << std::endl;

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return true;
}