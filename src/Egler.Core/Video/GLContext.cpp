#include "Video.hpp"

GLContext::GLContext()
{
}

GLContext::GLContext(const char * const windowName, const PixelRect& windowDim)
: window(GLWindow(windowName, windowDim))
{
}

GLContext::~GLContext()
{
    models.~ModelPool();
    window.~GLWindow();
}

GLWindow& GLContext::Window()
{
    return window;
}

ModelPool& GLContext::Models()
{
    return models;
}

bool GLContext::IsCurrent()
{
    return window.IsCurrent();
}

void GLContext::MakeCurrent()
{
    window.MakeCurrent();
}