#pragma once

#include <SDL2/SDL.h>
#include "../Common.hpp"

#include "Console.hpp"
#include "Matrix.hpp"
#include "Vector.hpp"
#include "Quaternion.hpp"
#include "Pool.hpp"

namespace Egler::Core
{
    #define SDLException(msg, ...) \
        FailureException(msg "\n\tSDL error: %s", ##__VA_ARGS__, SDL_GetError())
    
    void EGAPI Init();
    bool EGAPI ShouldQuit();
    void EGAPI Quit();

    void EGAPI Delay(uint ms);
}