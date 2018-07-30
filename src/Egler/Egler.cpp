#include "../Egler.Core/Core/Core.hpp"
#include "../Egler.Core/IO/IO.hpp"
#include "../Egler.Core/Logging/Logging.hpp"
#include "../Egler.Core/Video/Video.hpp"
#include "../Egler.FBX/FBXImporter.hpp"

#include "Egler.hpp"

using namespace Egler::Core;
using namespace Egler::Logging;
using namespace Egler::Video;

namespace Egler
{
    struct ModelBuffer
    {
        float VertexPositions[1204];
        float VertexColors[1024];
        ushort Indices[4096];
    };

    const char * const vertFile = "data/shader.vert";
    const char * const fragFile = "data/shader.frag";
    const char * const fbxFile = "data/hello.fbx";

    ConsoleLogger consoleLogger;
    FileLogger fileLogger("log.txt");

    FBXImporter fbxImporter;
    ModelBuffer modelBuffer;

    EglerContext *egler;
    EntityMan::Ptr entity;

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

        std::string vertStr = IO::ReadAllText(vertFile);
        std::string fragStr = IO::ReadAllText(fragFile);
        ShaderSourceFile vert(vertStr.c_str(), ShaderType::Vertex, vertFile);
        ShaderSourceFile frag(fragStr.c_str(), ShaderType::Fragment, fragFile);
        ShaderSourceFile files[] = { vert, frag };
        ShaderSource shaderSrc = ShaderSource(files, 2);

        ModelData modelData;
        modelData.VertexPositions = modelBuffer.VertexPositions;
        modelData.VertexColors = modelBuffer.VertexColors;
        modelData.Indices = modelBuffer.Indices;
        fbxImporter.ImportModel(fbxFile, &modelData);

        egler = new EglerContext(windowName, windowRect);
        
        auto model = egler->Models().Create(*egler, modelData);
        auto shader = egler->Shaders().Create(*egler, shaderSrc);
        auto material = egler->Materials().Create(*egler, shader);
        entity = egler->Entities().Create(*egler, model, material);
        
        Entity& ent = egler->Entities().Get(entity);
        ent.SetPosition(Vector3(0, 0, -20));
    }

    bool ShouldQuit()
    {
        return Core::ShouldQuit();
    }

    void Frame()
    {
        GLWindow& window = egler->Window();
        Vector4 color(0, 0, 0, 1);
        window.Clear(color, 1);

        egler->Entities().Update(*egler);

        egler->Window().Present();
        Core::Delay(16);
    }

    int Quit(const int code)
    {
        if(egler)
        { delete egler; }

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
        getchar();
    }

    return Egler::Quit(1);
}