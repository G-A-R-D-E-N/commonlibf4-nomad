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

		virtual void Unk_01() = 0;  // 01
		virtual void Unk_02() = 0;  // 02

		template <class T>
		void SetValue(const T& a_value);

		template <class T>
		[[nodiscard]] T GetValue() const;

		[[nodiscard]] BSFixedString& QChannelName();
		void                         PollChannelUpdate(const bool a_allowEventQueuesC);
		void                         Reset();

		BSFixedString channelName;  // 10
		std::uint32_t value;        // 18
	};
	static_assert(sizeof(BSAnimationGraphChannel) == 0x20);
}
