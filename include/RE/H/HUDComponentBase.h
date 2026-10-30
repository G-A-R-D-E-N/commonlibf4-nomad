#pragma once

#include "RE/B/BSGFxShaderFXTarget.h"
#include "RE/B/BSTArray.h"
#include "RE/H/HUDModeInitParams.h"
#include "RE/H/HUDModeType.h"
#include "RE/H/HUDModes.h"

namespace RE
{
	class HUDDataBase;

	class __declspec(novtable) HUDComponentBase :
		public BSGFxShaderFXTarget  // 00
	{
	public:
		static constexpr auto RTTI{ RTTI::HUDComponentBase };
		static constexpr auto VTABLE{ VTABLE::HUDComponentBase };

		enum class FADE_STATE
		{
			kVisible = 0,
			kHidden = 1,
			kFadingIn = 2,
			kFadingOut = 3,
		};

		virtual ~HUDComponentBase();  // 00

		// add
		virtual bool ProcessHUDMessage(const HUDDataBase& a_data);                                // 02
		virtual void Reinitialize();                                                              // 03
		virtual void UpdateDisplayObject();                                                       // 04
		virtual void UpdateHUDMode(const BSTArray<HUDModeType, BSTArrayHeapAllocator>& a_modes);  // 05
		virtual void SetColor();                                                                  // 06
		virtual bool CanBeVisible() const;                                                        // 07
		virtual bool IsValidHUDMode() const;                                                      // 08

		void EnableWidgetDisplay()
		{
			using func_t = decltype(&HUDComponentBase::EnableWidgetDisplay);
			static REL::Relocation<func_t> func{ ID::HUDComponentBase::EnableWidgetDisplay };
			return func(this);
		}

		void DisableWidgetDisplay()
		{
			using func_t = decltype(&HUDComponentBase::DisableWidgetDisplay);
			static REL::Relocation<func_t> func{ ID::HUDComponentBase::DisableWidgetDisplay };
			return func(this);
		}

		void EnableWidgetDisplayMS(std::uint32_t a_durationMS)
		{
			using func_t = decltype(&HUDComponentBase::EnableWidgetDisplayMS);
			static REL::Relocation<func_t> func{ ID::HUDComponentBase::EnableWidgetDisplayMS };
			return func(this, a_durationMS);
		}

		void SetWidgetDisplayEnabled(bool a_enabled)
		{
			using func_t = decltype(&HUDComponentBase::SetWidgetDisplayEnabled);
			static REL::Relocation<func_t> func{ ID::HUDComponentBase::SetWidgetDisplayEnabled };
			return func(this, a_enabled);
		}

		bool IsWidgetDisplayEnabled() const
		{
			using func_t = decltype(&HUDComponentBase::IsWidgetDisplayEnabled);
			static REL::Relocation<func_t> func{ ID::HUDComponentBase::IsWidgetDisplayEnabled };
			return func(this);
		}

		void SetDisplayWarningColor(bool a_useWarningColor)
		{
			using func_t = decltype(&HUDComponentBase::SetDisplayWarningColor);
			static REL::Relocation<func_t> func{ ID::HUDComponentBase::SetDisplayWarningColor };
			return func(this, a_useWarningColor);
		}

		// members
		std::uint64_t widgetDisplayStartTime;    // B0 - appTimer.lastTime snapshot when EnableWidgetDisplayMS was called
		std::uint64_t widgetDisplayEndTime;      // B8 - appTimer.lastTime deadline for timed widget display
		bool          widgetDisplayTimedActive;  // C0 - true while a EnableWidgetDisplayMS timer is running
												 // 7 bytes padding
		HUDModes   hudModes;                     // C8
		float      fadePerSecond;                // E8 - alpha units/sec used by UpdateDisplayObject's fade animation
		FADE_STATE fadeState;                    // EC
		bool       flashElementsRegistered;      // F0 - set by OnRegisterFlashElements (not yet exposed here)
		bool       widgetDisplayEnabled;         // F1
		bool       displayWarningColor;          // F2
												 // 5 bytes padding
	};
	static_assert(sizeof(HUDComponentBase) == 0xF8);
}
