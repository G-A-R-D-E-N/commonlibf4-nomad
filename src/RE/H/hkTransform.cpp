#include "RE/H/hkTransform.h"

namespace RE
{
	constexpr hkTransformf::hkTransformf(const hkRotationf& a_rotation, const hkVector4f& a_translation) noexcept :
		rotation(a_rotation), translation(a_translation)
	{}
}
