#pragma once

#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbBehaviorGraph :
		public hkbGenerator  // 0x88
	{
	public:
		virtual ~hkbBehaviorGraph();  // 00

		// members
		std::uint32_t variableMode;                 // 0x88
		std::uint8_t  pad8C[4];                     // 0x8C
		void*         uniqueIdPool;                 // 0x90
		void*         idToStateMachineTemplateMap;  // 0xA0
		void*         mirroredExternalIdMap;        // 0xA8
		void*         pseudoRandomGenerator;        // 0xB8
		void*         rootGenerator;                // 0xC0
		void*         data;                         // 0xC8
		void*         templateGraph;                // 0xD0
		void*         rootGeneratorClone;           // 0xD8
		void*         activeNodes;                  // 0xE0
		void*         globalTransitionData;         // 0xE8
		void*         eventIdMap;                   // 0xF0
		void*         attributeIdMap;               // 0xF8
		void*         variableIdMap;                // 0x100
		void*         characterPropertyIdMap;       // 0x108
		void*         variableValueSet;             // 0x110
		std::uint8_t  pad118[0x90];                 // 0x118
		std::uint16_t nextUniqueId;                 // 0x1A8
		bool          isActive;                     // 0x1AA
		std::uint8_t  pad1AB[3];                    // 0x1AB
		bool          checkNodeValidity;            // 0x1AE
		bool          stateOrTransitionChanged;     // 0x1AF
	};
	static_assert(sizeof(hkbBehaviorGraph) == 0x1B0);
}
