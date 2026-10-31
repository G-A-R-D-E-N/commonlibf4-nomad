#pragma once

#include "RE/H/hkbGeneratorPartitionInfo.h"
#include "RE/H/hkbNode.h"

namespace RE
{
	class __declspec(novtable) hkbGenerator :
		public hkbNode  // 0x50
	{
	public:
		virtual ~hkbGenerator();  // 00

		// members
		hkbGeneratorPartitionInfo partitionInfo;  // 0x50
		void*                     syncInfo;       // 0x78
		std::uint8_t              pad80[8];       // 0x80
	};
	static_assert(sizeof(hkbGenerator) == 0x88);
}
