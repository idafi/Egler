#pragma once

#include "Video.hpp"

namespace Egler::Video
{
    class GLContext
    {
        public:
            GLContext();
            GLContext(const char * const windowName, const PixelRect& windowDim);

            GLWindow& Window();
            ModelPool& Models();

            bool IsCurrent();
            void MakeCurrent();

        private:
            GLWindow window;
            ModelPool models;
    };
}