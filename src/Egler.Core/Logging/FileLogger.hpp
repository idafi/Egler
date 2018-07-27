#pragma once

#include <fstream>
#include "Logging.hpp"

// - - - - - -
// ILogger implementation targeting output file
// - - - - - -

class FileLogger : public ILogger
{
	public:
		FileLogger(const char * const filePath);
		~FileLogger();
		
		void Write(const LogLevel level, const char * const msg);
		
	private:
		std::ofstream file;
};