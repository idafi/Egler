#include "Video.hpp"

GLContext::GLContext(const char * const windowName, const PixelRect& windowDim)
{
    window = new GLWindow(windowName, windowDim);
    models = new ModelPool();
}

GLContext::~GLContext()
{
    delete models;
    delete window;
}

GLWindow& GLContext::Window()
{
    return *window;
}

ModelPool& GLContext::Models()
{
    return *models;
}

bool GLContext::IsCurrent()
{
    return window->IsCurrent();
}

void GLContext::MakeCurrent()
{
    window->MakeCurrent();
}