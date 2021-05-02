#include "log.h"

// Based on code found here: https://github.com/TheCherno/Hazel/blob/master/Hazel/src/Hazel/Core/Log.cpp

namespace PsAi
{

	std::shared_ptr<spdlog::logger> Log::s_logger;

	void Log::init()
	{
		spdlog::set_pattern("%^[%T] %n_%L: %v%$");
		s_logger = spdlog::stdout_color_mt("PSAI");
		spdlog::set_level(spdlog::level::trace);
	}

} // PsAi namespace