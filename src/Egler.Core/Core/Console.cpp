#if defined(_WIN64) || defined(_WIN32)

#include <cstdio>
#include <stdexcept>
#include <windows.h>
#include "Core.hpp"

namespace Egler::Core
{
	ushort Console::GetForegroundColor(ConsoleColor color)
	{
		switch(color)
		{
			case ConsoleColor::Black:
				return 0;
			case ConsoleColor::Grey:
				return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
			case ConsoleColor::White:
				return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
			case ConsoleColor::Red:
				return FOREGROUND_RED | FOREGROUND_INTENSITY;
			case ConsoleColor::Yellow:
				return FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
		}
		
		return 0;
	}

	ushort Console::GetBackgroundColor(ConsoleColor color)
	{
		switch(color)
		{
			case ConsoleColor::Black:
				return 0;
			case ConsoleColor::Grey:
				return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
			case ConsoleColor::White:
				return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_INTENSITY;
			case ConsoleColor::Red:
				return BACKGROUND_RED | BACKGROUND_INTENSITY;
			case ConsoleColor::Yellow:
				return BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		}
		
		return 0;
	}

	Console::Console()
	{
		int result = AllocConsole();
		if(result == 0)
		{ throw FailureException("Failed to allocate Windows console."); }
		
		// we need an extant but otherwised-unused file to satisfy freopen_s
		freopen_s(&dummy, "CONIN$", "r", stdin);
		freopen_s(&dummy, "CONOUT$", "w", stdout);
		freopen_s(&dummy, "CONOUT$", "w", stderr);
	}

	Console::~Console()
	{
		fclose(dummy);
		FreeConsole();
	}

	void Console::SetColor(ConsoleColor foreground, ConsoleColor background)
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		WORD color = GetForegroundColor(foreground) | GetBackgroundColor(background);
		
		SetConsoleTextAttribute(hConsole, color);
	}

	void Console::Print(const char * const msg)
	{
		CheckPtr(msg);
		
		// we could write directly... or we could make it easy and printf.
		printf("%s", msg);
	}
	#endif
}