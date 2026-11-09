#pragma once

#include "RE/B/BSTEvent.h"
#include "Scaleform/P/Ptr.h"
#include "Scaleform/R/Render_ContextImpl_DisplayHandle.h"
#include "Scaleform/R/Render_TreeRoot.h"

namespace Scaleform::Render
{
	class HAL;
	class Renderer2D;
	class RenderTarget;
	class TextureManager;
}

namespace RE
{
	class SFRendererInitializedEvent;

	class BSScaleformRenderer :
		public BSTEventSource<SFRendererInitializedEvent>  // 000
	{
	public:
		void Initialize()
		{
			using func_t = decltype(&BSScaleformRenderer::Initialize);
			static REL::Relocation<func_t> func{ ID::BSScaleformRenderer::Initialize };
			return func(this);
		}

		void BeginFrame()
		{
			using func_t = decltype(&BSScaleformRenderer::BeginFrame);
			static REL::Relocation<func_t> func{ ID::BSScaleformRenderer::BeginFrame };
			func(this);
		}

		void EndFrame()
		{
			using func_t = decltype(&BSScaleformRenderer::EndFrame);
			static REL::Relocation<func_t> func{ ID::BSScaleformRenderer::EndFrame };
			func(this);
		}

		void BeginScene()
		{
			using func_t = decltype(&BSScaleformRenderer::BeginScene);
			static REL::Relocation<func_t> func{ ID::BSScaleformRenderer::BeginScene };
			func(this);
		}

		void EndScene()
		{
			using func_t = decltype(&BSScaleformRenderer::EndScene);
			static REL::Relocation<func_t> func{ ID::BSScaleformRenderer::EndScene };
			func(this);
		}

		bool DisplayMovie(Scaleform::Render::ContextImpl::DisplayHandle<Scaleform::Render::TreeRoot>& a_displayHandle,
			bool a_renderMenu)
		{
			using func_t = decltype(&BSScaleformRenderer::DisplayMovie);
			static REL::Relocation<func_t> func{ ID::BSScaleformRenderer::DisplayMovie };
			return func(this, a_displayHandle, a_renderMenu);
		}

		void SetCurrentRenderTarget()
		{
			using func_t = decltype(&BSScaleformRenderer::SetCurrentRenderTarget);
			static REL::Relocation<func_t> func{ ID::BSScaleformRenderer::SetCurrentRenderTarget };
			func(this);
		}

		void ClearRenderTargets()
		{
			using func_t = decltype(&BSScaleformRenderer::ClearRenderTargets);
			static REL::Relocation<func_t> func{ ID::BSScaleformRenderer::ClearRenderTargets };
			func(this);
		}

		// members
		Scaleform::Ptr<Scaleform::Render::Renderer2D>     renderer;            // 058
		Scaleform::Ptr<Scaleform::Render::HAL>            renderConfig;        // 060
		Scaleform::Ptr<Scaleform::Render::TextureManager> textureManager;      // 068
		Scaleform::Render::RenderTarget*                  renderTargets[100];  // 070
		bool                                              initialized;         // 390
	};
	static_assert(sizeof(BSScaleformRenderer) == 0x398);
}
