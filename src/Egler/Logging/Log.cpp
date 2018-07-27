#include <ctime>
#include <cstdarg>
#include <chrono>

#include "Log.hpp"

Log Log::defaultLog;

void Log::AddDefaultLogger(ILogger * const logger, const LogLevel minLevel)
{
	assert(logger);
	defaultLog.AddLogger(logger, minLevel);
}

void Log::RemoveDefaultLogger(ILogger * const logger)
{
	if(logger)
	{ defaultLog.RemoveLogger(logger); }
}

void Log::ChangeDefaultMinLevel(ILogger * const logger, const LogLevel minLevel)
{
	assert(logger);
	defaultLog.ChangeMinLevel(logger, minLevel);
}

void Log::WriteToDefault(const LogLevel level, char const * const msg, ...)
{
	assert(msg);

	va_list args;
	va_start(args, msg);
	defaultLog.Write(level, msg, args);
	va_end(args);
}

void Log::AddLogger(ILogger * const logger, const LogLevel minLevel)
{
	assert(logger);
	loggers[logger] = minLevel;
}

void Log::RemoveLogger(ILogger * const logger)
{
	if(logger)
	{ loggers.erase(logger); }
}

void Log::ChangeMinLevel(ILogger * const logger, const LogLevel minLevel)
{
	assert(logger);
	
	if(loggers.find(logger) != loggers.end())
	{ loggers[logger] = minLevel; }
	else
	{ LogWarning("couldn't change min level of logger: logger isn't yet registered"); }
}

void Log::Write(const LogLevel level, char const * const msg, ...)
{
	assert(msg);
	
	va_list args;
	va_start(args, msg);
	Write(level, msg, args);
	va_end(args);
}

std::string Log::GetTimestamp()
{
	using namespace std::chrono;
	
	time_point<system_clock> tp = system_clock::now();
	milliseconds ms = duration_cast<milliseconds>(tp.time_since_epoch());
	uint msRem = ms.count() % 1000;

	time_t time = system_clock::to_time_t(tp);
	struct tm local;
	localtime_s(&local, &time);
	
	char prefix[9];
	char out[13];
	strftime(prefix, 9, "%H:%M:%S", &local);
	snprintf(out, 13, "%s.%03u", prefix, msRem);

	return std::string(out);
}

void Log::Write(const LogLevel level, char const * const msg, va_list args)
{
	assert(msg);
	
	if(loggers.size() > 0)
	{
		std::string str = GetTimestamp();
		str += ": ";

		char fmtMsg[512];
		vsnprintf(fmtMsg, 512, msg, args);

		str += fmtMsg;

		for(auto pair : loggers)
		{
			LogLevel loggerMinLevel = loggers[pair.first];
			if(level >= loggerMinLevel)
			{ pair.first->Write(level, str.c_str()); }
		}
	}
}