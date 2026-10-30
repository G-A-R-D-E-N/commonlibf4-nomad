#pragma once

#include "RE/N/NiPoint3.h"
#include "RE/N/NiPointer.h"
#include "RE/T/ThirdPersonState.h"

namespace RE
{
	class Actor;
	class BGSCameraShot;
	class ImageSpaceModifierInstance;
	class TESObjectREFR;

	class __declspec(novtable) DialogueCameraState :
		public ThirdPersonState
	{
	public:
		static constexpr auto RTTI{ RTTI::DialogueCameraState };
		static constexpr auto VTABLE{ VTABLE::DialogueCameraState };
		static constexpr auto STATE{ CameraStates::kDialogue };

		float GetCurrentPlaybackTimer() const { return currentPlaybackTimer; }

		const NiPointer<TESObjectREFR>& QEventCamRef() const { return eventCamRef; }
		const NiPointer<TESObjectREFR>& QTarget() const { return target; }
		const NiPointer<TESObjectREFR>& QListener() const { return listener; }
		const NiPointer<TESObjectREFR>& QPrimary() const { return primary; }
		void                            SetCameraTarget(const NiPointer<TESObjectREFR>& a_target) { target = a_target; }

		void SetCameraRotation(float a_x, float a_y, float a_z)
		{
			rotation.x = a_x;
			rotation.y = a_y;
			rotation.z = a_z;
		}

		void SetCameraTranslation(const NiPoint3& a_translation) { translation = a_translation; }

		bool QAllow1stP() const { return allow1stP; }
		void SetAllow1stP(bool a_allow) { allow1stP = a_allow; }
		bool QEnteredFrom1stP() const { return enteredFrom1stP; }
		void SetEnteredFrom1stP(bool a_entered) { enteredFrom1stP = a_entered; }

		// members
		std::uint64_t               unk138;                 // 138
		std::uint64_t               unk140;                 // 140
		BGSCameraShot*              currentCameraShot;      // 148 - drives GetRotation when set
		std::uint64_t               unk150;                 // 150 - reset together in Begin(), likely camera-shot-list state
		std::uint64_t               unk158;                 // 158
		std::uint64_t               unk160;                 // 160
		std::uint64_t               unk168;                 // 168
		ImageSpaceModifierInstance* imageSpaceMod;          // 170 - Stop()'d and cleared in Begin()
		NiPointer<Actor>            playerRef;              // 178 - default GetRotation target when no camera shot/explicit target
		NiPointer<TESObjectREFR>    target;                 // 180
		NiPointer<TESObjectREFR>    speaker;                // 188
		NiPointer<TESObjectREFR>    listener;               // 190
		NiPointer<TESObjectREFR>    primary;                // 198
		NiPointer<TESObjectREFR>    eventCamRef;            // 1A0
		std::uint64_t               unk1A8;                 // 1A8 - intrusive-refcounted pointer, type unconfirmed
		std::uint64_t               unk1B0;                 // 1B0 - vtable-refcounted pointer, type unconfirmed
		std::uint64_t               unk1B8;                 // 1B8 - vtable-refcounted pointer, type unconfirmed
		float                       currentPlaybackTimer;   // 1C0
		float                       unk1C4;                 // 1C4
		std::uint64_t               unk1C8;                 // 1C8
		std::int32_t                unk1D0;                 // 1D0 - reset to 1 alongside unk1D4 in Begin() when playOpening is false
		std::int32_t                unk1D4;                 // 1D4
		std::uint32_t               numCameraShootActions;  // 1D8 - see UpdateNumCameraShootActions()
		std::uint32_t               unk1DC;                 // 1DC
		std::uint64_t               unk1E0;                 // 1E0
		std::uint32_t               unk1E8;                 // 1E8 - not explicitly zeroed by the constructor
		// the constructor zeroes 0x1EC..0x1F3 with a single unaligned 8-byte store; split into two
		// 4-byte members because a std::uint64_t here would be padded up to 0x1F0 and shift every
		// following member (and the shift is invisible to sizeof, being absorbed by tail padding)
		std::uint32_t unk1EC;           // 1EC
		std::uint32_t unk1F0;           // 1F0
		NiPoint3      rotation;         // 1F4 - set via SetCameraRotation
		NiPoint3      translation;      // 200 - set via SetCameraTranslation
		NiPoint3      locationOnActor;  // 20C - cached from Actor::GetLocationOnActor(player) in Begin()
		bool          unk218;           // 218
		bool          playOpening;      // 219
		bool          unk21A;           // 21A
		bool          enteredFrom1stP;  // 21B
		bool          allow1stP;        // 21C - defaults to true
		bool          unk21D;           // 21D
	};
	// PlayerCamera::SetCameraRoot allocates this class at a literal 0x220 bytes
	static_assert(sizeof(DialogueCameraState) == 0x220);
}
