#pragma once

// - - - - - -
// describes Log message severity level
// - - - - - -

namespace Egler::Logging
{
	enum class LogLevel
	{
		Debug,
		Note,
		Warning,
		Error,
		Failure
	};
}