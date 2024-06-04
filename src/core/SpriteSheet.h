#pragma once
#include <stdint.h>
#include <string>
#include "Texture.h"

class SpriteSheet
{

private:
    uint32_t m_vao, m_vbo, m_ebo;
    uint32_t m_tex_buff;

    uint32_t m_width, m_height;
    uint32_t m_x, m_y;

    Texture m_sheet;

public:
    SpriteSheet();

    ~SpriteSheet();

    bool load(const std::string& filpath);

    //Sets the size of each clip (can be changed per frame)
    //@param width width of clip
    //@param height height of clip
    void set_size(uint32_t width, uint32_t height);

    //Sets the position of the clip (has width that was previously set)
    //@param x x position of bottom right corner of clip
    //@param y y position of bottom right corner of clip
    void set_clip(uint32_t x, uint32_t y);

    void draw();

};