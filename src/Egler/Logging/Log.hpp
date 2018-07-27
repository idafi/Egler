#pragma once

#include "Logging.hpp"

// - - - - - -
// multi-target logging system
// - - - - - -

class Log
{
	public:
		static Log& Default();
	
		void AddLogger(ILogger * const logger, const LogLevel minLevel);
		void RemoveLogger(ILogger * const logger);
		void ChangeMinLevel(ILogger * const logger, const LogLevel minLevel);
		
		void Write(LogLevel level, char const * const msg, ...);
		
	private:
		static Log defaultLog;
		std::map<ILogger * const, LogLevel> loggers;
		
		std::string GetTimestamp();
};

#define LogDebug(msg, ...) Log::Default().Write(LogLevel::Debug, msg "\n", ##__VA_ARGS__)
#define LogNote(msg, ...) Log::Default().Write(LogLevel::Note, msg "\n", ##__VA_ARGS__)
#define LogWarning(msg, ...) Log::Default().Write(LogLevel::Warning, msg "\n", ##__VA_ARGS__)
#define LogError(msg, ...) Log::Default().Write(LogLevel::Error, msg "\n", ##__VA_ARGS__)
#define LogFailure(msg, ...) Log::Default().Write(LogLevel::Failure, msg "\n", ##__VA_ARGS__)