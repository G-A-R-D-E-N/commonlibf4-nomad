#pragma once

#include "RE/N/NiMatrix3.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class NiQuaternion
	{
	public:
		constexpr NiQuaternion() noexcept = default;
		constexpr NiQuaternion(float a_w, float a_x, float a_y, float a_z) noexcept :
			w(a_w), x(a_x), y(a_y), z(a_z)
		{}

		NiQuaternion(const NiMatrix3& a_rotation) { FromRotation(a_rotation); }

		constexpr NiQuaternion operator*(const NiQuaternion& a_rhs) const noexcept
		{
			return {
				a_rhs.w * w - a_rhs.x * x - a_rhs.y * y - a_rhs.z * z,
				a_rhs.w * x + a_rhs.x * w - a_rhs.y * z + a_rhs.z * y,
				a_rhs.w * y + a_rhs.x * z + a_rhs.y * w - a_rhs.z * x,
				a_rhs.w * z - a_rhs.x * y + a_rhs.y * x + a_rhs.z * w
			};
		}

		constexpr NiQuaternion& operator*=(const NiQuaternion& a_rhs) noexcept
		{
			*this = *this * a_rhs;
			return *this;
		}

		constexpr NiQuaternion operator*(float a_scalar) const noexcept { return { w * a_scalar, x * a_scalar, y * a_scalar, z * a_scalar }; }
		constexpr NiQuaternion operator/(float a_scalar) const noexcept { return { w / a_scalar, x / a_scalar, y / a_scalar, z / a_scalar }; }
		constexpr NiQuaternion operator+(const NiQuaternion& a_rhs) const noexcept { return { w + a_rhs.w, x + a_rhs.x, y + a_rhs.y, z + a_rhs.z }; }
		constexpr NiQuaternion operator-(const NiQuaternion& a_rhs) const noexcept { return { w - a_rhs.w, x - a_rhs.x, y - a_rhs.y, z - a_rhs.z }; }
		constexpr NiQuaternion operator-() const noexcept { return { -w, -x, -y, -z }; }

		[[nodiscard]] constexpr NiQuaternion InvertScalar() const noexcept { return { -w, x, y, z }; }
		[[nodiscard]] constexpr NiQuaternion InvertVector() const noexcept { return { w, -x, -y, -z }; }
		[[nodiscard]] constexpr NiQuaternion Abs() const noexcept { return { w < 0.0F ? -w : w, x, y, z }; }

		void FromRotation(const NiMatrix3& a_rotation);
		void ToRotation(NiMatrix3& a_rotation) const;
		void FromEulerAnglesXYZ(float a_x, float a_y, float a_z);  // x = pitch, y = roll, z = yaw
		void FromAngleAxis(float a_angle, const NiPoint3& a_axis);
		void ToAngleAxis(float& a_angle, NiPoint3& a_axis) const;
		void Slerp(float a_time, const NiQuaternion& a_begin, const NiQuaternion& a_end);

		NiQuaternion& Intermediate(const NiQuaternion& a_before, const NiQuaternion& a_current, const NiQuaternion& a_after);
		NiQuaternion& UnitInverse(const NiQuaternion& a_quaternion);
		NiQuaternion& Exp(const NiQuaternion& a_quaternion);  // unpacks a vector into a quaternion
		NiQuaternion& Log(const NiQuaternion& a_quaternion);  // packs a quaternion into a vector

		[[nodiscard]] NiQuaternion ExpN() const
		{
			NiQuaternion result;
			result.Exp(*this);
			return result;
		}

		[[nodiscard]] NiQuaternion LogN() const
		{
			NiQuaternion result;
			result.Log(*this);
			return result;
		}

		// members
		float w{ 0.0F };  // 00
		float x{ 0.0F };  // 04
		float y{ 0.0F };  // 08
		float z{ 0.0F };  // 0C
	};
	static_assert(sizeof(NiQuaternion) == 0x10);
}
