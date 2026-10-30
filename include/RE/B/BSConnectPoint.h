#pragma once

namespace RE
{
	// Real engine type with several nested types (Parent, Parents, Children, ChildOrigin,
	// ConnectPointName, ConnectData, SkinAttach) and members not reverse-engineered here.
	// Parent is forward-declared only far enough to name it inside
	// BSTSmartPointer<Parent>& parameters (e.g. Workshop::SetSnapInfo) - that usage never
	// requires Parent's layout, only that the type exists.
	class BSConnectPoint
	{
	public:
		class Parent;
	};
}
