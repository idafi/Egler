#include <SDL2/SDL.h>
#include "../Egler.Core/Core.hpp"
#include "../Egler.Core/Video/Video.hpp"

int main(int argc, char **argv)
{
    ConsoleLogger *logger = new ConsoleLogger();
    FileLogger *file = new FileLogger("log.txt");
    Log::AddDefaultLogger(file, LogLevel::Debug);
    Log::AddDefaultLogger(logger, LogLevel::Debug);

    SDL_Init(SDL_INIT_VIDEO);

    PixelRect rect(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
    Window *window = new Window("Egler", rect);

    while(!SDL_QuitRequested())
    {
        Vector4 color(0, 1, 1, 1);
        window->Clear(color, 1);
        window->Present();
        
        SDL_Delay(16);
    }

    delete window;
    SDL_Quit();

    Log::RemoveDefaultLogger(file);
    Log::RemoveDefaultLogger(logger);
    delete file;
    delete logger;
    
    return 0;
}