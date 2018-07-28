#include "Core.hpp"

namespace Egler::Core
{
    void Init()
    {
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        { throw SDLException("SDL failed to initialize."); }
    }

    bool ShouldQuit()
    {
        return SDL_QuitRequested();
    }

    void Quit()
    {
        SDL_Quit();
    }

    void Delay(uint ms)
    {
        SDL_Delay(ms);
    }
}