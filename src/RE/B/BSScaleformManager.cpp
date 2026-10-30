#include "RE/B/BSScaleformManager.h"

#include "RE/B/BSSystemFileStreamer.h"
#include "RE/I/IMenu.h"
#include "RE/S/Setting.h"
#include "Scaleform/G/GFx_ASMovieRootBase.h"
#include "Scaleform/G/GFx_FunctionHandler.h"
#include "Scaleform/G/GFx_Loader.h"
#include "Scaleform/G/GFx_MovieDef.h"
#include "Scaleform/G/GFx_Value.h"
#include "Scaleform/P/Ptr.h"

namespace RE
{
	bool BSScaleformManager::LoadMovieEx(
		IMenu&           a_menu,
		std::string_view a_filePath,
		std::string_view a_menuObjPath,
		ScaleModeType    a_scaleMode,
		float            a_backgroundAlpha)
	{
		static REL::Relocation<SettingT<INISettingCollection>*> fileUncacheOnMenuOpen{ ID::BSScaleformManager::FileUncacheOnMenuOpen };
		if (fileUncacheOnMenuOpen && fileUncacheOnMenuOpen->GetBinary()) {
			BSSystemFileStreamer::UncacheAll(true);
		}

		REX::TEnumSet loadConstants{
			Scaleform::GFx::Loader::LoadConstants::kKeepBindData,
			Scaleform::GFx::Loader::LoadConstants::kWaitFrame1
		};

		const auto movieDef = Scaleform::Ptr{ loader->CreateMovie(a_filePath.data(), loadConstants.get()) };
		if (!movieDef) {
			return false;
		}
		movieDef->Release();

		auto& movie = a_menu.uiMovie;
		movie.reset(movieDef->CreateInstance(true));
		if (!movie) {
			return false;
		}
		movie->Release();

		movie->SetViewScaleMode(a_scaleMode);
		movie->SetBackgroundAlpha(a_backgroundAlpha);
		a_menu.DoAdvanceMovie(0.0);
		if (!a_menuObjPath.empty()) {
			a_menu.SetMenuCodeObject(*movie, a_menuObjPath);
		}
		a_menu.RefreshPlatform();
		InitMovieViewport(*movie, 1.0F, 1.0F);
		a_menu.OnSetSafeRect();

		return true;
	}

	bool BSScaleformManager::LoadAsset(
		const IMenu&                     a_menu,
		const char*                      a_filePath,
		const char*                      a_rootVarPath,
		Scaleform::GFx::FunctionHandler* a_onComplete,
		Scaleform::GFx::FunctionHandler* a_onError)
	{
		if (!a_filePath || *a_filePath == '\0' || !a_rootVarPath || *a_rootVarPath == '\0') {
			return false;
		}

		auto menuMovie = a_menu.uiMovie;
		if (!menuMovie) {
			return false;
		}

		auto menuRoot = menuMovie->asMovieRoot;
		if (!menuRoot) {
			return false;
		}

		Scaleform::GFx::Value gfxRootPath;
		if (!menuRoot->GetVariable(std::addressof(gfxRootPath), a_rootVarPath) || !gfxRootPath.IsDisplayObject()) {
			return false;
		}

		Scaleform::GFx::Value gfxLoader;
		menuRoot->CreateObject(std::addressof(gfxLoader), "flash.display.Loader");
		if (!gfxLoader.IsDisplayObject()) {
			return false;
		}

		if (a_onComplete || a_onError) {
			Scaleform::GFx::Value gfxContentLoaderInfo;
			if (!gfxLoader.GetMember("contentLoaderInfo", std::addressof(gfxContentLoaderInfo)) || !gfxContentLoaderInfo.IsObject()) {
				return false;
			}

			if (a_onComplete) {
				std::array<Scaleform::GFx::Value, 2> gfxOnCompleteArgs;
				menuRoot->CreateString(std::addressof(gfxOnCompleteArgs[0]), "complete");
				menuRoot->CreateFunction(std::addressof(gfxOnCompleteArgs[1]), a_onComplete);

				if (!gfxContentLoaderInfo.Invoke("addEventListener", gfxOnCompleteArgs)) {
					return false;
				}

				// Make it a weak reference.
				a_onComplete->Release();
			}

			if (a_onError) {
				std::array<Scaleform::GFx::Value, 2> gfxOnErrorArgs;
				menuRoot->CreateString(std::addressof(gfxOnErrorArgs[0]), "ioError");
				menuRoot->CreateFunction(std::addressof(gfxOnErrorArgs[1]), a_onError);

				if (!gfxContentLoaderInfo.Invoke("addEventListener", gfxOnErrorArgs)) {
					return false;
				}

				std::array<Scaleform::GFx::Value, 2> gfxOnSecurityErrorArgs;
				menuRoot->CreateString(std::addressof(gfxOnSecurityErrorArgs[0]), "securityError");
				menuRoot->CreateFunction(std::addressof(gfxOnSecurityErrorArgs[1]), a_onError);

				if (!gfxContentLoaderInfo.Invoke("addEventListener", gfxOnSecurityErrorArgs)) {
					return false;
				}

				// Make it a weak reference.
				a_onError->Release();
			}
		}

		std::array<Scaleform::GFx::Value, 1> gfxRootPathAddChildArgs{ gfxLoader };
		if (!gfxRootPath.Invoke("addChild", gfxRootPathAddChildArgs)) {
			return false;
		}

		Scaleform::GFx::Value gfxFilePath;
		menuRoot->CreateString(std::addressof(gfxFilePath), a_filePath);

		std::array<Scaleform::GFx::Value, 1> gfxUrlRequestArgs{ gfxFilePath };
		Scaleform::GFx::Value                gfxUrlRequest;
		menuRoot->CreateObject(std::addressof(gfxUrlRequest), "flash.net.URLRequest", gfxUrlRequestArgs.data(), static_cast<std::uint32_t>(gfxUrlRequestArgs.size()));
		if (!gfxUrlRequest.IsObject()) {
			return false;
		}

		std::array<Scaleform::GFx::Value, 1> gfxLoaderLoadArgs{ gfxUrlRequest };
		if (!gfxLoader.Invoke("load", gfxLoaderLoadArgs)) {
			return false;
		}

		return true;
	}

	bool BSScaleformManager::UnloadAsset(
		const IMenu&                     a_menu,
		const char*                      a_assetVarPath,
		Scaleform::GFx::FunctionHandler* a_onUnload)
	{
		if (!a_assetVarPath || *a_assetVarPath == '\0') {
			return false;
		}

		auto menuMovie = a_menu.uiMovie;
		if (!menuMovie) {
			return false;
		}

		auto menuRoot = menuMovie->asMovieRoot;
		if (!menuRoot) {
			return false;
		}

		Scaleform::GFx::Value gfxAsset;
		if (!menuRoot->GetVariable(std::addressof(gfxAsset), a_assetVarPath) || !gfxAsset.IsDisplayObject()) {
			return false;
		}

		return UnloadAsset(a_menu, gfxAsset, a_onUnload);
	}

	bool BSScaleformManager::UnloadAsset(
		const IMenu&                     a_menu,
		const Scaleform::GFx::Value&     a_assetValue,
		Scaleform::GFx::FunctionHandler* a_onUnload)
	{
		if (!a_assetValue.IsDisplayObject()) {
			return false;
		}

		auto menuMovie = a_menu.uiMovie;
		if (!menuMovie) {
			return false;
		}

		auto menuRoot = menuMovie->asMovieRoot;
		if (!menuRoot) {
			return false;
		}

		Scaleform::GFx::Value gfxLoaderInfo;
		if (!a_assetValue.GetMember("loaderInfo", std::addressof(gfxLoaderInfo)) || !gfxLoaderInfo.IsObject()) {
			return false;
		}

		Scaleform::GFx::Value gfxLoader;
		if (!gfxLoaderInfo.GetMember("loader", std::addressof(gfxLoader)) || !gfxLoader.IsDisplayObject()) {
			return false;
		}

		if (a_onUnload) {
			std::array<Scaleform::GFx::Value, 2> gfxOnUnloadArgs;
			menuRoot->CreateString(std::addressof(gfxOnUnloadArgs[0]), "unload");
			menuRoot->CreateFunction(std::addressof(gfxOnUnloadArgs[1]), a_onUnload);

			if (!gfxLoader.Invoke("addEventListener", gfxOnUnloadArgs)) {
				return false;
			}

			// Make it a weak reference.
			a_onUnload->Release();
		}

		if (!gfxLoader.Invoke("unload")) {
			return false;
		}

		return true;
	}
}
