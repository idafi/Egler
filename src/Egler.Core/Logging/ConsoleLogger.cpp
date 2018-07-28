#include "ConsoleLogger.hpp"

void ConsoleLogger::Write(const LogLevel level, const char * const msg)
{
	CheckPtr(msg);
	
	SetLevelColor(level);
	console.Print(msg);
}

void ConsoleLogger::SetLevelColor(const LogLevel level)
{
	switch(level)
	{
		case LogLevel::Debug:
			console.SetColor(ConsoleColor::Grey, ConsoleColor::Black);
			break;
		case LogLevel::Note:
			console.SetColor(ConsoleColor::White, ConsoleColor::Black);
			break;
		case LogLevel::Warning:
			console.SetColor(ConsoleColor::Yellow, ConsoleColor::Black);
			break;
		case LogLevel::Error:
			console.SetColor(ConsoleColor::Red, ConsoleColor::Black);
			break;
		case LogLevel::Failure:
			console.SetColor(ConsoleColor::Yellow, ConsoleColor::Red);
			break;
	}
}