#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <graphics.h>

//Might be a bug initializing m_id to 0 because I think OpenGL uses 0 for something (might not tho)
Texture::Texture()
:m_id(0), m_width(0), m_height(0), m_channels(0)
{}

Texture::~Texture()
{
    glDeleteTextures(1, &m_id);
}

bool Texture::load(const std::string& filepath)
{
    int32_t width, height, channels;

    #if defined(GPU_FLIP_TEX)
    stbi_set_flip_vertically_on_load(true);
    #endif


    unsigned char* image = stbi_load(filepath.c_str(), &width, &height, &channels, 0);

    if(!image)
        return false;

    if(!gpu_gen_texture((const unsigned char*)image))
    {
        stbi_image_free(image);
        return false;
    }

    stbi_image_free(image);

    m_width = width;
    m_height = height;
    m_channels = channels;

    return true;
}

bool Texture::gpu_gen_texture(const unsigned char* texture)
{
    uint32_t id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    //TODO: Need to make this work for any file type (right now it just works for jpgs)
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, texture);
    glGenerateMipmap(GL_TEXTURE_2D);

    return true;
}

uint32_t Texture::get_id()
{
    return m_id;
}

uint32_t Texture::get_width()
{
    return m_width;
}

uint32_t Texture::get_height()
{
    return m_height;
}

uint32_t Texture::get_channel_count()
{
    return m_channels;
}