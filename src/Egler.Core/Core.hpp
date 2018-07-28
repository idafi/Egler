#pragma once

#include <SDL2/SDL.h>
#include "Common.hpp"

#include "Console.hpp"
#include "Logging/Logging.hpp"
#include "Pool.hpp"

#define SDLException(msg, ...) \
    FailureException(msg "\n\tSDL error: %s", ##__VA_ARGS__, SDL_GetError())