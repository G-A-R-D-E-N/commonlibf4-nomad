#pragma once

#include "RE/B/BSAnimationGraphChannel.h"

namespace RE
{
	class Actor;
	class ActorWardHealthChannel;

	template <class T, class ValueType, class ChannelImpl>
	class BSTAnimationGraphDataChannel :
		public BSAnimationGraphChannel  // 00
	{
	public:
		T* owner;  // 20
	};

	template <>
	class BSTAnimationGraphDataChannel<Actor, float, ActorWardHealthChannel> :
		public BSAnimationGraphChannel  // 00
	{
	public:
		static constexpr auto VTABLE{ VTABLE::BSTAnimationGraphDataChannel_Actor_float_ActorWardHealthChannel };

		~BSTAnimationGraphDataChannel() override;  // 00

		Actor* owner;  // 20
	};
	static_assert(sizeof(BSTAnimationGraphDataChannel<Actor, float, ActorWardHealthChannel>) == 0x28);
}
