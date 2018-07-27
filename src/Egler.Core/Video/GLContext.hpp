#pragma once

#include "Video.hpp"

class GLContext
{
    public:
        GLContext(const char * const windowName, const PixelRect& windowDim);
        ~GLContext();

        GLWindow& Window();
        ModelPool& Models();

        bool IsCurrent();
        void MakeCurrent();

    private:
        GLWindow *window;
        ModelPool *models;
};