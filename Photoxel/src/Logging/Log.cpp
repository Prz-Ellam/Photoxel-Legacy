#include "fxpch.h"
#include "Log.h"
#include "../Core/Core.h"

namespace Photoxel
{
	std::ostream& operator<<(std::ostream& os, const PriorityColour& color)
	{
		os << "\033[" << static_cast<int>(color) << "m";
		return os;
	}

	Priority Log::s_Priority;
	std::mutex Log::s_Mutex;
	std::ofstream Log::s_FileOutput;
	std::tm Log::s_TimeInfo;

	void Log::SetPriotity(const Priority& priotity)
	{
		s_Priority = priotity;
	}

	void Log::StartFileOutput(const std::string& filepath)
	{
		s_FileOutput.open(filepath, std::ios::trunc);
	}

	void Log::FinishFileOutput()
	{
		s_FileOutput.close();
	}

	void Log::GetLogDate()
	{
		std::time_t timer = std::time(nullptr);
		localtime_s(&s_TimeInfo, &timer);
	}

	PriorityData Log::GetPriorityData(const Priority& priority)
	{
		switch (priority)
		{
			case Priority::Trace:		return { "[TRACE]", TraceColour };
			case Priority::Debug:		return { "[DEBUG]", DebugColour };
			case Priority::Info:		return { "[INFO]", InfoColour };
			case Priority::Warning:		return { "[WARNING]", WarningColour };
			case Priority::Error:		return { "[ERROR]", ErrorColour };
			case Priority::Critical:	return { "[CRITICAL]", CriticalColour };
		}

		PX_ASSERT(false, "Priority not support!")
		return {};
	}
}