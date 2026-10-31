#pragma once

#include "RE/H/hkbGenerator.h"

namespace RE
{
	class hkbStateMachine :
		public hkbGenerator  // 0x88
	{
	public:
		class StateInfo :
			public hkbBindable  // 0x30
		{
		public:
			void*         listeners;               // 0x30
			std::uint8_t  pad38[8];                // 0x38
			void*         enterNotifyEvents;       // 0x40
			void*         exitNotifyEvents;        // 0x48
			void*         transitions;             // 0x50
			void*         generator;               // 0x58
			const char*   name;                    // 0x60
			std::int32_t  stateId;                 // 0x68
			float         probability;             // 0x6C
			bool          enable;                  // 0x70
			bool          hasEventlessTransitions; // 0x71
			std::uint8_t  pad72[6];                // 0x72
		};
		static_assert(sizeof(StateInfo) == 0x78);

		struct ActiveTransitionInfo
		{
			std::uint8_t pad00[0x1C];  // 0x00
			std::int32_t stateId;      // 0x1C
			void*        transition;   // 0x20
		};
		static_assert(sizeof(ActiveTransitionInfo) == 0x28);

		virtual ~hkbStateMachine();  // 00

		// members
		std::uint8_t pad88[0x38];                        // 0x88
		std::uint32_t currentStateId;                    // 0xC0
		std::uint8_t padC4[4];                           // 0xC4
		std::uint8_t padC8[8];                           // 0xC8
		hkArray<StateInfo*> states;                      // 0xD0
		void* wildcardTransitions;                       // 0xE0
		void* stateIdToIndexMap;                         // 0xE8
		hkArray<ActiveTransitionInfo> activeTransitions; // 0xF0
		hkArray<std::uint8_t> transitionFlags;           // 0x100
		hkArray<std::uint8_t> wildcardTransitionFlags;   // 0x110
		hkArray<void*> delayedTransitions;               // 0x120
		float timeInState;                               // 0x130
		float lastLocalTime;                             // 0x134
		std::int32_t previousStateId;                    // 0x138
		std::int32_t nextStartStateIndexOverride;        // 0x13C
		bool stateOrTransitionChanged;                   // 0x140
		bool echoNextUpdate;                             // 0x141
		bool hasEventlessWildcardTransitions;            // 0x142
		std::uint8_t pad143[5];                          // 0x143
	};
	static_assert(sizeof(hkbStateMachine) == 0x148);
}
