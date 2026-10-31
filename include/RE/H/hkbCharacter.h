#pragma once

#include "RE/H/hkReferencedObject.h"

namespace RE
{
	class hkbCharacter :
		public hkReferencedObject  // 0x10
	{
	public:
		virtual ~hkbCharacter();  // 00

		// members
		void*         nearbyCharacters;          // 0x10
		std::uint8_t  pad18[8];                  // 0x18
		void*         userData;                  // 0x20
		std::int8_t   currentLod;                // 0x28
		std::uint8_t  pad29;                     // 0x29
		std::int16_t  numTracksInLod;            // 0x2A
		std::uint8_t  pad2C[4];                  // 0x2C
		void*         generatorOutput;           // 0x30
		const char*   name;                      // 0x38
		void*         animationDrivers[6];       // 0x40
		std::uint8_t  pad70[8];                  // 0x70
		void*         setup;                     // 0x78
		void*         behaviorGraph;             // 0x80
		void*         projectData;               // 0x88
		void*         animationBindingSet;       // 0x90
		void*         spatialQueryInterface;     // 0x98
		void*         world;                     // 0xA0
		void*         boneAttachments;           // 0xA8
		std::uint8_t  padB0[8];                  // 0xB0
		void*         eventQueue;                // 0xB8
		void*         characterLuaState;         // 0xC0
		void*         assetManager;              // 0xC8
		std::uint32_t capabilities;              // 0xD0
		std::uint32_t effectiveCapabilities;     // 0xD4
	};
	static_assert(sizeof(hkbCharacter) == 0xD8);
}
