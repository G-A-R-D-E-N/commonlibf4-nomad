#pragma once

#include <cstdint>

namespace RE
{
	class bhkCollisionFilter
	{
	public:
		static constexpr auto VTABLE{ VTABLE::bhkCollisionFilter };

		enum class FilterBits : std::uint32_t
		{
			kLayerMask = 0x7F,
			kSystemGroupMask = 0x1F00,
			kNoCollide = 0x4000,
			kAdjacencyMode = 0x8000,
			kSubsystemMask = 0xFFFF0000
		};

		bhkCollisionFilter();
		virtual ~bhkCollisionFilter();  // 00

		void InitFlags();
		void SetLayerCollision(std::uint32_t a_layer, std::uint64_t a_flags);
		void SetPartCollision(std::uint32_t a_part, std::uint32_t a_flags);
		bool TestPair(std::uint32_t a_filterA, std::uint32_t a_filterB) const;
		bool FilterBodyPairs(std::uint32_t a_filterA, std::uint32_t a_filterB) const;

		// members
		std::uint8_t  pad08[0x18];         // 0x08
		std::uint32_t systemGroupTable[32];  // 0x20
		std::uint8_t  padA0[0x100];        // 0xA0
		std::uint64_t layerTable[64];      // 0x1A0
		std::uint64_t layerMask;           // 0x3A0
		std::uint64_t unk3A8;              // 0x3A8
		std::uint8_t  layerNames[0x300];   // 0x3B0
		std::uint8_t  partNames[0x100];    // 0x6B0
	};
}
