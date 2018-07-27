#pragma once

#include "Logging.hpp"

// - - - - - -
// multi-target logging system
// - - - - - -

class Log
{
	public:
		static void AddDefaultLogger(ILogger * const logger, const LogLevel minLevel);
		static void RemoveDefaultLogger(ILogger * const logger);
		static void ChangeDefaultMinLevel(ILogger * const logger, const LogLevel minLevel);
		static void WriteToDefault(const LogLevel level, char const * const msg, ...);
	
		void AddLogger(ILogger * const logger, const LogLevel minLevel);
		void RemoveLogger(ILogger * const logger);
		void ChangeMinLevel(ILogger * const logger, const LogLevel minLevel);
		
		void Write(const LogLevel level, char const * const msg, ...);
		
	private:
		static Log defaultLog;
		std::map<ILogger * const, LogLevel> loggers;
		
		void GetTimestamp(char *buffer);
		void Write(const LogLevel level, char const * const msg, va_list args);
};

#define LogDebug(msg, ...) Log::WriteToDefault(LogLevel::Debug, msg "\n", ##__VA_ARGS__)
#define LogNote(msg, ...) Log::WriteToDefault(LogLevel::Note, msg "\n", ##__VA_ARGS__)
#define LogWarning(msg, ...) Log::WriteToDefault(LogLevel::Warning, msg "\n", ##__VA_ARGS__)
#define LogError(msg, ...) Log::WriteToDefault(LogLevel::Error, msg "\n", ##__VA_ARGS__)
#define LogFailure(msg, ...) Log::WriteToDefault(LogLevel::Failure, msg "\n", ##__VA_ARGS__)