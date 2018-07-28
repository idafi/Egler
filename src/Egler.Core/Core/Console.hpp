#pragma once

#include "Core.hpp"

// - - - - - -
// platform-independent console interface
// - - - - - -

namespace Egler::Core
{
	enum class ConsoleColor
	{
		Black,
		Grey,
		White,
		Red,
		Yellow
	};

	class Console
	{
		public:
			Console();
			~Console();
			
			void SetColor(ConsoleColor foreground, ConsoleColor background);
			void Print(const char * const msg);
			
		private:
			FILE *dummy;
			
			ushort GetForegroundColor(ConsoleColor color);
			ushort GetBackgroundColor(ConsoleColor color);
	};
}