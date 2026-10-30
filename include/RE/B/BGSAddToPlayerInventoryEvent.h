#pragma once

#include <type_traits>

#include "RE/B/BSPointerHandle.h"

namespace RE
{
	class BGSLocation;
	class TESForm;
	class TESObjectREFR;
	enum class ACQUIRE_TYPE : std::int32_t;

	class BGSAddToPlayerInventoryEvent
	{
	public:
		[[nodiscard]] static BGSAddToPlayerInventoryEvent Create(
			TESObjectREFR* a_ownerRef,
			BGSLocation*   a_location,
			TESObjectREFR* a_containerRef,
			TESForm*       a_baseItem,
			ACQUIRE_TYPE   a_acquireType,
			std::uint32_t  a_itemCount);

		[[nodiscard]] static std::uint32_t EVENT_INDEX()
		{
			static REL::Relocation<std::uint32_t*> eventIdx{ ID::BGSAddToPlayerInventoryEvent::EventIndex };
			return *eventIdx;
		}

		// members
		ObjectRefHandle          ownerRef{};           // 00
		ObjectRefHandle          containerRef{};       // 04
		BGSLocation*             location{ nullptr };  // 08
		TESForm*                 baseItem{ nullptr };  // 10
		REX::TEnum<ACQUIRE_TYPE> acquireType{};        // 18
		std::uint32_t            itemCount{ 0 };       // 1C
	};
	static_assert(std::is_aggregate_v<BGSAddToPlayerInventoryEvent>);
	static_assert(sizeof(BGSAddToPlayerInventoryEvent) == 0x20);
}
