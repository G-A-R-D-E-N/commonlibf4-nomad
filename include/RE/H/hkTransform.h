#pragma once

#include "RE/H/hkRotation.h"

namespace RE
{
	class hkTransformf
	{
	public:
		constexpr hkTransformf() noexcept = default;
		constexpr hkTransformf(const hkRotationf& a_rotation, const hkVector4f& a_translation) noexcept;

		// members
		hkRotationf rotation;
		hkVector4f  translation;
	};

	using hkTransform = hkTransformf;
}

namespace RE
{
   	constexpr hkTransformf::hkTransformf(const hkRotationf& a_rotation, const hkVector4f& a_translation) noexcept :
		rotation(a_rotation), translation(a_translation)
	{}
}
