#pragma once

#include "RE/B/BSScaleformExternalTexture.h"
#include "RE/M/MemoryManager.h"
#include "RE/N/NiPoint3.h"

namespace RE
{
	class LocalMapRenderer;

	namespace nsPipboy_LocalMap
	{
		inline void GetLocalMapCameraExtents(NiPoint3& a_corner1, NiPoint3& a_corner2, NiPoint3& a_corner3)
		{
			using func_t = void (*)(NiPoint3&, NiPoint3&, NiPoint3&);
			static REL::Relocation<func_t> func{ ID::nsPipboy_LocalMap::GetLocalMapCameraExtents };
			func(a_corner1, a_corner2, a_corner3);
		}

		inline void DestroyRenderer()
		{
			using func_t = void (*)();
			static REL::Relocation<func_t> func{ ID::nsPipboy_LocalMap::DestroyRenderer };
			func();
		}

		[[nodiscard]] inline BSScaleformExternalTexture* GetLocalMapTexture()
		{
			if (REX::FModule::IsRuntimeNG()) {
				return nullptr;
			}
			static REL::Relocation<BSScaleformExternalTexture**> texture{ ID::nsPipboy_LocalMap::LocalMapTexture };
			return *texture;
		}

		[[nodiscard]] inline LocalMapRenderer* GetMapRenderer()
		{
			if (REX::FModule::IsRuntimeNG()) {
				return nullptr;
			}
			static REL::Relocation<LocalMapRenderer**> renderer{ ID::nsPipboy_LocalMap::pMapRenderer };
			return *renderer;
		}

		[[nodiscard]] inline LocalMapRenderer* GetCompanionMapRenderer()
		{
			if (REX::FModule::IsRuntimeNG()) {
				return nullptr;
			}
			static REL::Relocation<LocalMapRenderer**> renderer{ ID::nsPipboy_LocalMap::pCompanionMapRenderer };
			return *renderer;
		}
	}
}
