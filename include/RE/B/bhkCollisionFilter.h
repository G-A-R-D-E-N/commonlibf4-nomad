#pragma once

#include <cstdint>

namespace RE
{
	class __declspec(novtable) bhkCollisionFilter
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

		bhkCollisionFilter() { ctor(); }
		virtual ~bhkCollisionFilter();  // 00

		void InitFlags()
		{
			using func_t = decltype(&bhkCollisionFilter::InitFlags);
			static REL::Relocation<func_t> func{ ID::bhkCollisionFilter::InitFlags };
			func(this);
		}

		void SetLayerCollision(std::uint32_t a_layer, std::uint32_t a_otherLayer, bool a_set)
		{
			using func_t = decltype(&bhkCollisionFilter::SetLayerCollision);
			static REL::Relocation<func_t> func{ ID::bhkCollisionFilter::SetLayerCollision };
			func(this, a_layer, a_otherLayer, a_set);
		}

		void SetPartCollision(std::uint32_t a_part, std::uint32_t a_otherPart, bool a_set)
		{
			using func_t = decltype(&bhkCollisionFilter::SetPartCollision);
			static REL::Relocation<func_t> func{ ID::bhkCollisionFilter::SetPartCollision };
			func(this, a_part, a_otherPart, a_set);
		}

		[[nodiscard]] bool TestPair(std::uint32_t a_filterA, std::uint32_t a_filterB) const
		{
			using func_t = decltype(&bhkCollisionFilter::TestPair);
			static REL::Relocation<func_t> func{ ID::bhkCollisionFilter::TestPair };
			return func(this, a_filterA, a_filterB);
		}

		// members
		std::uint8_t  pad08[0x18];           // 0x08
		std::uint32_t systemGroupTable[32];  // 0x20
		std::uint8_t  padA0[0x100];          // 0xA0
		std::uint64_t layerTable[64];        // 0x1A0
		std::uint64_t layerMask;             // 0x3A0
		std::uint64_t unk3A8;                // 0x3A8
		std::uint8_t  layerNames[0x300];     // 0x3B0
		std::uint8_t  partNames[0x100];      // 0x6B0

	private:
		bhkCollisionFilter* ctor()
		{
			using func_t = decltype(&bhkCollisionFilter::ctor);
			static REL::Relocation<func_t> func{ ID::bhkCollisionFilter::ctor };
			return func(this);
		}
	};
	static_assert(sizeof(bhkCollisionFilter) == 0x7B0);
}
