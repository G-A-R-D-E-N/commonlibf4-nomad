#pragma once

#include "RE/N/NiTransform.h"

namespace RE
{
	class TESObjectREFR;

	class TESObjectREFRSync
	{
	public:
		static void Add(TESObjectREFR* a_ref, TESObjectREFR* a_target, const NiTransform& a_offset);
	};
}
