#include "Mesh.h"
#include <graphics.h>

Mesh::Mesh()
:m_vertex_array(0), m_vertex_buffer(0), m_index_buffer(0)
{}


Mesh::~Mesh()
{
    //Vectors are RAII so no need to free them here

    glDeleteVertexArrays(1, &m_vertex_array);
    glDeleteBuffers(1, &m_vertex_buffer);
    glDeleteBuffers(1, &m_index_buffer);
}

void Mesh::draw(Shader& shader)
{
    //Set up uniforms


    //For batch rendering this would be completely different but we probably won't do that until we get
    //text rendering going and stuff
    glBindVertexArray(m_vertex_array);
    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, nullptr);

}

