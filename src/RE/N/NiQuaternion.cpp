#include "RE/N/NiQuaternion.h"

namespace RE
{
	void NiQuaternion::FromRotation(const NiMatrix3& a_rotation)
	{
		using func_t = void (*)(NiQuaternion*, const NiMatrix3&);
		static REL::Relocation<func_t> func{ ID::NiQuaternion::FromRotation };
		return func(this, a_rotation);
	}

	void NiQuaternion::ToRotation(NiMatrix3& a_rotation) const
	{
		using func_t = void (*)(const NiQuaternion*, NiMatrix3&);
		static REL::Relocation<func_t> func{ ID::NiQuaternion::ToRotation };
		return func(this, a_rotation);
	}

	void NiQuaternion::FromEulerAnglesXYZ(float a_x, float a_y, float a_z)
	{
		using func_t = void (*)(NiQuaternion*, float, float, float);
		static REL::Relocation<func_t> func{ ID::NiQuaternion::FromEulerAnglesXYZ };
		return func(this, a_x, a_y, a_z);
	}

	void NiQuaternion::FromAngleAxis(float a_angle, const NiPoint3& a_axis)
	{
		using func_t = void (*)(NiQuaternion*, float, const NiPoint3&);
		static REL::Relocation<func_t> func{ ID::NiQuaternion::FromAngleAxis };
		return func(this, a_angle, a_axis);
	}

	void NiQuaternion::ToAngleAxis(float& a_angle, NiPoint3& a_axis) const
	{
		using func_t = void (*)(const NiQuaternion*, float&, NiPoint3&);
		static REL::Relocation<func_t> func{ ID::NiQuaternion::ToAngleAxis };
		return func(this, a_angle, a_axis);
	}

	void NiQuaternion::Slerp(float a_time, const NiQuaternion& a_begin, const NiQuaternion& a_end)
	{
		using func_t = void (*)(NiQuaternion*, float, const NiQuaternion&, const NiQuaternion&);
		static REL::Relocation<func_t> func{ ID::NiQuaternion::Slerp };
		return func(this, a_time, a_begin, a_end);
	}

	NiQuaternion& NiQuaternion::Intermediate(const NiQuaternion& a_before, const NiQuaternion& a_current, const NiQuaternion& a_after)
	{
		using func_t = NiQuaternion& (*)(NiQuaternion*, const NiQuaternion&, const NiQuaternion&, const NiQuaternion&);
		static REL::Relocation<func_t> func{ ID::NiQuaternion::Intermediate };
		return func(this, a_before, a_current, a_after);
	}

	NiQuaternion& NiQuaternion::UnitInverse(const NiQuaternion& a_quaternion)
	{
		using func_t = NiQuaternion& (*)(NiQuaternion*, const NiQuaternion&);
		static REL::Relocation<func_t> func{ ID::NiQuaternion::UnitInverse };
		return func(this, a_quaternion);
	}

	NiQuaternion& NiQuaternion::Exp(const NiQuaternion& a_quaternion)
	{
		using func_t = NiQuaternion& (*)(NiQuaternion*, const NiQuaternion&);
		static REL::Relocation<func_t> func{ ID::NiQuaternion::Exp };
		return func(this, a_quaternion);
	}

	NiQuaternion& NiQuaternion::Log(const NiQuaternion& a_quaternion)
	{
		using func_t = NiQuaternion& (*)(NiQuaternion*, const NiQuaternion&);
		static REL::Relocation<func_t> func{ ID::NiQuaternion::Log };
		return func(this, a_quaternion);
	}
}
