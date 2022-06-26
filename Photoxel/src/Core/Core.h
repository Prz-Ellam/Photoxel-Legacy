#pragma once
#ifndef _PHOTOXEL_CORE_H_
#define _PHOTOXEL_CORE_H_

#include "Logging/Log.h"

#define PX_ASSERT(condition, message, ...)\
	if (!condition) {\
		Photoxel::Log::Error(std::source_location::current(), message, __VA_ARGS__);\
		__debugbreak();\
	}\

#define CREATE_WINDOW(...) std::make_shared<Photoxel::Win32Window>(__VA_ARGS__)

//#define EVENT_FN(function) [this](Fidela::WindowCloseEvent e) { CloseWindow(e); }

#endif // _PHOTOXEL_CORE_H_