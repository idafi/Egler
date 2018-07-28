#pragma once

#include "Logging.hpp"

// - - - - - -
// used by the Logger to log to multiple arbitrary output destinations
// - - - - - -

namespace Egler::Logging
{
	class ILogger
	{
		public:
			virtual ~ILogger() { }

			virtual void Write(LogLevel level, const char * const msg) = 0;
			virtual void Flush(){ }
	};
}