#pragma once

#include "Logging.hpp"

// - - - - - -
// used by the Logger to log to multiple arbitrary output destinations
// - - - - - -

class ILogger
{
	public:
		virtual ~ILogger() { }		
		virtual void Write(LogLevel level, const char * const msg) = 0;
};