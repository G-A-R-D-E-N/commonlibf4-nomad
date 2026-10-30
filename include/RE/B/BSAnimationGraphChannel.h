#pragma once

#include "RE/B/BSFixedString.h"
#include "RE/B/BSIntrusiveRefCounted.h"

namespace RE
{
	// vtable address and the three slots are verified on OG/NG/AE; the two virtual parameter types are unverified
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
	};
}
