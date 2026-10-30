#pragma once

#include "RE/B/BSPointerHandle.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSingleton.h"
#include "RE/B/BSTSmartPointer.h"
#include "RE/N/NiPoint3.h"
#include "RE/S/SCENE_ACTION_PLAYER_RESPONSE_TYPE.h"
#include "REX/FModule.h"

namespace RE
{
	class BSInputEnableLayer;
	class MenuOpenCloseEvent;
	class PositionPlayerEvent;

	class __declspec(novtable) MenuTopicManager :
		public BSTEventSink<MenuOpenCloseEvent>,   // 00
		public BSTEventSink<PositionPlayerEvent>,  // 08
		public BSTSingletonSDM<MenuTopicManager>   // 10
	{
	public:
		static constexpr auto RTTI{ RTTI::MenuTopicManager };
		static constexpr auto VTABLE{ VTABLE::MenuTopicManager };

		[[nodiscard]] static MenuTopicManager* GetSingleton()
		{
			static REL::Relocation<MenuTopicManager**> singleton{ ID::MenuTopicManager::Singleton };
			return *singleton;
		}

		bool IsCurrentSpeaker(const ObjectRefHandle& a_handle) const
		{
			return menuOpen && speaker == a_handle;
		}

		// AE-only until the OG selector prototype is independently verified.
		// Expanded dialogue options require a separate engine path.
		[[nodiscard]] bool TrySelectResponse(SCENE_ACTION_PLAYER_RESPONSE_TYPE a_responseType)
		{
			if (!REX::FModule::IsRuntimeAE()) {
				return false;
			}

			using func_t = decltype(&MenuTopicManager::TrySelectResponse);
			static REL::Relocation<func_t> func{ ID::MenuTopicManager::SelectResponse };
			func(this, a_responseType);
			return true;
		}

		// members
		ObjectRefHandle                     speaker;                       // 14
		ObjectRefHandle                     lastSpeaker;                   // 18
		BSTSmartPointer<BSInputEnableLayer> inputLayer;                    // 20
		float                               reLookTimer;                   // 28
		float                               notInMenuTimer;                // 2C
		float                               restartMenuOnFocus;            // 30
		float                               menuStart;                     // 34
		float                               buttonShowTimer;               // 38
		NiPoint3                            centerPoint;                   // 3C
		uint32_t                            numRefsInScene;                // 48
		bool                                menuOpen;                      // 4C
		bool                                shutMenu;                      // 4D
		bool                                canSkip;                       // 4E
		bool                                shuttingDown;                  // 4F
		bool                                menuSlow;                      // 50
		bool                                doneFOV;                       // 51
		bool                                leaveMenuOpen;                 // 52
		bool                                showHelpButton;                // 53
		bool                                needEnterDialogueAction;       // 54
		bool                                allowInput;                    // 55
		bool                                thirdPartyCameraReady;         // 56
		bool                                speechChallengeAlwaysSucceed;  // 57
		bool                                speechChallengeAlwaysFail;     // 58
		bool                                overSceneActor;                // 59
		bool                                forceCameraRotationStart;      // 5A
	};
	static_assert(sizeof(MenuTopicManager) == 0x60);
}
