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

		REFRSyncController() { ctor(); }

		void Add(TESObjectREFR* a_ref, NiAVObject* a_target)
		{
			using func_t = decltype(&REFRSyncController::Add);
			static REL::Relocation<func_t> func{ ID::REFRSyncController::Add };
			func(this, a_ref, a_target);
		}

		void Update(float a_delta)
		{
			using func_t = decltype(&REFRSyncController::Update);
			static REL::Relocation<func_t> func{ ID::REFRSyncController::Update };
			func(this, a_delta);
		}

	private:
		REFRSyncController* ctor()
		{
			using func_t = decltype(&REFRSyncController::ctor);
			static REL::Relocation<func_t> func{ ID::REFRSyncController::ctor };
			return func(this);
		}
	};
}
