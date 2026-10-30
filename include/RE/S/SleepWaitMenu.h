#pragma once

#include "RE/B/BGSAppPausedEvent.h"
#include "RE/B/BSInputEnableLayer.h"
#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/G/GameMenuBase.h"

namespace RE
{
	class __declspec(novtable) SleepWaitMenu :
		public GameMenuBase,                    // 00
		public BSTEventSink<BGSAppPausedEvent>  // E0
	{
	public:
		static constexpr auto RTTI{ RTTI::SleepWaitMenu };
		static constexpr auto VTABLE{ VTABLE::SleepWaitMenu };
		static constexpr auto MENU_NAME{ "SleepWaitMenu"sv };

		virtual ~SleepWaitMenu();  // 00

		// override (GameMenuBase)
		virtual void               Call(const Params&) override;                   // 01
		virtual void               MapCodeObjectFunctions() override;              // 02
		virtual UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;  // 03

		// override (BSTEventSink<BGSAppPausedEvent>)
		virtual BSEventNotifyControl ProcessEvent(const BGSAppPausedEvent& a_event, BSTEventSource<BGSAppPausedEvent>* a_source) override;  // 01

		// members
		ObjectRefHandle                      furnitureHandle;     // E8
		BSTSmartPointer<BSInputEnableLayer>  inputLayer;          // F0
		std::unique_ptr<BSGFxShaderFXTarget> bgRectFilter;        // F8
		float                                sleepTimer{ 0.0F };  // 100
		bool                                 waitMode{ false };   // 104 - TODO
		bool                                 isActive{ false };   // 105 - TODO
		bool                                 appPaused{ false };  // 106
	};
	static_assert(sizeof(SleepWaitMenu) == 0x108);
}
