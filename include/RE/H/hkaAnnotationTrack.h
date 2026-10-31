#pragma once

#include "RE/H/hkArray.h"

namespace RE
{
	class hkaAnnotationTrack
	{
	public:
		class Annotation
		{
		public:
			float       time;  // 0x00
			const char* text;  // 0x08
		};
		static_assert(sizeof(Annotation) == 0x10);

		const char*           name;         // 0x00
		hkArray<Annotation>   annotations;  // 0x08
	};
	static_assert(sizeof(hkaAnnotationTrack) == 0x18);
}
