#pragma once

#include "RE/N/NiTransform.h"

namespace RE
{
	class NiAVObject;
	class TESObjectREFR;

	class TESObjectREFRSync
	{
	public:
		static void Add(TESObjectREFR* a_ref, TESObjectREFR* a_target, NiAVObject* a_node, const NiTransform& a_offset, bool a_findCollision);
	};
}
