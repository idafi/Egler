#include "Video.hpp"

GLWindow::GLWindow()
: GLWindow("Egler", PixelRect(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480))
{
}

GLWindow::GLWindow(const char * const name, const PixelRect& dimensions)
{
	CheckPtr(name);
    CheckSign(dimensions.Width);
    CheckSign(dimensions.Height);

    window = SDL_CreateWindow(name,
        dimensions.X, dimensions.Y, dimensions.Width, dimensions.Height,
        SDL_WINDOW_OPENGL
    );

    if(!window)
    { throw SDLException("SDL window failed to initialize."); }

    context = SDL_GL_CreateContext(window);
    if(!context)
    { throw SDLException("SDL failed to create GL context."); }

    SDL_GL_MakeCurrent(window, context);

    GLenum glewErr = glewInit();
    if(glewErr != GLEW_OK)
    { throw GLEWException(glewErr, "GLEW failed to initialize."); }

    SDL_GL_SetSwapInterval(1);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LEQUAL);
    glDepthRange(0.0f, 1.0f);

    glViewport(0, 0, dimensions.Width, dimensions.Height);
}

GLWindow::~GLWindow()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
	
	context = nullptr;
	window = nullptr;
}

void GLWindow::Clear(const Vector4& color, const float depth)
{
	if(!IsCurrent())
    { throw NotInitializedException("GL window to clear is not of the current GL context (%i).", context); }
	
    glClearColor(color[0], color[1], color[2], color[3]);
    glClearDepth(depth);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLWindow::Present()
{
	if(!IsCurrent())
    { throw NotInitializedException("GL window to clear is not of the current GL context (%i).", context); }
	
    SDL_GL_SwapWindow(window);
}

void GLWindow::MakeCurrent()
{
	if(!IsCurrent())
	{ SDL_GL_MakeCurrent(window, context); }
}

bool GLWindow::IsCurrent()
{
	SDL_GLContext current = SDL_GL_GetCurrentContext();
	return (current != nullptr && current == context);
}