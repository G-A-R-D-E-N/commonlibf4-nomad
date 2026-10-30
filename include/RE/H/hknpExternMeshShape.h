#pragma once

#include "RE/H/hknpCompositeShape.h"

namespace RE
{
	class __declspec(novtable) hknpExternMeshShape :
		public hknpCompositeShape
	{
	public:
		static constexpr auto RTTI{ RTTI::hknpExternMeshShape };
		static constexpr auto VTABLE{ VTABLE::hknpExternMeshShape };

		// members
		void* geometry;            // 0x60 - pointer, target type unconfirmed
		void* boundingVolumeData;  // 0x68 - pointer, target type unconfirmed
	};
	static_assert(sizeof(hknpExternMeshShape) == 0x70);
}
