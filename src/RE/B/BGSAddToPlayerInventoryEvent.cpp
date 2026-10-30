#include "RE/B/BGSAddToPlayerInventoryEvent.h"

#include "RE/NativeControllerRuntime.h"
#include "RE/T/TESObjectREFR.h"

namespace RE
{
	BGSAddToPlayerInventoryEvent BGSAddToPlayerInventoryEvent::Create(
		TESObjectREFR* a_ownerRef,
		BGSLocation*   a_location,
		TESObjectREFR* a_containerRef,
		TESForm*       a_baseItem,
		ACQUIRE_TYPE   a_acquireType,
		std::uint32_t  a_itemCount)
	{
		BGSAddToPlayerInventoryEvent event{};
		if (!detail::IsSupportedNativeControllerRuntime()) {
			return event;
		}

		using func_t = BGSAddToPlayerInventoryEvent* (*)(BGSAddToPlayerInventoryEvent*, TESObjectREFR*, BGSLocation*, TESObjectREFR*, TESForm*, ACQUIRE_TYPE, std::uint32_t);
		static REL::Relocation<func_t> func{ ID::BGSAddToPlayerInventoryEvent::ctor };
		func(&event, a_ownerRef, a_location, a_containerRef, a_baseItem, a_acquireType, a_itemCount);
		return event;
	}
}
