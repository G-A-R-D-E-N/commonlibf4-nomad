#pragma once

namespace RE
{
	class ManualCountdownTimer
	{
	public:
		// members
		float timeRemaining;  // 00
		float duration;       // 04
		bool  active;         // 08
	};
	static_assert(sizeof(ManualCountdownTimer) == 0x0C);
}
