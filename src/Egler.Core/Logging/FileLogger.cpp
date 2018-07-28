#include "FileLogger.hpp"

FileLogger::FileLogger(const char * const filePath)
{
	CheckPtr(filePath);
	
	file.open(filePath);
}

FileLogger::~FileLogger()
{
	file.close();
}

void FileLogger::Write(LogLevel level, const char * const msg)
{
	CheckPtr(msg);
	
	file << msg;
}

void FileLogger::Flush()
{
	file.flush();
}