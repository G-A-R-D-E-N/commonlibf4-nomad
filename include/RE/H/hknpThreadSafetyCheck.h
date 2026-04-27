#pragma once

#include "RE/H/hkBool.h"
#include "RE/H/hkCriticalSection.h"

namespace RE
{
	class hknpThreadSafetyCheck
	{
	public:
		class State
		{
		public:
			// members
			std::uint32_t numReaders: 5;
			std::uint32_t numWriters: 3;
			std::uint32_t writerThreadId: 24;
		};
		static_assert(sizeof(State) == 0x04);

		// members
		State             state;            // 0x00
		hkCriticalSection criticalSection;  // 0x08
		hkBool            enabled;          // 0x30
	};
	static_assert(sizeof(hknpThreadSafetyCheck) == 0x38);
}
