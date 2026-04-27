#pragma once

#include "RE/H/hkArray.h"

namespace RE
{
	class hkVisualDebugger;

	class hkProcessContext
	{
	public:
		hkProcessContext() = default;

		virtual ~hkProcessContext() = default;

		virtual const char* GetType() = 0;

		virtual void SetOwner(hkVisualDebugger* a_owner)
		{
			owner = a_owner;
		}

		// members
		hkVisualDebugger*              owner{ nullptr };     // 0x08
		hkInplaceArray<const char*, 6> monitorStreamBegins;  // 0x10
		hkInplaceArray<const char*, 6> monitorStreamEnds;    // 0x50
	};
	static_assert(sizeof(hkProcessContext) == 0x90);
}
