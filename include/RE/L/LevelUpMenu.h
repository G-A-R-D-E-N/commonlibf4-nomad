#pragma once

#include "RE/B/BSGFxShaderFXTarget.h"
#include "RE/B/BSScaleformExternalTexture.h"
#include "RE/B/BSSoundHandle.h"
#include "RE/B/BSTEvent.h"
#include "RE/G/GameMenuBase.h"
#include "RE/P/PerkAdded.h"

namespace RE
{
	class __declspec(novtable) LevelUpMenu :
		public GameMenuBase,                   // 00
		public BSTEventSink<PerkAdded::Event>  // E0
	{
	public:
		static constexpr auto RTTI{ RTTI::LevelUpMenu };
		static constexpr auto VTABLE{ VTABLE::LevelUpMenu };
		static constexpr auto MENU_NAME{ "LevelUpMenu"sv };

		virtual ~LevelUpMenu();  // 00

		// override (GameMenuBase)
		virtual void               Call(const Params&) override;                                    // 01
		virtual void               MapCodeObjectFunctions() override;                               // 02
		virtual UI_MESSAGE_RESULTS ProcessMessage(UIMessage& a_message) override;                   // 03
		virtual void               AdvanceMovie(float a_timeDelta, std::uint64_t a_time) override;  // 04
		virtual void               PreDisplay() override;                                           // 05

		// override (BSTEventSink<PerkAdded::Event>)
		virtual BSEventNotifyControl ProcessEvent(const PerkAdded::Event& a_event, BSTEventSource<PerkAdded::Event>* a_source) override;  // 01

		// members
		Scaleform::GFx::Value                gridValue;                  // E8
		std::unique_ptr<BSGFxShaderFXTarget> perkInfoFilter;             // 108
		std::unique_ptr<BSGFxShaderFXTarget> selectionRectFilter;        // 110
		std::unique_ptr<BSGFxShaderFXTarget> xpMeterFilter;              // 118
		BSScaleformExternalTexture           perkTexture0;               // 120
		BSScaleformExternalTexture           perkTexture1;               // 138
		BSScaleformExternalTexture           perkTexture2;               // 150
		BSScaleformExternalTexture           perkTexture3;               // 168
		BSSoundHandle                        levelUpSound;               // 180
		bool                                 hasLeveledUp{ false };      // 188 - TODO
		bool                                 autosaveDeferred{ false };  // 189 - TODO
		bool                                 pendingAutosave{ false };   // 18A - TODO
		std::byte                            unk18B[0xD];                // 18B - TODO
	};
	static_assert(sizeof(LevelUpMenu) == 0x198);
}
