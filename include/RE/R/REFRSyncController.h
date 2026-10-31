#pragma once

#include "RE/N/NiTimeController.h"
#include "RE/N/NiTransform.h"

namespace RE
{
	class NiAVObject;
	class TESObjectREFR;

	class __declspec(novtable) REFRSyncController :
		public NiTimeController  // 0x00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectREFRSync__REFRSyncController };
		static constexpr auto VTABLE{ VTABLE::TESObjectREFRSync__REFRSyncController };
		static constexpr auto Ni_RTTI{ Ni_RTTI::REFRSyncController };

		REFRSyncController();

		void Add(TESObjectREFR* a_ref, NiAVObject* a_target);
		void Update(float a_delta);

		[[nodiscard]] TESObjectREFR* GetAVTarget() const;
	};
}
