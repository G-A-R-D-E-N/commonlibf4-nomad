#pragma once

#include "RE/H/hkSimdFloat32.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class hknpSolverInfo
	{
	public:
		// members
		float         tau;                                   // 0x000
		float         frictionTau;                           // 0x004
		hkSimdFloat32 damping;                               // 0x010
		hkSimdFloat32 deltaTime;                             // 0x020
		hkSimdFloat32 invDeltaTime;                          // 0x030
		hkSimdFloat32 subStepDeltaTime;                      // 0x040
		hkSimdFloat32 subStepInvDeltaTime;                   // 0x050
		hkSimdFloat32 distanceToLinearTim;                   // 0x060
		hkSimdFloat32 linearTimToDistance;                   // 0x070
		hkSimdFloat32 collisionTolerance;                    // 0x080
		hkSimdFloat32 unitScale;                             // 0x090
		hkSimdFloat32 collisionAccuracy;                     // 0x0A0
		float         maxApproachSpeedForHighQualitySolver;  // 0x0B0
		std::int32_t  numSteps;                              // 0x0B4
		float         invNumSteps;                           // 0x0B8
		std::int32_t  numMicroSteps;                         // 0x0BC
		float         invNumMicroSteps;                      // 0x0C0
		float         nominalGravityLength;                  // 0x0C4
		float         expectedDeltaTime;                     // 0x0C8
		std::uint32_t stepSolveCount;                        // 0x0CC
		hkVector4f    globalAccelerationPerSubStep;          // 0x0D0
		hkVector4f    globalAccelerationPerStep;             // 0x0E0
		hkVector4f    integrateVelocityFactor;               // 0x0F0
		hkVector4f    invIntegrateVelocityFactor;            // 0x100
		hkSimdFloat32 rhsFactor;                             // 0x110
		hkSimdFloat32 frictionRhsFactor;                     // 0x120
		float         dampDivTau;                            // 0x130
		float         tauDivDamp;                            // 0x134
		float         dampDivFrictionTau;                    // 0x138
		float         frictionTauDivDamp;                    // 0x13C
	};
	static_assert(sizeof(hknpSolverInfo) == 0x140);
}
