#pragma once

#include "Logging.hpp"

// - - - - - -
// ILogger implementation targeting program console
// - - - - - -

class ConsoleLogger : public ILogger
{
	public:
		ConsoleLogger();
		~ConsoleLogger();
		
		void Write(const LogLevel level, const char * const msg);
		
	private:
		Console *console;
		void SetLevelColor(const LogLevel level);
};