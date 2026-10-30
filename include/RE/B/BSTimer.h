#pragma once

#include "REX/FModule.h"

namespace RE
{
	class BSTimer
	{
	public:
		struct RuntimeData
		{
			std::uint64_t firstTime;                      // 00
			std::uint64_t disabledLastTime;               // 08
			std::uint64_t disabledFirstTime;              // 10
			std::uint32_t disableCounter;                 // 18
			bool          useGlobalTimeMultiplierTarget;  // 1C
		};
		static_assert(sizeof(RuntimeData) == 0x20);

		[[nodiscard]] static constexpr std::size_t GetRuntimeSize(
			REX::FModule::Runtime a_runtime = REX::FModule::GetRuntimeIndex()) noexcept
		{
			return a_runtime == REX::FModule::Runtime::kAE ? 0x50 : 0x40;
		}

		[[nodiscard]] RuntimeData& GetRuntimeData(
			REX::FModule::Runtime a_runtime = REX::FModule::GetRuntimeIndex()) noexcept
		{
			return *reinterpret_cast<RuntimeData*>(
				reinterpret_cast<std::byte*>(this) + GetRuntimeSize(a_runtime) - sizeof(RuntimeData));
		}

		[[nodiscard]] const RuntimeData& GetRuntimeData(
			REX::FModule::Runtime a_runtime = REX::FModule::GetRuntimeIndex()) const noexcept
		{
			return *reinterpret_cast<const RuntimeData*>(
				reinterpret_cast<const std::byte*>(this) + GetRuntimeSize(a_runtime) - sizeof(RuntimeData));
		}

		// lastTime is at 0x18 on OG/NG; the member layout is AE-only.
		[[nodiscard]] std::uint64_t QLastTime(
			REX::FModule::Runtime a_runtime = REX::FModule::GetRuntimeIndex()) const noexcept
		{
			const auto offset = a_runtime == REX::FModule::Runtime::kAE ? 0x20 : 0x18;
			return *reinterpret_cast<const std::uint64_t*>(
				reinterpret_cast<const std::byte*>(this) + offset);
		}

		// Runtime-independent access to the tail fields. AE only has the extra 0x10-byte gap
		// between lastTime and firstTime that OG/NG lack: confirmed by disassembling
		// BSTimer::SetGlobalTimeMultiplier in both binaries -- OG (1.10.163) reads
		// useGlobalTimeMultiplierTarget at [this+0x3C], AE (1.11.240) reads it at [this+0x4C],
		// an exact 0x10 delta matching RuntimeData's anchor below. NG (1.10.984) groups with
		// OG (same 0x40 runtime size). Use these instead of the raw members past realDeltaMs --
		// the raw members reflect the AE-only shape.
		[[nodiscard]] std::uint64_t& QFirstTime() noexcept { return GetRuntimeData().firstTime; }
		[[nodiscard]] std::uint64_t& QDisabledLastTime() noexcept { return GetRuntimeData().disabledLastTime; }
		[[nodiscard]] std::uint64_t& QDisabledFirstTime() noexcept { return GetRuntimeData().disabledFirstTime; }
		[[nodiscard]] std::uint32_t& QDisableCounter() noexcept { return GetRuntimeData().disableCounter; }
		[[nodiscard]] bool&          QUseGlobalTimeMultiplierTargetField() noexcept { return GetRuntimeData().useGlobalTimeMultiplierTarget; }

		[[nodiscard]] static BSTimer* GetSingleton()
		{
			static REL::Relocation<BSTimer*> singleton{ ID::BSTimer::Singleton };
			return singleton.get();
		}

		[[nodiscard]] static float QGameDeltaTime()
		{
			static REL::Relocation<float*> value{ ID::BSTimer::QGameDeltaTime };
			return *value;
		}

		[[nodiscard]] static float QGlobalTimeMultiplier()
		{
			static REL::Relocation<float*> value{ ID::BSTimer::QGlobalTimeMultiplier };
			return *value;
		}

		[[nodiscard]] static float QGlobalTimeMultiplierTarget()
		{
			static REL::Relocation<float*> value{ ID::BSTimer::QGlobalTimeMultiplierTarget };
			return *value;
		}

		void SetGlobalTimeMultiplier(float a_mult, bool a_now)
		{
			using func_t = decltype(&BSTimer::SetGlobalTimeMultiplier);
			static REL::Relocation<func_t> func{ ID::BSTimer::SetGlobalTimeMultiplier };
			return func(this, a_mult, a_now);
		}

		// members
		std::int64_t  highPrecisionInitTime;          // 00
		float         clamp;                          // 08
		float         clampRemainder;                 // 0C
		float         delta;                          // 10
		float         realTimeDelta;                  // 14
		std::uint64_t realDeltaMs;                    // 18
		std::uint64_t lastTime;                       // 20
		std::uint64_t lastRawTime;                    // 28
		std::uint64_t firstTime;                      // 30
		std::uint64_t disabledLastTime;               // 38
		std::uint64_t disabledFirstTime;              // 40
		std::uint32_t disableCounter;                 // 48
		bool          useGlobalTimeMultiplierTarget;  // 4C
	};
	static_assert(sizeof(BSTimer) == 0x50);
}
