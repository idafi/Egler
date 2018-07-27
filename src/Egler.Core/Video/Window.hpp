#pragma once

#include "Video.hpp"

class Window
{
    public:
        Window(char const * const name, const PixelRect& dimensions);
        ~Window();

        void Clear(const Vector4& color, const float depth);
        void Present();

    private:
        SDL_Window *window;
        SDL_GLContext context;

        void EnsureCurrent();
};