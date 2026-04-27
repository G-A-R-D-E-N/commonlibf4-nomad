#pragma once

#include "RE/H/hkVector4.h"

namespace RE
{
	class hkMatrix3f
	{
	public:
		constexpr hkMatrix3f() noexcept = default;
		constexpr hkMatrix3f(const hkVector4f& a_vec0, const hkVector4f& a_vec1, const hkVector4f& a_vec2) noexcept;
		constexpr hkMatrix3f(
			float a_x0, float a_y0, float a_z0, float a_w0,
			float a_x1, float a_y1, float a_z1, float a_w1,
			float a_x2, float a_y2, float a_z2, float a_w2) noexcept;

		constexpr hkVector4f&       operator[](std::size_t a_pos) noexcept;
		constexpr const hkVector4f& operator[](std::size_t a_pos) const noexcept;
		constexpr bool              operator==(const hkMatrix3f& a_rhs) const noexcept;
		constexpr bool              operator!=(const hkMatrix3f& a_rhs) const noexcept;
		constexpr hkMatrix3f        operator*(const hkMatrix3f& a_rhs) const noexcept;
		constexpr hkMatrix3f        operator*(float a_scalar) const noexcept;

		// members
		hkVector4f col[3];  // 00
	};
	static_assert(sizeof(hkMatrix3f) == 0x30);

	using hkMatrix3 = hkMatrix3f;
}
