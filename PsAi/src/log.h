#pragma once

// Based on code found here: https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Log.h

// Third party includes
// SPDLOG
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace PsAi
{

	class Log
	{
		public:
			static void init();

			static std::shared_ptr<spdlog::logger>& GetLogger() { return s_logger; }
		private:
			static std::shared_ptr<spdlog::logger> s_logger;
	};

} // PsAi namespace

// Logger macros
#define PSAI_LOG_DEBUG(...) ::PsAi::Log::GetLogger()->debug(__VA_ARGS__)
#define PSAI_LOG_WARN(...) ::PsAi::Log::GetLogger()->warn(__VA_ARGS__)