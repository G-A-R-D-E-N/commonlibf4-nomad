#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkVector4.h"

namespace RE
{
	class hkStridedVertices
	{
	public:
		constexpr hkStridedVertices() = default;

		template <class T>
		constexpr hkStridedVertices(const T* a_vertices, const std::int32_t a_numVertices)
		{
			static_assert(sizeof(T) > sizeof(float));
			vertices = (const float*)vertices;
			numVertices = a_numVertices;
			striding = sizeof(T);
		}

		hkStridedVertices(const hkArrayBase<hkVector4>& a_vertices)
		{
			vertices = (const float*)a_vertices.begin();
			numVertices = a_vertices.size();
			striding = sizeof(hkVector4);
		}

		constexpr std::int32_t size() const
		{
			return numVertices;
		}

		// members
		const float* vertices{ nullptr };  // 0x00
		std::int32_t numVertices{ 0 };     // 0x08
		std::int32_t striding{ 0 };        // 0x0C - sizeof(T)
	};
	static_assert(sizeof(hkStridedVertices) == 0x10);
}
