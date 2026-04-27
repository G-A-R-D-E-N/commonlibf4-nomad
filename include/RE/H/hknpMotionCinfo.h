#pragma once

#include "RE/H/hkQuaternion.h"
#include "RE/H/hkVector4.h"
#include "RE/H/hknpMotionPropertiesId.h"

namespace RE
{
	class hkLocalFrame;
	class hknpBodyCinfo;

	class hknpMotionCinfo
	{
	public:
		hknpMotionCinfo()
		{
			using func_t = void (*)(hknpMotionCinfo*);
			static REL::Relocation<func_t> func{ ID::hknpMotionCinfo::ctor };
			func(this);
		}

		void InitializeAsKeyFramed(hknpBodyCinfo* a_cInfos, std::uint32_t a_cInfosNum)
		{
			using func_t = decltype(&hknpMotionCinfo::InitializeAsKeyFramed);
			static REL::Relocation<func_t> func{ ID::hknpMotionCinfo::InitializeAsKeyFramed };
			func(this, a_cInfos, a_cInfosNum);
		}

		// members
		hknpMotionPropertiesId motionPropertiesId;                    // 0x00
		hkBool                 enableDeactivation;                    // 0x02
		float                  inverseMass;                           // 0x04
		float                  massFactor;                            // 0x08
		float                  maxLinearAccelerationDistancePerStep;  // 0x0C
		float                  maxRotationToPreventTunneling;         // 0x10
		hkVector4f             inverseInertiaLocal;                   // 0x20
		hkVector4f             centerOfMassWorld;                     // 0x30
		hkQuaternionf          orientation;                           // 0x40
		hkVector4f             linearVelocity;                        // 0x50
		hkVector4f             angularVelocity;                       // 0x60
	};
	static_assert(sizeof(hknpMotionCinfo) == 0x70);
}
