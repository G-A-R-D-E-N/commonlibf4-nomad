#include "RE/N/NiTransform.h"

namespace RE
{
	void NiTransform::InvertNonUniform(NiTransform& a_result) const
	{
		using func_t = void (*)(const NiTransform*, NiTransform&);
		static REL::Relocation<func_t> func{ ID::NiTransform::InvertNonUniform };
		return func(this, a_result);
	}

	NiTransform NiTransform::WorldToLocal(const NiTransform& a_parentWorld) const
	{
		NiTransform parentInverse;
		a_parentWorld.InvertNonUniform(parentInverse);
		return parentInverse * *this;
	}
}
