#pragma once

#include "RE/B/BSInputEventReceiver.h"
#include "RE/B/BSSpinLock.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSingleton.h"
#include "RE/C/CalculateCompassMarkersFunctor.h"
#include "RE/C/ConditionBoyEvent.h"
#include "RE/H/HUDActiveEffectsModel.h"
#include "RE/H/HUDAmmoCountModel.h"
#include "RE/H/HUDDirectionalHitIndicatorDataModel.h"
#include "RE/H/HUDExplosivesDataModel.h"
#include "RE/H/HUDMessagesModel.h"
#include "RE/H/HUDNotificationsModel.h"
#include "RE/H/HUDPerkVaultBoyModel.h"
#include "RE/H/HUDRadiationModel.h"
#include "RE/H/HUDRolloverModel.h"
#include "RE/H/HUDTargetHealthModel.h"

namespace RE
{
	// Ghidra-confirmed (OG 1.10.163, AND independently re-confirmed on AE 1.11.221 and AE 1.11.240 -- all
	// three runtimes' HUDDataModel::HUDDataModel decompile to the identical sequence of sub-model constructor
	// calls at the identical offsets, and all three explicitly pass sizeof==0x13A0 to their allocator): the
	// nine sub-model members plus the compass functor and its spinlock sit at rolloverModel +0x18,
	// targetHealthModel +0x5C0, radiationModel +0x698, explosivesDataModel +0x910,
	// directionalHitIndicatorDataModel +0x968, ammoCountModel +0x9E0, messagesModel +0xA08,
	// perkVaultBoyModel +0xB68, notificationsModel +0xC40, activeEffectsModel +0xEC0, conditionBoy +0x1320,
	// compassMarkerFunctor +0x1340, compassMarkerArrayLock +0x1398 -- matching LucaDotGit's layout exactly
	// at every offset, including total size.
	class __declspec(novtable) HUDDataModel :
		public BSInputEventReceiver,          // 0000
		public BSTSingletonSDM<HUDDataModel>  // 0010
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDDataModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDDataModel };

		// override (BSInputEventReceiver)
		void PerformInputProcessing(const InputEvent* a_queueHead) override;  // 00

		// add
		virtual ~HUDDataModel();  // 01

		[[nodiscard]] static HUDDataModel* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<HUDDataModel**>{ ID::HUDDataModel::Singleton };
			return *SINGLETON;
		}

		// members
		HUDRolloverModel                       rolloverModel;                     // 0018
		HUDTargetHealthModel                   targetHealthModel;                 // 05C0
		HUDRadiationModel                      radiationModel;                    // 0698
		HUDExplosivesDataModel                 explosivesDataModel;               // 0910
		HUDDirectionalHitIndicatorDataModel    directionalHitIndicatorDataModel;  // 0968
		HUDAmmoCountModel                      ammoCountModel;                    // 09E0
		HUDMessagesModel                       messagesModel;                     // 0A08
		HUDPerkVaultBoyModel                   perkVaultBoyModel;                 // 0B68
		HUDNotificationsModel                  notificationsModel;                // 0C40
		HUDActiveEffectsModel                  activeEffectsModel;                // 0EC0
		BSTValueEventSource<ConditionBoyEvent> conditionBoy;                      // 1320
		CalculateCompassMarkersFunctor         compassMarkerFunctor;              // 1340
		mutable BSSpinLock                     compassMarkerArrayLock;            // 1398
	};
	static_assert(sizeof(HUDDataModel) == 0x13A0);
}
