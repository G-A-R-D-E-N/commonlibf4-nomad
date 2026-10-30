#pragma once

#include "RE/C/CombatStyleCloseRangeData.h"
#include "RE/C/CombatStyleCoverData.h"
#include "RE/C/CombatStyleFlightData.h"
#include "RE/C/CombatStyleGeneralData.h"
#include "RE/C/CombatStyleLongRangeData.h"
#include "RE/C/CombatStyleMeleeData.h"
#include "RE/C/CombatStyleRangedData.h"
#include "RE/T/TESForm.h"

namespace RE
{
	class __declspec(novtable) TESCombatStyle :
		public TESForm  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESCombatStyle };
		static constexpr auto VTABLE{ VTABLE::TESCombatStyle };
		static constexpr auto FORM_ID{ ENUM_FORM_ID::kCSTY };
		static constexpr auto TYPE_ID{ BSScript::kCombatStyle };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kAllowDualWielding = 1 << 19
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class FLAG : std::uint32_t
		{
			kDuelingStyle = 0x1,
			kFlankingStyle = 0x2,
			kAllowDualWeilding = 0x4,
			kChargingStyle = 0x8,
			kAllowMeleeRetarget = 0x10
		};

		// members
		CombatStyleGeneralData    generalData;     // 20
		CombatStyleMeleeData      meleeData;       // 50
		CombatStyleRangedData     rangedData;      // 78
		CombatStyleCloseRangeData closeRangeData;  // 7C
		CombatStyleLongRangeData  longRangeData;   // A8
		CombatStyleCoverData      coverData;       // BC
		CombatStyleFlightData     flightData;      // C0
		FLAG                      flags;           // E0
	};
	static_assert(sizeof(TESCombatStyle) == 0xE8);
}
