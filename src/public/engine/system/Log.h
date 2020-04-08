#pragma once

/*
#include <memory>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

class Log
{
public:
	static void Init();

	inline static std::shared_ptr<spdlog::logger>& GetLogger()
	{
		return s_logger;
	}

private:
	static std::shared_ptr<spdlog::logger> s_logger;
};

// Core Log Macros
#define ME_CORE_TRACE(...)	::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define ME_CORE_INFO(...)	::Log::GetCoreLogger()->info(__VA_ARGS__)
#define ME_CORE_WARN(...)	::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define ME_CORE_ERROR(...)	::Log::GetCoreLogger()->error(__VA_ARGS__)
#define ME_CORE_FATAL(...)	::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log Macros
#define ME_TRACE(...)		::Log::GetClientLogger()->trace(__VA_ARGS__)
#define ME_INFO(...)		::Log::GetClientLogger()->info(__VA_ARGS__)
#define ME_WARN(...)		::Log::GetClientLogger()->warn(__VA_ARGS__)
#define ME_ERROR(...)		::Log::GetClientLogger()->error(__VA_ARGS__)
#define ME_FATAL(...)		::Log::GetClientLogger()->fatal(__VA_ARGS__)
*/