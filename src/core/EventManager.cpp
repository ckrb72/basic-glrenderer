#include "EventManager.h"
#include <SDL2/SDL.h>

EventManager::EventManager()
{

}

EventManager::~EventManager()
{

}

void handle_events()
{
    SDL_Event event;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
            case SDL_QUIT:
                break;
            
            default: 
                break;
        }
    }
}