#include "SpriteSheet.h"
#include <graphics.h>
#include <iostream>

#define TEXTURE_BUFFER_SIZE 32

SpriteSheet::SpriteSheet()
{

    float vertices[] = 
    {
        -0.5, -0.5, 0.0,
        0.5, -0.5, 0.0,
        0.5, 0.5, 0.0,
        -0.5, 0.5, 0.0
    };

    unsigned int indices[] = 
    {
        0, 1, 2,
        2, 3, 0
    };

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);
    glGenBuffers(1, &m_tex_buff);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, m_tex_buff);
    glBufferData(GL_ARRAY_BUFFER, TEXTURE_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


SpriteSheet::~SpriteSheet()
{
    glDeleteBuffers(1, &m_vbo);
    glDeleteBuffers(1, &m_ebo);
    glDeleteBuffers(1, &m_tex_buff);
    glDeleteVertexArrays(1, &m_vao);
}

bool SpriteSheet::load(const std::string& filepath)
{
    //Load spritesheet texture
    if(!m_sheet.load(filepath))
    {
        return false;
    }


    m_width = m_sheet.get_width();
    m_height = m_sheet.get_height();

    m_x = 0;
    m_y = 0;


    return true;

}

//Sets the size of each clip (can be changed per frame)
void SpriteSheet::set_size(uint32_t width, uint32_t height)
{
    m_width = width;
    m_height = height;
}

//Sets the position of the clip (has width that was previously set)
void SpriteSheet::set_clip(uint32_t x, uint32_t y)
{
    m_x = x;
    m_y = y;
}

void SpriteSheet::draw()
{

    float sheet_width = (float)m_sheet.get_width();
    float sheet_height = (float)m_sheet.get_height();

    //Create texture coordinates
    float tex_coords[] =
    {
        (float)m_x / sheet_width, (float)m_y / sheet_height,
        (float)(m_x + m_width) / sheet_width, (float)m_y / sheet_height,
        (float)(m_x + m_width) / sheet_width, (float)(m_y + m_height) / sheet_height,
        (float)m_x / sheet_width, (float)(m_y + m_height) / sheet_height
    };

    //Send data over to tex_coords buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_tex_buff);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(tex_coords), tex_coords);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_sheet.get_id());

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
    glBindVertexArray(0);
}