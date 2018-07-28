#include <fstream>
#include <sstream>
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

        LogNote("Initializing Core...");
        Core::Init();
        LogNote("...done.");

        const char * const windowName = "Egler";
        const PixelRect windowRect(GLWindow::Centered, GLWindow::Centered, 640, 480);

        // build shaders
        const char * const vertFilename = "data/shader.vert";
        const char * const fragFilename = "data/shader.frag";

        std::ifstream vertFile(vertFilename);
        std::ifstream fragFile(fragFilename);
        std::stringstream buffer;

        buffer << vertFile.rdbuf();
        vertFile.close();

        std::string vertStr = buffer.str();
        buffer.str("");
        ShaderSourceFile vert(vertStr.c_str(), ShaderType::Vertex, vertFilename);

        buffer << fragFile.rdbuf();
        fragFile.close();

        std::string fragStr = buffer.str();
        buffer.str("");
        ShaderSourceFile frag(fragStr.c_str(), ShaderType::Fragment, fragFilename);

        ShaderSourceFile files[] = { vert, frag };
        ShaderSource shaders[] =  { ShaderSource(files, 2) };

        GLContextData data(windowName, windowRect, shaders, 1);
        context = new GLContext(data);
    }

    bool ShouldQuit()
    {
        return Core::ShouldQuit();
    }

    void Frame()
    {
        Vector4 color(0, 1, 1, 1);
        context->Window().Clear(color, 1);
        context->Window().Present();
        
        Core::Delay(16);
    }

    int Quit(const int code)
    {
        if(context)
        { delete context; }

        LogNote("Shutting down Core...");
        Core::Quit();
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