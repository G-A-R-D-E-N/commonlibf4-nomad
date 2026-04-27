#pragma once

#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint.h"

namespace RE
{
	class NiTransform
	{
	public:
		static const NiTransform ZERO;
		static const NiTransform IDENTITY;

		constexpr NiTransform() noexcept = default;
		constexpr NiTransform(const NiMatrix3& a_rotation, const NiPoint3& a_translation, const float a_scale = 1.0F) noexcept;

		constexpr bool        operator==(const NiTransform& a_rhs) const noexcept;
		constexpr bool        operator!=(const NiTransform& a_rhs) const noexcept;
		constexpr NiTransform operator*(const NiTransform& a_rhs) const noexcept;
		constexpr NiPoint3    operator*(const NiPoint3& a_rhs) const noexcept;

		constexpr NiTransform  Invert() const noexcept;
		constexpr NiTransform& MakeIdentity() noexcept;
		constexpr NiTransform& MakeInvert() noexcept;

		// members
		NiMatrix3 rotate;         // 00
		NiPoint3  translate;      // 30
		float     scale{ 1.0F };  // 3C
	};
	static_assert(sizeof(NiTransform) == 0x40);
}

template <>
struct std::formatter<RE::NiTransform>
{
	template <class ParseContext>
	constexpr auto parse(ParseContext& a_ctx)
	{
		return a_ctx.begin();
	}

	template <class FormatContext>
	constexpr auto format(const RE::NiTransform& a_transform, FormatContext& a_ctx) const
	{
		return format_to(a_ctx.out(), "<{}, {}>", a_transform.rotate, a_transform.translate, a_transform.scale);
	}
};
