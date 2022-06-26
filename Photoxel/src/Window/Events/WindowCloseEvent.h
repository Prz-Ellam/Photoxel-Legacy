#pragma once
#ifndef _PHOTOXEL_WINDOW_CLOSE_EVENT_H_
#define _PHOTOXEL_WINDOW_CLOSE_EVENT_H_

namespace Photoxel
{
	class WindowCloseEvent
	{
	public:
		WindowCloseEvent() = default;
	private:
	};

	using WindowCloseEventFn = std::function<void(WindowCloseEvent)>;
}

#endif // _PHOTOXEL_WINDOW_CLOSE_EVENT_H_
