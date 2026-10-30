#pragma once

namespace RE
{
	// Pip-Boy/HUD controller font glyph characters, keyed by the engine's glyph name; decompile-verified on OG 1.10.163 only
	namespace ControllerGlyphs
	{
		namespace Xenon
		{
			inline constexpr char kA{ 'A' };
			inline constexpr char kB{ 'B' };
			inline constexpr char kX{ 'C' };
			inline constexpr char kY{ 'D' };
			inline constexpr char kSelect{ 'E' };
			inline constexpr char kLS{ 'F' };
			inline constexpr char kL1{ 'G' };
			inline constexpr char kL3{ 'H' };
			inline constexpr char kL2{ 'I' };
			inline constexpr char kRS{ 'K' };
			inline constexpr char kR1{ 'L' };
			inline constexpr char kR3{ 'M' };
			inline constexpr char kR2{ 'N' };
			inline constexpr char kStart{ 'O' };
		}

		namespace PSN
		{
			inline constexpr char kA{ 'a' };
			inline constexpr char kY{ 'b' };
			inline constexpr char kX{ 'c' };
			inline constexpr char kB{ 'd' };
			inline constexpr char kL3{ 'f' };
			inline constexpr char kL1{ 'g' };
			inline constexpr char kLS{ 'i' };
			inline constexpr char kL2{ 'j' };
			inline constexpr char kR3{ 'l' };
			inline constexpr char kR1{ 'm' };
			inline constexpr char kRS{ 'n' };
			inline constexpr char kR2{ 'o' };
			inline constexpr char kStart{ 'p' };
			inline constexpr char kSelect{ 'z' };
		}

		namespace DPad
		{
			inline constexpr char kNone{ 's' };
			inline constexpr char kLeft{ 't' };
			inline constexpr char kRight{ 'u' };
			inline constexpr char kDown{ 'v' };
			inline constexpr char kUp{ 'w' };
		}
	}
}
