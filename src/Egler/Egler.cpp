#include "../Egler.Core/Core/Core.hpp"
#include "../Egler.Core/IO/IO.hpp"
#include "../Egler.Core/Logging/Logging.hpp"
#include "../Egler.Core/Video/Video.hpp"
#include "Models.hpp"

using namespace Egler::Core;
using namespace Egler::Logging;
using namespace Egler::Video;

namespace Egler
{
    static constexpr float cameraFOV = 45;
    static constexpr float zNear = 1;
    static constexpr float zFar = 45;

    ConsoleLogger consoleLogger;
    FileLogger fileLogger("log.txt");

    GLContext *context;
    ModelPool::Ptr modelPtr;
    MaterialPool::Ptr materialPtr;

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

        std::string vertStr = IO::ReadAllText(vertFilename);
        std::string fragStr = IO::ReadAllText(fragFilename);
        
        ShaderSourceFile vert(vertStr.c_str(), ShaderType::Vertex, vertFilename);
        ShaderSourceFile frag(fragStr.c_str(), ShaderType::Fragment, fragFilename);
        ShaderSourceFile files[] = { vert, frag };
        ShaderSource shaders[] = { ShaderSource(files, 2) };

        GLContextData data(windowName, windowRect, shaders, 1);
        context = new GLContext(data);

        ModelData modelData;
        modelData.VertexPositions = modelVertices;
        modelData.VertexColors = modelColors;
        modelData.Indices = modelIndices;
        modelData.VertexCount = 8;
        modelData.IndexCount = 24;

        modelPtr = context->Models().Allocate(modelData);

        Shader& shader = context->GetShader(0);
        materialPtr = context->Materials().Allocate(shader);

        Matrix pspMatrix = Mat4::Perspective(cameraFOV, zNear, zFar);
        context->Materials()[materialPtr].SetProperty("perspectiveMatrix", pspMatrix);
    }

    bool ShouldQuit()
    {
        return Core::ShouldQuit();
    }

    void Frame()
    {
        Vector4 color(0, 0, 0, 1);
        context->Window().Clear(color, 1);

        Mat4 modelMatrix = Mat4::Identity();
        Model& model = context->Models()[modelPtr];
        Material& material = context->Materials()[materialPtr];

        modelMatrix.SetColumn(3, Vector4(0, 0, -20.0f, 1.0f));
        material.SetProperty("localToCameraMatrix", modelMatrix);

        context->Window().DrawModel(model, material);
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