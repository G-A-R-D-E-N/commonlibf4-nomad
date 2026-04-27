#pragma once

namespace RE
{
	class __declspec(align(16)) hkVector4f
	{
	public:
		static const hkVector4f ZERO;

		constexpr hkVector4f() noexcept = default;
		constexpr hkVector4f(float a_x, float a_y, float a_z, float a_w) noexcept;

		constexpr float&       operator[](std::size_t a_pos) noexcept;
		constexpr const float& operator[](std::size_t a_pos) const noexcept;
		constexpr bool         operator==(const hkVector4f& a_rhs) const noexcept;
		constexpr bool         operator!=(const hkVector4f& a_rhs) const noexcept;
		constexpr bool         operator<(const hkVector4f& a_rhs) const noexcept;
		constexpr bool         operator>(const hkVector4f& a_rhs) const noexcept;
		constexpr hkVector4f   operator+(const hkVector4f& a_rhs) const noexcept;
		constexpr hkVector4f   operator-(const hkVector4f& a_rhs) const noexcept;
		constexpr hkVector4f   operator*(const hkVector4f& a_rhs) const noexcept;
		constexpr hkVector4f   operator/(const hkVector4f& a_rhs) const noexcept;
		constexpr hkVector4f   operator*(float a_scalar) const noexcept;
		constexpr hkVector4f   operator/(float a_scalar) const noexcept;
		constexpr hkVector4f   operator-() const noexcept;
		constexpr hkVector4f&  operator+=(const hkVector4f& a_rhs) noexcept;
		constexpr hkVector4f&  operator-=(const hkVector4f& a_rhs) noexcept;
		constexpr hkVector4f&  operator*=(const hkVector4f& a_rhs) noexcept;
		constexpr hkVector4f&  operator/=(const hkVector4f& a_rhs) noexcept;
		constexpr hkVector4f&  operator+=(float a_scalar) noexcept;
		constexpr hkVector4f&  operator-=(float a_scalar) noexcept;
		constexpr hkVector4f&  operator*=(float a_scalar) noexcept;
		constexpr hkVector4f&  operator/=(float a_scalar) noexcept;

		constexpr float Dot(const hkVector4f& v) const;

		hkVector4f  GetNormalized() const;
		float       Length() const;
		hkVector4f& Normalize();

		// members
		float x{ 0.0F };
		float y{ 0.0F };
		float z{ 0.0F };
		float w{ 0.0F };
	};
	static_assert(sizeof(hkVector4f) == 0x10);

	using hkVector4 = hkVector4f;
};
