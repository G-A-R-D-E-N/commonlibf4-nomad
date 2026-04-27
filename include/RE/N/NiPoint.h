#pragma once

namespace RE
{
	class NiPoint2
	{
	public:
		static const NiPoint2 ZERO;
		static const NiPoint2 UNIT;
		static const NiPoint2 UNIT_X;
		static const NiPoint2 UNIT_Y;

		constexpr NiPoint2() noexcept = default;
		constexpr NiPoint2(float a_x, float a_y) noexcept;

		constexpr float&       operator[](std::size_t a_pos) noexcept;
		constexpr const float& operator[](std::size_t a_pos) const noexcept;
		constexpr bool         operator==(const NiPoint2& a_rhs) const noexcept;
		constexpr bool         operator!=(const NiPoint2& a_rhs) const noexcept;
		constexpr bool         operator<(const NiPoint2& a_rhs) const noexcept;
		constexpr bool         operator>(const NiPoint2& a_rhs) const noexcept;
		constexpr NiPoint2     operator+(const NiPoint2& a_rhs) const noexcept;
		constexpr NiPoint2     operator-(const NiPoint2& a_rhs) const noexcept;
		constexpr NiPoint2     operator*(const NiPoint2& a_rhs) const noexcept;
		constexpr NiPoint2     operator/(const NiPoint2& a_rhs) const noexcept;
		constexpr NiPoint2     operator*(float a_scalar) const noexcept;
		constexpr NiPoint2     operator/(float a_scalar) const noexcept;
		constexpr NiPoint2     operator-() const noexcept;
		constexpr NiPoint2&    operator+=(const NiPoint2& a_rhs) noexcept;
		constexpr NiPoint2&    operator-=(const NiPoint2& a_rhs) noexcept;
		constexpr NiPoint2&    operator*=(const NiPoint2& a_rhs) noexcept;
		constexpr NiPoint2&    operator/=(const NiPoint2& a_rhs) noexcept;
		constexpr NiPoint2&    operator+=(float a_scalar) noexcept;
		constexpr NiPoint2&    operator-=(float a_scalar) noexcept;
		constexpr NiPoint2&    operator*=(float a_scalar) noexcept;
		constexpr NiPoint2&    operator/=(float a_scalar) noexcept;

		// members
		float x{ 0.0F };  // 00
		float y{ 0.0F };  // 04
	};
	static_assert(sizeof(NiPoint2) == 0x8);
}

namespace RE
{
	class NiPoint3
	{
	public:
		static const NiPoint3 ZERO;
		static const NiPoint3 UNIT;
		static const NiPoint3 UNIT_X;
		static const NiPoint3 UNIT_Y;
		static const NiPoint3 UNIT_Z;

		constexpr NiPoint3() noexcept = default;
		constexpr NiPoint3(const NiPoint2& a_point) noexcept;
		constexpr NiPoint3(float a_x, float a_y, float a_z) noexcept;

		constexpr float&       operator[](std::size_t a_pos) noexcept;
		constexpr const float& operator[](std::size_t a_pos) const noexcept;
		constexpr bool         operator==(const NiPoint3& a_rhs) const noexcept;
		constexpr bool         operator!=(const NiPoint3& a_rhs) const noexcept;
		constexpr bool         operator<(const NiPoint3& a_rhs) const noexcept;
		constexpr bool         operator>(const NiPoint3& a_rhs) const noexcept;
		constexpr NiPoint3     operator+(const NiPoint3& a_rhs) const noexcept;
		constexpr NiPoint3     operator-(const NiPoint3& a_rhs) const noexcept;
		constexpr NiPoint3     operator*(const NiPoint3& a_rhs) const noexcept;
		constexpr NiPoint3     operator/(const NiPoint3& a_rhs) const noexcept;
		constexpr NiPoint3     operator*(float a_scalar) const noexcept;
		constexpr NiPoint3     operator/(float a_scalar) const noexcept;
		constexpr NiPoint3     operator-() const noexcept;
		constexpr NiPoint3&    operator+=(const NiPoint3& a_rhs) noexcept;
		constexpr NiPoint3&    operator-=(const NiPoint3& a_rhs) noexcept;
		constexpr NiPoint3&    operator*=(const NiPoint3& a_rhs) noexcept;
		constexpr NiPoint3&    operator/=(const NiPoint3& a_rhs) noexcept;
		constexpr NiPoint3&    operator+=(float a_scalar) noexcept;
		constexpr NiPoint3&    operator-=(float a_scalar) noexcept;
		constexpr NiPoint3&    operator*=(float a_scalar) noexcept;
		constexpr NiPoint3&    operator/=(float a_scalar) noexcept;

		constexpr NiPoint3 Cross(const NiPoint3& a_point) const noexcept;
		constexpr float    Dot(const NiPoint3& a_point) const noexcept;
		constexpr float    GetSquaredDistance(const NiPoint3& a_point) const noexcept;
		constexpr float    SqrLength() const noexcept;

		float    GetDistance(const NiPoint3& a_point) const noexcept;
		float    GetZAngleFromVector() const;
		float    Length() const noexcept;
		NiPoint3 UnitCross(const NiPoint3& a_point) const noexcept;
		float    Unitize() noexcept;

		// members
		float x{ 0.0F };  // 00
		float y{ 0.0F };  // 04
		float z{ 0.0F };  // 08
	};
	static_assert(sizeof(NiPoint3) == 0xC);

	class alignas(0x10) NiPoint3A :
		public NiPoint3
	{
	public:
		static const NiPoint3A ZERO;
		static const NiPoint3A UNIT;
		static const NiPoint3A UNIT_X;
		static const NiPoint3A UNIT_Y;
		static const NiPoint3A UNIT_Z;

		using NiPoint3::NiPoint3;
	};
	static_assert(sizeof(NiPoint3A) == 0x10);
}

namespace RE
{
	class NiPoint4
	{
	public:
		static const NiPoint4 ZERO;
		static const NiPoint4 IDENTITY0;
		static const NiPoint4 IDENTITY1;
		static const NiPoint4 IDENTITY2;
		static const NiPoint4 IDENTITY3;

		constexpr NiPoint4() noexcept = default;
		constexpr NiPoint4(const NiPoint2& a_point) noexcept;
		constexpr NiPoint4(const NiPoint3& a_point) noexcept;
		constexpr NiPoint4(float a_x, float a_y, float a_z, float a_w) noexcept;

		constexpr float&       operator[](std::size_t a_pos) noexcept;
		constexpr const float& operator[](std::size_t a_pos) const noexcept;
		constexpr bool         operator==(const NiPoint4& a_rhs) const noexcept;
		constexpr bool         operator!=(const NiPoint4& a_rhs) const noexcept;
		constexpr bool         operator<(const NiPoint4& a_rhs) const noexcept;
		constexpr bool         operator>(const NiPoint4& a_rhs) const noexcept;
		constexpr NiPoint4     operator+(const NiPoint4& a_rhs) const noexcept;
		constexpr NiPoint4     operator-(const NiPoint4& a_rhs) const noexcept;
		constexpr NiPoint4     operator*(const NiPoint4& a_rhs) const noexcept;
		constexpr NiPoint4     operator/(const NiPoint4& a_rhs) const noexcept;
		constexpr NiPoint4     operator*(float a_scalar) const noexcept;
		constexpr NiPoint4     operator/(float a_scalar) const noexcept;
		constexpr NiPoint4     operator-() const noexcept;
		constexpr NiPoint4&    operator+=(const NiPoint4& a_rhs) noexcept;
		constexpr NiPoint4&    operator-=(const NiPoint4& a_rhs) noexcept;
		constexpr NiPoint4&    operator*=(const NiPoint4& a_rhs) noexcept;
		constexpr NiPoint4&    operator/=(const NiPoint4& a_rhs) noexcept;
		constexpr NiPoint4&    operator+=(float a_scalar) noexcept;
		constexpr NiPoint4&    operator-=(float a_scalar) noexcept;
		constexpr NiPoint4&    operator*=(float a_scalar) noexcept;
		constexpr NiPoint4&    operator/=(float a_scalar) noexcept;

		// members
		float x{ 0.0F };  // 00
		float y{ 0.0F };  // 04
		float z{ 0.0F };  // 08
		float w{ 0.0F };  // 0C
	};
	static_assert(sizeof(NiPoint4) == 0x10);
}

template <>
struct std::formatter<RE::NiPoint2>
{
	template <class ParseContext>
	constexpr auto parse(ParseContext& a_ctx)
	{
		return a_ctx.begin();
	}

	template <class FormatContext>
	constexpr auto format(const RE::NiPoint2& a_point, FormatContext& a_ctx) const
	{
		return format_to(a_ctx.out(), "({}, {})", a_point.x, a_point.y);
	}
};

template <>
struct std::formatter<RE::NiPoint3>
{
	template <class ParseContext>
	constexpr auto parse(ParseContext& a_ctx)
	{
		return a_ctx.begin();
	}

	template <class FormatContext>
	constexpr auto format(const RE::NiPoint3& a_point, FormatContext& a_ctx) const
	{
		return format_to(a_ctx.out(), "({}, {}, {})", a_point.x, a_point.y, a_point.z);
	}
};

template <>
struct std::formatter<RE::NiPoint4>
{
	template <class ParseContext>
	constexpr auto parse(ParseContext& a_ctx)
	{
		return a_ctx.begin();
	}

	template <class FormatContext>
	constexpr auto format(const RE::NiPoint4& a_point, FormatContext& a_ctx) const
	{
		return format_to(a_ctx.out(), "({}, {}, {}, {})", a_point.x, a_point.y, a_point.z, a_point.w);
	}
};
