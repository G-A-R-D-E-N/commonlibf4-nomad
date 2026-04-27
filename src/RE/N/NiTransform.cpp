#include "RE/N/NiTransform.h"

namespace RE
{
	inline constexpr NiTransform NiTransform::ZERO = { NiMatrix3::ZERO, NiPoint3::ZERO, 0.0F };
	inline constexpr NiTransform NiTransform::IDENTITY = { NiMatrix3::IDENTITY, NiPoint3::ZERO, 1.0F };

	constexpr NiTransform::NiTransform(const NiMatrix3& a_rotation, const NiPoint3& a_translation, const float a_scale) noexcept :
		rotate(a_rotation), translate(a_translation), scale(a_scale)
	{}

	constexpr bool NiTransform::operator==(const NiTransform& a_rhs) const noexcept
	{
		return (rotate == a_rhs.rotate) && (translate == a_rhs.translate) && (scale == a_rhs.scale);
	}

	constexpr bool NiTransform::operator!=(const NiTransform& a_rhs) const noexcept
	{
		return !operator==(a_rhs);
	}

	constexpr NiTransform NiTransform::operator*(const NiTransform& a_rhs) const noexcept
	{
		return NiTransform(rotate * a_rhs.rotate, translate + (rotate * a_rhs.translate) * scale, scale * a_rhs.scale);
	}

	constexpr NiPoint3 NiTransform::operator*(const NiPoint3& a_rhs) const noexcept
	{
		return NiPoint3(((rotate * a_rhs) * scale) + translate);
	}

	constexpr NiTransform NiTransform::Invert() const noexcept
	{
		NiTransform transform(*this);
		return transform.MakeInvert();
	}

	constexpr NiTransform& NiTransform::MakeIdentity() noexcept
	{
		rotate = NiMatrix3::IDENTITY;
		translate = NiPoint3::ZERO;
		scale = 1.0F;
		return *this;
	}

	constexpr NiTransform& NiTransform::MakeInvert() noexcept
	{
		rotate = rotate.Transpose();
		scale = 1.0f / scale;
		translate = (rotate * -translate) * scale;
		return *this;
	}
}
