#pragma once

#include "RE/N/NiTimeController.h"
#include "RE/N/NiTransform.h"

namespace RE
{
	class __declspec(novtable) REFRSyncController :
		public NiTimeController  // 0x00
	{
	public:
		static constexpr auto RTTI{ RTTI::TESObjectREFRSync__REFRSyncController };
		static constexpr auto VTABLE{ VTABLE::TESObjectREFRSync__REFRSyncController };
		static constexpr auto Ni_RTTI{ Ni_RTTI::REFRSyncController };

		void Update(float a_delta)
		{
			using func_t = decltype(&REFRSyncController::Update);
			static REL::Relocation<func_t> func{ ID::REFRSyncController::Update };
			func(this, a_delta);
		}
	};
}
