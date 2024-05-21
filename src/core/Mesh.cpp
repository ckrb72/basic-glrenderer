#include "Mesh.h"
#include <graphics.h>

Mesh::Mesh()
:m_gl_vertex_array(0), m_gl_vertex_buffer(0), m_gl_index_buffer(0)
{}


Mesh::~Mesh()
{
    //Vectors are RAII so no need to free them here

    glDeleteVertexArrays(1, &m_gl_vertex_array);
    glDeleteBuffers(1, &m_gl_vertex_buffer);
    glDeleteBuffers(1, &m_gl_index_buffer);
}

void Mesh::draw(Shader& shader)
{
    //Set up uniforms


    //For batch rendering this would be completely different but we probably won't do that until we get
    //text rendering going and stuff
    glBindVertexArray(m_gl_vertex_array);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);

}

bool Mesh::load(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    //Generate the mesh on GPU
    if(!gpu_gen_mesh(vertices, indices))
        return false;


    //If everything went well set member variables
    this->m_vertices = vertices;
    this->m_indices = indices;
    this->m_textures = textures;

    return true;
}

bool Mesh::gpu_gen_mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices)
{

    //Generate the buffers (no data assigned yet)
    glGenVertexArrays(1, &m_gl_vertex_array);
    glGenBuffers(1, &m_gl_vertex_buffer);
    glGenBuffers(1, &m_gl_index_buffer);

    glBindVertexArray(m_gl_vertex_array);

    glBindBuffer(GL_ARRAY_BUFFER, m_gl_vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_gl_index_buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);

    return true;
}