#pragma once

namespace RE
{
	class hkStopwatch
	{
	public:
		hkStopwatch() = default;

		// members
		std::int64_t ticksAtStart{ 0 };     // 0x00
		std::int64_t ticksTotal{ 0 };       // 0x08
		std::int64_t ticksAtSplit{ 0 };     // 0x10
		std::int64_t splitTotal{ 0 };       // 0x18
		hkBool       runningFlag{ false };  // 0x20
		std::int32_t numTimings{ 0 };       // 0x24
		const char*  name{ nullptr };       // 0x28
	};
	static_assert(sizeof(hkStopwatch) == 0x30);
}
