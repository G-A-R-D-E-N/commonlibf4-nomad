#pragma once

#include "RE/N/NiTransform.h"

namespace RE
{
	class NiAVObject;
	class TESObjectREFR;

	class TESObjectREFRSync
	{
	public:
		static void Add(TESObjectREFR* a_ref, TESObjectREFR* a_target, NiAVObject* a_node, const NiTransform& a_offset, bool a_findCollision)
		{
			using func_t = decltype(&TESObjectREFRSync::Add);
			static REL::Relocation<func_t> func{ ID::TESObjectREFRSync::Add };
			func(a_ref, a_target, a_node, a_offset, a_findCollision);
		}
	};
}
