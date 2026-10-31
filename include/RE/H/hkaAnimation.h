#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkReferencedObject.h"

namespace RE
{
	struct hkaAnnotationTrack;

	class __declspec(novtable) hkaAnimation :
		public hkReferencedObject  // 0x00
	{
	public:
		enum class AnimationType : std::int32_t
		{
			kUnknown = 0,
			kInterleaved = 1,
			kMirrored = 2,
			kSplineCompressed = 3,
			kQuantizedCompressed = 4,
			kPredictiveCompressed = 5,
			kReferencePose = 6
		};

		virtual ~hkaAnimation();  // 00

		// members
		AnimationType        animationType;        // 0x10
		float                duration;             // 0x14
		std::int32_t         numTransformTracks;   // 0x18
		std::int32_t         numFloatTracks;       // 0x1C
		void*                extractedMotion;      // 0x20
		hkArray<hkaAnnotationTrack> annotationTracks;  // 0x28
		std::uint32_t         unk38;                // 0x38
		std::uint32_t         unk3C;                // 0x3C
	};
	static_assert(sizeof(hkaAnimation) == 0x40);
}
