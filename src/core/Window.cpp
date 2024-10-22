#include "Window.h"
#include <stdexcept>
#include <graphics.h>
#include <iostream>


Window::Window(const std::string& title, uint32_t width, uint32_t height)
:m_width(width), m_height(height)
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

    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

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

    SDL_GL_SetSwapInterval(0);

    //Set up various OpenGL functionality
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_MULTISAMPLE);

    m_win_open = true;

    /*glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);*/
}

Window::~Window()
{
    //Clean up window and SDL Context
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}


void Window::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0.3, 0.3, 0.3, 1.0);
}



void Window::swap_buffers()
{
    SDL_GL_SwapWindow(m_window);
}

uint32_t Window::get_width() const
{
    return this->m_width;
}

uint32_t Window::get_height() const 
{
    return this->m_height;
}

void Window::set_cursor_pos(uint32_t x, uint32_t y)
{
    SDL_WarpMouseInWindow(m_window, x, y);
}

void Window::set_cursor_relative(bool val)
{
    if(val)
        SDL_SetRelativeMouseMode(SDL_TRUE);
    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}

void Window::set_close(bool val)
{
    m_win_open = !val;
}