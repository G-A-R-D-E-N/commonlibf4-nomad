#include "RE/H/hkVector4.h"

namespace RE
{
	inline constexpr hkVector4f hkVector4f::ZERO = { 0.0F, 0.0F, 0.0F, 0.0F };

	constexpr hkVector4f::hkVector4f(float a_x, float a_y, float a_z, float a_w) noexcept :
		x(a_x), y(a_y), z(a_z), w(a_w)
	{}

	constexpr float& hkVector4f::operator[](std::size_t a_pos) noexcept
	{
		assert(a_pos < 4);
		return std::addressof(x)[a_pos];
	}

	constexpr const float& hkVector4f::operator[](std::size_t a_pos) const noexcept
	{
		assert(a_pos < 4);
		return std::addressof(x)[a_pos];
	}

	constexpr bool hkVector4f::operator==(const hkVector4f& a_rhs) const noexcept
	{
		return (x == a_rhs.x) && (y == a_rhs.y) && (z == a_rhs.z) && (w == a_rhs.w);
	}

	constexpr bool hkVector4f::operator!=(const hkVector4f& a_rhs) const noexcept
	{
		return !operator==(a_rhs);
	}

	constexpr bool hkVector4f::operator<(const hkVector4f& a_rhs) const noexcept
	{
		return std::tie(x, y, z, w) < std::tie(a_rhs.x, a_rhs.y, a_rhs.z, a_rhs.w);
	}

	constexpr bool hkVector4f::operator>(const hkVector4f& a_rhs) const noexcept
	{
		return std::tie(x, y, z, w) > std::tie(a_rhs.x, a_rhs.y, a_rhs.z, a_rhs.w);
	}

	constexpr hkVector4f hkVector4f::operator+(const hkVector4f& a_rhs) const noexcept
	{
		return hkVector4f(x + a_rhs.x, y + a_rhs.y, z + a_rhs.z, w + a_rhs.w);
	}

	constexpr hkVector4f hkVector4f::operator-(const hkVector4f& a_rhs) const noexcept
	{
		return hkVector4f(x - a_rhs.x, y - a_rhs.y, z - a_rhs.z, w - a_rhs.w);
	}

	constexpr hkVector4f hkVector4f::operator*(const hkVector4f& a_rhs) const noexcept
	{
		return hkVector4f(x * a_rhs.x, y * a_rhs.y, z * a_rhs.z, w * a_rhs.w);
	}

	constexpr hkVector4f hkVector4f::operator/(const hkVector4f& a_rhs) const noexcept
	{
		return hkVector4f(x / a_rhs.x, y / a_rhs.y, z / a_rhs.z, w / a_rhs.w);
	}

	constexpr hkVector4f hkVector4f::operator*(float a_scalar) const noexcept
	{
		return hkVector4f(x * a_scalar, y * a_scalar, z * a_scalar, w * a_scalar);
	}

	constexpr hkVector4f hkVector4f::operator/(float a_scalar) const noexcept
	{
		return operator*(1.0F / a_scalar);
	}

	constexpr hkVector4f hkVector4f::operator-() const noexcept
	{
		return hkVector4f(-x, -y, -z, -w);
	}

	constexpr hkVector4f& hkVector4f::operator+=(const hkVector4f& a_rhs) noexcept
	{
		x += a_rhs.x;
		y += a_rhs.y;
		z += a_rhs.z;
		w += a_rhs.w;
		return *this;
	}

	constexpr hkVector4f& hkVector4f::operator-=(const hkVector4f& a_rhs) noexcept
	{
		x -= a_rhs.x;
		y -= a_rhs.y;
		z -= a_rhs.z;
		w -= a_rhs.w;
		return *this;
	}

	constexpr hkVector4f& hkVector4f::operator*=(const hkVector4f& a_rhs) noexcept
	{
		x *= a_rhs.x;
		y *= a_rhs.y;
		z *= a_rhs.z;
		w *= a_rhs.w;
		return *this;
	}

	constexpr hkVector4f& hkVector4f::operator/=(const hkVector4f& a_rhs) noexcept
	{
		x /= a_rhs.x;
		y /= a_rhs.y;
		z /= a_rhs.z;
		w /= a_rhs.w;
		return *this;
	}

	constexpr hkVector4f& hkVector4f::operator+=(float a_scalar) noexcept
	{
		x += a_scalar;
		y += a_scalar;
		z += a_scalar;
		w += a_scalar;
		return *this;
	}

	constexpr hkVector4f& hkVector4f::operator-=(float a_scalar) noexcept
	{
		x -= a_scalar;
		y -= a_scalar;
		z -= a_scalar;
		w -= a_scalar;
		return *this;
	}

	constexpr hkVector4f& hkVector4f::operator*=(float a_scalar) noexcept
	{
		x *= a_scalar;
		y *= a_scalar;
		z *= a_scalar;
		w *= a_scalar;
		return *this;
	}

	constexpr hkVector4f& hkVector4f::operator/=(float a_scalar) noexcept
	{
		x /= a_scalar;
		y /= a_scalar;
		z /= a_scalar;
		w /= a_scalar;
		return *this;
	}

	constexpr float hkVector4f::Dot(const hkVector4f& v) const
	{
		return this->x * v.x + this->y * v.y + this->z * v.z;
	}

	inline hkVector4f hkVector4f::GetNormalized() const
	{
		hkVector4f norm = *this;
		norm.Normalize();
		return norm;
	}

	inline float hkVector4f::Length() const
	{
		return std::sqrt(x * x + y * y + z * z);
	}

	inline hkVector4f& hkVector4f::Normalize()
	{
		float l = Length();
		if (l == 0) {
			this->x = 0;
			this->y = 0;
			this->z = 0;
			return *this;
		}
		this->x /= l;
		this->y /= l;
		this->z /= l;
		return *this;
	}
}
