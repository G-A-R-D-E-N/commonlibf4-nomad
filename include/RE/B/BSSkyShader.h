#pragma once

#include "RE/B/BSShader.h"

namespace RE
{
	class __declspec(novtable) BSSkyShader :
		public BSShader  // 0x00
	{
	public:
		static constexpr auto RTTI{ RTTI::BSSkyShader };
		static constexpr auto VTABLE{ VTABLE::BSSkyShader };

		enum class BSSkyShaderTechniques : std::int32_t
		{
			kSky = 0,
			kSkyClouds = 1,
			kSkyCloudsLayers = 2,
			kSkySun = 3,
			kSkySunGlare = 4,
			kSkyAtmosphere = 5,
			kSkyStars = 6,
			kSkyMoon = 7,
			kSkyMoonShadow = 8,
			kTotal = 9
		};

		enum class VertexConstants : std::uint32_t
		{
			kWorldViewProj = 0,
			kWorld = 1,
			kBlendColor = 2,
			kEyePosition = 3,
			kTexCoordOff = 4,
			kPreviousWorld = 5
		};

		enum class PixelConstants : std::uint32_t
		{
			kParams = 0
		};

		enum class Samplers : std::uint32_t
		{
			kBase = 0,
			kBlend = 1,
			kNoiseGrad = 2
		};

		virtual ~BSSkyShader();  // 00

		virtual void Unk_01();  // 01
		virtual void SetupTechnique(std::uint32_t a_technique);  // 02
		virtual void RestoreTechnique(std::uint32_t a_technique);  // 03
		virtual void Unk_04();  // 04
		virtual void Unk_05();  // 05
		virtual void Unk_06();  // 06
		virtual void SetupGeometry();  // 07
		virtual void RestoreGeometry();  // 08
		virtual const char* GetTechniqueName(std::uint32_t a_technique);  // 09
		virtual void Unk_10();  // 10
		virtual void Unk_11();  // 11
		virtual void Unk_12();  // 12
	};
	static_assert(sizeof(BSSkyShader) == 0x120);
}
