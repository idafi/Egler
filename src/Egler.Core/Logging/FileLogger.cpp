#include "FileLogger.hpp"

FileLogger::FileLogger(const char * const filePath)
{
	assert(filePath);
	
	file.open(filePath);
}

FileLogger::~FileLogger()
{
	file.close();
}

void FileLogger::Write(LogLevel level, const char * const msg)
{
	assert(msg);
	
	file << msg;
}