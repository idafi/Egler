#include <SDL2/SDL.h>
#include "../Egler.Core/Common.hpp"

int main(int argc, char **argv)
{
    ConsoleLogger *logger = new ConsoleLogger();
    Log::AddDefaultLogger(logger, LogLevel::Debug);

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window = SDL_CreateWindow("Egler",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480,
        SDL_RENDERER_PRESENTVSYNC
    );

    LogNote("hello !!");

    while(!SDL_QuitRequested())
    { SDL_Delay(16); }

    SDL_DestroyWindow(window);
    SDL_Quit();

    Log::RemoveDefaultLogger(logger);
    delete logger;
    
    return 0;
}