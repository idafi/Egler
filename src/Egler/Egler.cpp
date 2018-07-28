#include "../Egler.Core/Core/Core.hpp"
#include "../Egler.Core/Logging/Logging.hpp"
#include "../Egler.Core/Video/Video.hpp"

using namespace Egler::Core;
using namespace Egler::Logging;
using namespace Egler::Video;

namespace Egler
{
    ConsoleLogger consoleLogger;
    FileLogger fileLogger("log.txt");
    GLContext *context;

    void Init()
    {
        Log::AddDefaultLogger(&fileLogger, LogLevel::Debug);
        Log::AddDefaultLogger(&consoleLogger, LogLevel::Debug);
        LogNote("Logs initialized.");

        LogNote("Initializing SDL...");

        if(SDL_Init(SDL_INIT_VIDEO) < 0)
        { throw SDLException("SDL failed to initialize."); }

        LogNote("...done.");

        const PixelRect windowRect(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480);
        context = new GLContext("Egler", windowRect);
    }

    bool ShouldQuit()
    {
        return SDL_QuitRequested();
    }

    void Frame()
    {
        Vector4 color(0, 1, 1, 1);
        context->Window().Clear(color, 1);
        context->Window().Present();
        
        SDL_Delay(16);
    }

    int Quit(const int code)
    {
        if(context)
        { delete context; }

        LogNote("Shutting down SDL...");
        SDL_Quit();
        LogNote("...done.");

        LogNote("Flushing and shutting down logs.");
        Log::FlushDefault();
        Log::RemoveDefaultLogger(&fileLogger);
        Log::RemoveDefaultLogger(&consoleLogger);

        return code;
    }
}

int main(int argc, char **argv)
{
    try
    {
        Egler::Init();

        while(!Egler::ShouldQuit())
        { Egler::Frame(); }

        return Egler::Quit(0);
    }
    catch(const Egler::EglerException& e)
    {
        LogFailure(e.what());
        LogFailure("Press Enter to exit...");
        getchar();
    }

    return Egler::Quit(1);
}