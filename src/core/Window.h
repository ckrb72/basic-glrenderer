#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <string>


//If we were doing OOP correclty (ew...) then we would
//probably have platform specific window classes derived from this class.
class Window
{
private:
    SDL_Window* m_window;

    bool open;

public:
    Window(const std::string& title, uint32_t width, uint32_t height);

    ~Window();

    void swap_buffers();

    
};