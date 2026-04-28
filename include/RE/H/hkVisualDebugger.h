#pragma once

#include "RE/H/hkArray.h"
#include "RE/H/hkBool.h"
#include "RE/H/hkReferencedObject.h"
#include "RE/H/hkStopwatch.h"

namespace RE
{
	class hkClass;
	class hkProcessContext;
	class hkSocket;
	class hkStringPtr;
	class hkVisualDebuggerClient;
	class hkVisualDebuggerTrackedObject;
	class hkVtableClassRegistry;

	class hkVisualDebugger :
		public hkReferencedObject
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hkVisualDebugger };
		inline static constexpr auto VTABLE{ VTABLE::hkVisualDebugger };

		using TrackCallback = void (*)(void*, const hkClass*, hkBool, std::uint64_t, void*);

		hkVisualDebugger(const hkArray<hkProcessContext*>& a_contexts, const hkVtableClassRegistry* a_classReg = nullptr)
		{
			using func_t = void (*)(hkVisualDebugger*, const hkArray<hkProcessContext*>&, const hkVtableClassRegistry*);
			static REL::Relocation<func_t> func{ ID::hkVisualDebugger::ctor };
			func(this, a_contexts, a_classReg);
		}

		// add
		virtual void Step([[maybe_unused]] float a_frameTime) {}  // 04
		virtual void PollForNewClients() {}                       // 05

		void AddContext(hkProcessContext* a_context)
		{
			using func_t = decltype(&hkVisualDebugger::AddContext);
			static REL::Relocation<func_t> func{ ID::hkVisualDebugger::AddContext };
			func(this, a_context);
		}

		void AddDefaultProcess(const char* a_name)
		{
			using func_t = decltype(&hkVisualDebugger::AddDefaultProcess);
			static REL::Relocation<func_t> func{ ID::hkVisualDebugger::AddDefaultProcess };
			func(this, a_name);
		}

		void Serve(const std::uint32_t a_port = 25001)
		{
			using func_t = decltype(&hkVisualDebugger::Serve);
			static REL::Relocation<func_t> func{ ID::hkVisualDebugger::Serve };
			func(this, a_port);
		}

		void Shutdown()
		{
			using func_t = decltype(&hkVisualDebugger::Shutdown);
			static REL::Relocation<func_t> func{ ID::hkVisualDebugger::Shutdown };
			func(this);
		}

		// members
		hkSocket*                              server;                     // 0x10
		bool                                   suppressPollForNewClients;  // 0x18
		hkArray<hkVisualDebuggerClient>        clients;                    // 0x20
		hkArray<hkProcessContext*>             contexts;                   // 0x30
		hkArray<hkVisualDebuggerTrackedObject> trackedObjects;             // 0x40
		hkArray<TrackCallback>                 trackCallbacks;             // 0x50
		hkArray<void*>                         trackCallbackHandles;       // 0x60
		const hkVtableClassRegistry*           classReg;                   // 0x70
		hkArray<hkStringPtr>                   defaultProcesses;           // 0x78
		hkArray<hkStringPtr>                   requiredProcesses;          // 0x88
		hkBool                                 timingFrame;                // 0x98
		hkStopwatch                            frameTimer;                 // 0xA0
		hkBool                                 overrideFrameTimeIfZero;    // 0xD0
	};
	static_assert(sizeof(hkVisualDebugger) == 0xD8);
}
