#pragma once
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <string>


//If we were doing OOP correclty (ew...) then we would
//probably have platform specific window classes derived from this class.
class Window
{
private:
    SDL_Window* m_window = nullptr;

    bool m_win_open = false;
    uint32_t m_width = 0;
    uint32_t m_height = 0;

public:

    Window(const std::string& title, uint32_t width, uint32_t height);

    ~Window();

    void clear();

    void swap_buffers();

    uint32_t get_width() const ;
    uint32_t get_height() const;

    inline SDL_Window* get_handle() const { return m_window; }
    inline void* get_sdl_context() const { return SDL_GLContext(); }
    inline bool is_closed() const { return !m_win_open; }
    void set_close(bool val);

    void set_cursor_pos(uint32_t x, uint32_t y);
    void set_cursor_relative(bool val);

};