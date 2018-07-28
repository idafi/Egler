#pragma once

#include "Logging.hpp"

// - - - - - -
// ILogger implementation targeting program console
// - - - - - -

using namespace Egler::Core;

namespace Egler::Logging
{
	class ConsoleLogger : public ILogger
	{
		public:
			void Write(const LogLevel level, const char * const msg);
			
		private:
			Console console;
			void SetLevelColor(const LogLevel level);
	};
}