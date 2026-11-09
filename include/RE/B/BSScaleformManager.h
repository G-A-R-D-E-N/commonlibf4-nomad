#pragma once

#include "RE/B/BSScaleformTranslator.h"
#include "RE/B/BSStringT.h"
#include "RE/B/BSTEvent.h"
#include "RE/B/BSTSingleton.h"
#include "Scaleform/G/GFx_Loader.h"
#include "Scaleform/G/GFx_Movie.h"
#include "Scaleform/P/Ptr.h"

namespace Scaleform::GFx
{
	class DrawTextManager;
	class FunctionHandler;
	class Value;
}

namespace RE
{
	class BSScaleformImageLoader;
	class BSScaleformRenderer;
	class IMenu;
	class SFRendererInitializedEvent;

	class __declspec(novtable) BSScaleformManager :
		public BSTEventSink<SFRendererInitializedEvent>,  // 00
		public BSTSingletonSDM<BSScaleformManager>        // 08
	{
	public:
		static constexpr auto RTTI{ RTTI::BSScaleformManager };
		static constexpr auto VTABLE{ VTABLE::BSScaleformManager };

		using ScaleModeType = Scaleform::GFx::Movie::ScaleModeType;

		[[nodiscard]] static BSScaleformManager* GetSingleton()
		{
			static REL::Relocation<BSScaleformManager**> singleton{ ID::BSScaleformManager::Singleton };
			return *singleton;
		}

		BSScaleformTranslator* GetTranslator() const
		{
			return loader->GetStateAddRef<BSScaleformTranslator>();
		}

		bool IsNameValid(const char* a_name)
		{
			using func_t = decltype(&BSScaleformManager::IsNameValid);
			static REL::Relocation<func_t> func{ ID::BSScaleformManager::IsNameValid };
			return func(this, a_name);
		}

		BSEventNotifyControl ProcessEvent(const SFRendererInitializedEvent& a_event,
			BSTEventSource<SFRendererInitializedEvent>* a_source) override
		{
			using func_t = decltype(&BSScaleformManager::ProcessEvent);
			static REL::Relocation<func_t> func{ ID::BSScaleformManager::ProcessEvent };
			return func(this, a_event, a_source);
		}

		bool LoadMovieDef(Scaleform::Ptr<Scaleform::GFx::MovieDef>& a_movieDef, const char* a_filePath)
		{
			using func_t = decltype(&BSScaleformManager::LoadMovieDef);
			static REL::Relocation<func_t> func{ ID::BSScaleformManager::LoadMovieDef };
			return func(this, a_movieDef, a_filePath);
		}

		bool LoadMovie(
			IMenu&                                 a_menu,
			Scaleform::Ptr<Scaleform::GFx::Movie>& a_movie,
			const char*                            a_menuName,
			const char*                            a_menuObjPath = nullptr,
			ScaleModeType                          a_scaleMode = ScaleModeType::kShowAll,
			float                                  a_backgroundAlpha = 0.0F)
		{
			using func_t = decltype(&BSScaleformManager::LoadMovie);
			static REL::Relocation<func_t> func{ ID::BSScaleformManager::LoadMovie };
			return func(this, a_menu, a_movie, a_menuName, a_menuObjPath, a_scaleMode, a_backgroundAlpha);
		}

		bool LoadMovieEx(
			IMenu&           a_menu,
			std::string_view a_filePath,
			std::string_view a_menuObjPath = ""sv,
			ScaleModeType    a_scaleMode = ScaleModeType::kShowAll,
			float            a_backgroundAlpha = 0.0F);

		// The file path has to be relative to "Data/Interface", with the file extension.
		static bool LoadAsset(
			const IMenu&                     a_menu,
			const char*                      a_filePath,
			const char*                      a_rootVarPath,
			Scaleform::GFx::FunctionHandler* a_onComplete = nullptr,
			Scaleform::GFx::FunctionHandler* a_onError = nullptr);

		static bool UnloadAsset(
			const IMenu&                     a_menu,
			const char*                      a_assetVarPath,
			Scaleform::GFx::FunctionHandler* a_onUnload = nullptr);

		static bool UnloadAsset(
			const IMenu&                     a_menu,
			const Scaleform::GFx::Value&     a_assetValue,
			Scaleform::GFx::FunctionHandler* a_onUnload = nullptr);

		// members
		Scaleform::GFx::Loader*                         loader;          // 10
		BSScaleformRenderer*                            renderer;        // 18
		Scaleform::Ptr<Scaleform::GFx::DrawTextManager> textManager;     // 20
		Scaleform::Ptr<BSScaleformImageLoader>          imageLoader;     // 28
		BSString                                        validNameChars;  // 30

	private:
		[[nodiscard]] bool GetMovieFilename(char const* a_menuName, BSStaticStringT<260>& a_filePath)
		{
			using func_t = decltype(&BSScaleformManager::GetMovieFilename);
			static REL::Relocation<func_t> func{ ID::BSScaleformManager::GetMovieFilename };
			return func(this, a_menuName, a_filePath);
		}

		void InitMovieViewport(Scaleform::GFx::Movie& a_movie, const float a_dynamicWidthRatio, const float a_dynamicHeightRatio)
		{
			using func_t = decltype(&BSScaleformManager::InitMovieViewport);
			static REL::Relocation<func_t> func{ ID::BSScaleformManager::InitMovieViewport };
			return func(this, a_movie, a_dynamicWidthRatio, a_dynamicHeightRatio);
		}
	};
	static_assert(sizeof(BSScaleformManager) == 0x40);
}
