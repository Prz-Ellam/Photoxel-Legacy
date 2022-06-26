#pragma once
#ifndef _PHOTOXEL_LOG_H_
#define _PHOTOXEL_LOG_H_

#include <string_view>
#include <stdint.h>
#include <fstream>
#include <iostream>
#include <source_location>
#include <mutex>

#define FILENAME(filename) (strrchr(filename, '\\') ? strrchr(filename, '\\') + 1 : filename)

namespace Photoxel
{
	enum class Priority : uint8_t
	{
		Trace = 0,
		Debug = 1,
		Info = 2,
		Warning = 3,
		Error = 4,
		Critical = 5
	};

	enum PriorityColour
	{
		ResetColour = 0,
		TraceColour = 37,
		DebugColour = 36,
		InfoColour = 32,
		WarningColour = 93,
		ErrorColour = 33,
		CriticalColour = 31,
	};

	std::ostream& operator<<(std::ostream& os, const PriorityColour& color);

#define PX_TRACE(message, ...)		Photoxel::Log::Trace(std::source_location::current(), message, __VA_ARGS__);
#define PX_DEBUG(message, ...)		Photoxel::Log::Debug(std::source_location::current(), message, __VA_ARGS__);
#define PX_INFO(message, ...)		Photoxel::Log::Info(std::source_location::current(), message, __VA_ARGS__);
#define PX_WARNING(message, ...)	Photoxel::Log::Warning(std::source_location::current(), message, __VA_ARGS__);
#define PX_ERROR(message, ...)		Photoxel::Log::Error(std::source_location::current(), message, __VA_ARGS__);
#define PX_CRITICAL(message, ...)	Photoxel::Log::Critical(std::source_location::current(), message, __VA_ARGS__);

	struct PriorityData
	{
		std::string Label;
		PriorityColour Colour;
	};

	class Log
	{
	public:
		static void SetPriotity(const Priority& priotity);
		static void StartFileOutput(const std::string& filepath);
		static void FinishFileOutput();

		template<typename ...Args>
		static void Trace(const std::source_location& location, const std::string_view message, Args&&... args);

		template<typename ...Args>
		static void Debug(const std::source_location& location, const std::string_view message, Args&&... args);

		template<typename ...Args>
		static void Info(const std::source_location& location, const std::string_view message, Args&&... args);

		template<typename ...Args>
		static void Warning(const std::source_location& location, const std::string_view message, Args&&... args);

		template<typename ...Args>
		static void Error(const std::source_location& location, const std::string_view message, Args&&... args);

		template<typename ...Args>
		static void Critical(const std::source_location& location, const std::string_view message, Args&&... args);
	private:
		static void GetLogDate();
		static PriorityData GetPriorityData(const Priority& priority);

		template<typename ...Args>
		static void Write(const std::source_location& location, const PriorityData& data, const std::string_view message, Args&&... args);

		static Priority s_Priority;
		static std::mutex s_Mutex;
		static std::ofstream s_FileOutput;
		static std::tm s_TimeInfo;
	};

	template<typename ...Args>
	inline void Log::Trace(const std::source_location& location, const std::string_view message, Args&&... args)
	{
		if (s_Priority >= Priority::Trace) return;
		Write(location, GetPriorityData(Priority::Trace), message, args...);
	}

	template<typename ...Args>
	inline void Log::Debug(const std::source_location& location, const std::string_view message, Args&&... args)
	{
		if (s_Priority >= Priority::Debug) return;
		Write(location, GetPriorityData(Priority::Debug), message, args...);
	}

	template<typename ...Args>
	inline void Log::Info(const std::source_location& location, const std::string_view message, Args&&... args)
	{
		if (s_Priority >= Priority::Info) return;
		Write(location, GetPriorityData(Priority::Info), message, args...);
	}

	template<typename ...Args>
	inline void Log::Warning(const std::source_location& location, const std::string_view message, Args&& ...args)
	{
		if (s_Priority >= Priority::Warning) return;
		Write(location, GetPriorityData(Priority::Warning), message, args...);
	}

	template<typename ...Args>
	inline void Log::Error(const std::source_location& location, const std::string_view message, Args&& ...args)
	{
		if (s_Priority >= Priority::Error) return;
		Write(location, GetPriorityData(Priority::Error), message, args...);
	}

	template<typename ...Args>
	inline void Log::Critical(const std::source_location& location, const std::string_view message, Args&& ...args)
	{
		if (s_Priority >= Priority::Critical) return;
		Write(location, GetPriorityData(Priority::Critical), message, args...);
	}

	template<typename ...Args>
	inline void Log::Write(const std::source_location& location, const PriorityData& data, const std::string_view message, Args&& ...args)
	{
		std::scoped_lock guard(s_Mutex);
		GetLogDate();
		std::cout << data.Colour << std::setw(12) << std::setfill(' ') << std::left << data.Label;
		std::cout << std::put_time(&s_TimeInfo, "[%a %b %d %H:%M:%S %Y]\t");
		std::cout << FILENAME(location.file_name()) << "(" << location.line() << ":" << location.column() << ") '" << location.function_name() << "'\t";
		std::cout << std::vformat(message, std::make_format_args(args...));
		std::cout << ResetColour << '\n';
		if (s_FileOutput.is_open())
		{
			s_FileOutput << std::setw(12) << std::setfill(' ') << std::left << data.Label;
			s_FileOutput << std::put_time(&s_TimeInfo, "[%a %b %d %H:%M:%S %Y]\t");
			s_FileOutput << FILENAME(location.file_name()) << "(" << location.line() << ":" << location.column() << ") '" << location.function_name() << "'\t";
			s_FileOutput << std::vformat(message, std::make_format_args(args...));
			s_FileOutput << '\n';
		}
	}
}

#endif