#pragma once

namespace RE
{
	class BGSAppPausedEvent
	{
	public:
		// members
		bool paused;  // 00
	};
	static_assert(sizeof(BGSAppPausedEvent) == 0x1);
}
