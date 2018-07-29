#pragma once

#include "Video.hpp"

namespace Egler::Video
{
	class GLWindow
	{
		public:
			// SDL magic
			static constexpr uint Centered = SDL_WINDOWPOS_CENTERED;

			GLWindow();
			GLWindow(const char * const name, const PixelRect& dimensions);
			~GLWindow();
			
			void Clear(const Vector4& color, const float depth);
			void DrawModel(const Model& model, const Material& material);
			void Present();

			bool IsCurrent();
			void MakeCurrent();

			Vector2 Size();
		
		private:
			SDL_Window *window;
			SDL_GLContext context;
	};
}