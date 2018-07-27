#pragma once

#include "Video.hpp"

class GLWindow
{
	public:
		GLWindow();
		GLWindow(const char * const name, const PixelRect& dimensions);
		~GLWindow();
		
		void Clear(const Vector4& color, const float depth);
		void Present();

		bool IsCurrent();
		void MakeCurrent();
	
	private:
		SDL_Window *window;
		SDL_GLContext context;
};