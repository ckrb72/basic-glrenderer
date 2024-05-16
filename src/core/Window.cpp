#include "Window.h"
#include <stdexcept>
#include <graphics.h>


Window::Window(const std::string& title, uint32_t width, uint32_t height)
{

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
        throw std::runtime_error("Failed to initalize SDL2!");

    m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    if(!m_window)
    {
        SDL_Quit();
        throw std::runtime_error("Failed to Create Window: " + std::string(SDL_GetError()));
    }

    //Set OpenGL Version and Profile
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_CreateContext(m_window);

    //Load gl function pointers via glad if not on APPLE (don't know if need this on linux)
    #if !defined(__APPLE__)
    if(!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        throw std::runtime_error("Failed to inialize GLAD!");
    }
    #endif
}

Window::~Window()
{
    //Clean up window and SDL Context
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}



void Window::swap_buffers()
{
    SDL_GL_SwapWindow(m_window);
}