#pragma once

#include "RE/M/MARKER_TYPE.h"
#include "RE/T/TESFullName.h"

namespace RE
{
	class __declspec(novtable) MapMarkerData :
		public TESFullName  // 00
	{
	public:
		enum class Flag : std::uint8_t
		{
			kNone = 0,
			kVisible = 1 << 0,
			kCanTravelTo = 1 << 1,
			kHidden = 1 << 2,
			kUseLocationName = 1 << 3
		};

		const char* GetLocationName()
		{
			using func_t = decltype(&MapMarkerData::GetLocationName);
			static REL::Relocation<func_t> func{ ID::MapMarkerData::GetLocationName };
			return func(this);
		}

		[[nodiscard]] bool GetVisible() const
		{
			using func_t = decltype(&MapMarkerData::GetVisible);
			static REL::Relocation<func_t> func{ ID::MapMarkerData::GetVisible };
			return func(this);
		}

		void SetVisible(bool a_visible)
		{
			using func_t = decltype(&MapMarkerData::SetVisible);
			static REL::Relocation<func_t> func{ ID::MapMarkerData::SetVisible };
			return func(this, a_visible);
		}

		[[nodiscard]] bool GetTravelLoc() const
		{
			using func_t = decltype(&MapMarkerData::GetTravelLoc);
			static REL::Relocation<func_t> func{ ID::MapMarkerData::GetTravelLoc };
			return func(this);
		}

		void SetTravelLoc(bool a_travelLoc)
		{
			using func_t = decltype(&MapMarkerData::SetTravelLoc);
			static REL::Relocation<func_t> func{ ID::MapMarkerData::SetTravelLoc };
			return func(this, a_travelLoc);
		}

		[[nodiscard]] bool GetHidden() const
		{
			using func_t = decltype(&MapMarkerData::GetHidden);
			static REL::Relocation<func_t> func{ ID::MapMarkerData::GetHidden };
			return func(this);
		}

		void SetHidden(bool a_hidden)
		{
			using func_t = decltype(&MapMarkerData::SetHidden);
			static REL::Relocation<func_t> func{ ID::MapMarkerData::SetHidden };
			return func(this, a_hidden);
		}

		[[nodiscard]] MARKER_TYPE GetMarkerType() const
		{
			using func_t = decltype(&MapMarkerData::GetMarkerType);
			static REL::Relocation<func_t> func{ ID::MapMarkerData::GetMarkerType };
			return func(this);
		}

		void SetMarkerType(MARKER_TYPE a_type)
		{
			using func_t = decltype(&MapMarkerData::SetMarkerType);
			static REL::Relocation<func_t> func{ ID::MapMarkerData::SetMarkerType };
			return func(this, a_type);
		}

		void ResetFlags() noexcept { flags = originalFlags; }

		[[nodiscard]] bool IsVisible() const noexcept { return GetVisible(); }
		[[nodiscard]] bool IsHidden() const noexcept { return GetHidden(); }
		[[nodiscard]] bool CanTravelTo() const noexcept { return GetTravelLoc(); }

		[[nodiscard]] bool IsDiscovered() const { return GetVisible() && !GetHidden(); }

		// members
		REX::TEnumSet<Flag, std::uint8_t>         flags;          // 10
		REX::TEnumSet<Flag, std::uint8_t>         originalFlags;  // 11
		REX::TEnumSet<MARKER_TYPE, std::uint16_t> type;           // 12
	};
	static_assert(sizeof(MapMarkerData) == 0x18);
	static_assert(offsetof(MapMarkerData, type) == 0x12);
}
