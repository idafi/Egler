#include <ctime>
#include <cstdarg>
#include <chrono>

#include "Log.hpp"

Log Log::defaultLog;

void Log::AddDefaultLogger(ILogger * const logger, const LogLevel minLevel)
{
	CheckPtr(logger);
	defaultLog.AddLogger(logger, minLevel);
}

void Log::RemoveDefaultLogger(ILogger * const logger)
{
	if(logger)
	{ defaultLog.RemoveLogger(logger); }
}

void Log::ChangeDefaultMinLevel(ILogger * const logger, const LogLevel minLevel)
{
	CheckPtr(logger);
	defaultLog.ChangeMinLevel(logger, minLevel);
}

void Log::WriteToDefault(const LogLevel level, char const * const msg, ...)
{
	CheckPtr(msg);

	va_list args;
	va_start(args, msg);
	defaultLog.Write(level, msg, args);
	va_end(args);
}

void Log::AddLogger(ILogger * const logger, const LogLevel minLevel)
{
	CheckPtr(logger);
	loggers[logger] = minLevel;
}

void Log::RemoveLogger(ILogger * const logger)
{
	if(logger)
	{ loggers.erase(logger); }
}

void Log::ChangeMinLevel(ILogger * const logger, const LogLevel minLevel)
{
	CheckPtr(logger);
	
	if(loggers.find(logger) != loggers.end())
	{ loggers[logger] = minLevel; }
	else
	{ LogWarning("couldn't change min level of logger: logger isn't yet registered"); }
}

void Log::Write(const LogLevel level, char const * const msg, ...)
{
	CheckPtr(msg);
	
	va_list args;
	va_start(args, msg);
	Write(level, msg, args);
	va_end(args);
}

void Log::GetTimestamp(char *buffer)
{
	using namespace std::chrono;
	
	time_point<system_clock> tp = system_clock::now();
	milliseconds ms = duration_cast<milliseconds>(tp.time_since_epoch());
	uint msRem = ms.count() % 1000;

	time_t time = system_clock::to_time_t(tp);
	struct tm local;
	localtime_s(&local, &time);

	strftime(buffer, 9, "%H:%M:%S", &local);
	snprintf(buffer, 13, "%s.%03u", buffer, msRem);
}

void Log::Write(const LogLevel level, char const * const msg, va_list args)
{
	CheckPtr(msg);
	
	if(loggers.size() > 0)
	{
		char fmt[MAX_LOG_MSG];
		char out[MAX_LOG_MSG];

		vsnprintf(fmt, MAX_LOG_MSG, msg, args);
		GetTimestamp(out);
		snprintf(out, MAX_LOG_MSG, "%s: %s", out, fmt);

		for(auto pair : loggers)
		{
			LogLevel loggerMinLevel = loggers[pair.first];
			if(level >= loggerMinLevel)
			{ pair.first->Write(level, out); }
		}
	}
}