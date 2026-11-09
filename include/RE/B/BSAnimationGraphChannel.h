#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	// vtable, both slots and the member offset +0x10 and +0x18 are verified on OG/NG/AE; the two virtual parameter types and the poll signatures are unverified
	class BSAnimationGraphChannel :
		public BSIntrusiveRefCounted
	{
	public:
		static constexpr auto RTTI{ RTTI::BSAnimationGraphChannel };
		static constexpr auto VTABLE{ VTABLE::BSAnimationGraphChannel };

		virtual ~BSAnimationGraphChannel();  // 00

		virtual void PollChannelUpdate(bool a_allowEventQueuesC) = 0;  // 01
		virtual void Reset() = 0;                                     // 02

		[[nodiscard]] BSFixedString& QChannelName() noexcept { return channelName; }

		BSFixedString channelName;  // 10
		std::uint32_t value;        // 18
	};
	static_assert(sizeof(BSAnimationGraphChannel) == 0x20);
}
