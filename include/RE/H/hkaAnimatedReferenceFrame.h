#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	enum class hkaReferenceFrameTypeEnum : std::int8_t
	{
		REFERENCE_FRAME_UNKNOWN = 0,
		REFERENCE_FRAME_DEFAULT = 1,
		REFERENCE_FRAME_PARAMETRIC = 2
	};

	class __declspec(novtable) hkaAnimatedReferenceFrame :
		public hkReferencedObject  // 0x10
	{
	public:
		virtual ~hkaAnimatedReferenceFrame();  // 00

		// members
		hkaReferenceFrameTypeEnum frameType;  // 0x10
		std::uint8_t              pad11[7];   // 0x11
	};
	static_assert(sizeof(hkaAnimatedReferenceFrame) == 0x18);
}
