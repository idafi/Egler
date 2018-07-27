#include <SDL2/SDL.h>
#include "../Egler.Core/Core.hpp"
#include "../Egler.Core/Video/Video.hpp"

ConsoleLogger consoleLogger;
FileLogger fileLogger("log.txt");

int main(int argc, char **argv)
{
    Log::AddDefaultLogger(&fileLogger, LogLevel::Debug);
    Log::AddDefaultLogger(&consoleLogger, LogLevel::Debug);

    SDL_Init(SDL_INIT_VIDEO);

    const PixelRect windowRect(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
    GLContext *context = new GLContext("Egler", windowRect);

    while(!SDL_QuitRequested())
    {
        Vector4 color(0, 1, 1, 1);
        context->Window().Clear(color, 1);
        context->Window().Present();
        
        SDL_Delay(16);
    }

    delete context;
    SDL_Quit();

    Log::RemoveDefaultLogger(&fileLogger);
    Log::RemoveDefaultLogger(&consoleLogger);
    
    return 0;
}