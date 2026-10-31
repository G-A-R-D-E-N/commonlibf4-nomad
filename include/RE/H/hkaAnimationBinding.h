#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkaAnimation;

	class __declspec(novtable) hkaAnimationBinding :
		public hkReferencedObject  // 0x10
	{
	public:
		enum class BlendHint : std::int8_t
		{
			kNormal = 0,
			kAdditiveDeprecated = 1,
			kAdditive = 2
		};

		virtual ~hkaAnimationBinding();  // 00

		// members
		const char*             originalSkeletonName;       // 0x10
		hkaAnimation*           animation;                  // 0x18
		hkArray<std::int16_t>   transformTrackToBoneIndices;  // 0x20
		hkArray<std::int16_t>   floatTrackToFloatSlotIndices; // 0x30
		hkArray<std::int16_t>   partitionIndices;           // 0x40
		BlendHint               blendHint;                  // 0x50
	};
	static_assert(sizeof(hkaAnimationBinding) == 0x58);
}
