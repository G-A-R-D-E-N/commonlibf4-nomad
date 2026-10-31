#pragma once

#include "RE/H/hkbEvent.h"
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
		hkbEvent     eventToSendWhenStateOrTransitionChanges;  // 0x88
		void*        startStateIdSelector;                     // 0xA0
		std::int32_t startStateId;                             // 0xA8
		std::int32_t returnToPreviousStateEventId;             // 0xAC
		std::int32_t randomTransitionEventId;                  // 0xB0
		std::int32_t transitionToNextHigherStateEventId;       // 0xB4
		std::int32_t transitionToNextLowerStateEventId;        // 0xB8
		std::int32_t syncVariableIndex;                        // 0xBC
		std::int32_t currentStateId;                           // 0xC0
		bool         wrapAroundStateId;                        // 0xC4
		std::int8_t  maxSimultaneousTransitions;               // 0xC5
		std::int8_t  startStateMode;                           // 0xC6
		std::int8_t  selfTransitionMode;                       // 0xC7
		bool         isActive;                                 // 0xC8
		std::uint8_t padC9[7];                                 // 0xC9
		hkArray<StateInfo*> states;                            // 0xD0
		void*        wildcardTransitions;                      // 0xE0
		void*        stateIdToIndexMap;                        // 0xE8
		hkArray<ActiveTransitionInfo> activeTransitions;       // 0xF0
		hkArray<std::uint8_t> transitionFlags;                 // 0x100
		hkArray<std::uint8_t> wildcardTransitionFlags;         // 0x110
		hkArray<void*> delayedTransitions;                     // 0x120
		float        timeInState;                              // 0x130
		float        lastLocalTime;                            // 0x134
		std::int32_t previousStateId;                          // 0x138
		std::int32_t nextStartStateIndexOverride;              // 0x13C
		bool         stateOrTransitionChanged;                 // 0x140
		bool         echoNextUpdate;                           // 0x141
		bool         hasEventlessWildcardTransitions;          // 0x142
		std::uint8_t pad143;                                   // 0x143
		std::uint16_t unk144;                                  // 0x144
		std::uint8_t pad146[2];                                // 0x146
	};
	static_assert(sizeof(hkbStateMachine) == 0x148);
}
