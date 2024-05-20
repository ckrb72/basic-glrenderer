#pragma once
#include <stdint.h>
#include <string>

class Texture
{
private:

    uint32_t m_id;
    int32_t m_width, m_height, m_channels;

    bool gpu_gen_texture(const unsigned char* texture);

public: 

    Texture();
    ~Texture();

    bool load(const std::string& filepath);

    uint32_t get_id();
    uint32_t get_width();
    uint32_t get_height();
    uint32_t get_channel_count();
};