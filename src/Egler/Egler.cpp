#include "../Egler.Core/Core/Core.hpp"
#include "../Egler.Core/IO/IO.hpp"
#include "../Egler.Core/Logging/Logging.hpp"
#include "../Egler.Core/Video/Video.hpp"
#include "../Egler.FBX/FBXImporter.hpp"
#include "Entity.hpp"

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

    static constexpr int maxEntities = 8;

    static constexpr float cameraFOV = 45;
    static constexpr float zNear = 1;
    static constexpr float zFar = 45;

    ConsoleLogger consoleLogger;
    FileLogger fileLogger("log.txt");

    FBXImporter fbxImporter;
    ModelBuffer modelBuffer;

    GLContext *context;
    Entity entities[maxEntities];
    int entityCount;

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
        ShaderSource shaders[] = { ShaderSource(files, 2) };

        GLContextData data(windowName, windowRect, shaders, 1);
        context = new GLContext(data);

        ModelData modelData;
        modelData.VertexPositions = modelBuffer.VertexPositions;
        modelData.VertexColors = modelBuffer.VertexColors;
        modelData.Indices = modelBuffer.Indices;

        fbxImporter.ImportModel(fbxFile, &modelData);
        Shader& shader = context->GetShader(0);

        entities[0].Model = context->Models().Allocate(modelData);
        entities[0].Material = context->Materials().Allocate(shader);
        entities[0].TRSMatrix = Mat4::Identity();
        entities[0].SetPosition(Vector3(0, 0, -20));
        entityCount++;
    }

    bool ShouldQuit()
    {
        return Core::ShouldQuit();
    }

    void Frame()
    {
        GLWindow& window = context->Window();
        Vector4 color(0, 0, 0, 1);
        window.Clear(color, 1);

        Vector2 windowSize = window.Size();
        float aspect = windowSize[0] / windowSize[1];
        Matrix pspMatrix = Mat4::Perspective(cameraFOV, zNear, zFar, aspect);

        const byte * const keys = SDL_GetKeyboardState(nullptr);

        for(int i = 0; i < entityCount; i++)
        {
            Entity& ent = entities[i];
            Model& model = context->Models()[ent.Model];
            Material& material = context->Materials()[ent.Material];

            Vector3 translate;
            if(keys[SDL_SCANCODE_RIGHT])
            { translate[0] += 0.1f; }
            if(keys[SDL_SCANCODE_LEFT])
            { translate[0] -= 0.1f; }
            if(keys[SDL_SCANCODE_UP])
            { translate[1] += 0.1f; }
            if(keys[SDL_SCANCODE_DOWN])
            { translate[1] -= 0.1f; }

            Vector3 scale = ent.GetScale();
            if(keys[SDL_SCANCODE_D])
            { scale[0] += 0.1f; }
            if(keys[SDL_SCANCODE_A])
            { scale[0] -= 0.1f; }
            if(keys[SDL_SCANCODE_W])
            { scale[1] += 0.1f; }
            if(keys[SDL_SCANCODE_S])
            { scale[1] -= 0.1f; }

            ent.Translate(translate.ClampMagnitude(0, 1));
            ent.SetScale(scale);

            material.SetProperty("perspectiveMatrix", pspMatrix);
            material.SetProperty("localToCameraMatrix", ent.TRSMatrix);
            context->Window().DrawModel(model, material);
        }

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
    //try
    //{
        Egler::Init();

        while(!Egler::ShouldQuit())
        { Egler::Frame(); }

        return Egler::Quit(0);
    //}
    //catch(const Egler::EglerException& e)
    //
      //  LogFailure(e.what());
       // LogFailure("Press Enter to exit...");
       // getchar();
       // getchar();
    //}

    //return Egler::Quit(1);
}