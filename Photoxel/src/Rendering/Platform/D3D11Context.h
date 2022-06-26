#pragma once
#ifndef _PHOTOXEL_D3D11_CONTEXT_H_
#define _PHOTOXEL_D3D11_CONTEXT_H_

#include <d3d11.h>
#include <dxgi.h>

namespace Photoxel
{
	class Window;

	class D3D11Context
	{
	public:
		D3D11Context(Window* window);
		~D3D11Context();

		void Present();
	private:

		void CreateDevice();

		Window* m_Window;
		ID3D11Device* m_Device = nullptr;
		ID3D11DeviceContext* m_DeviceContext = nullptr;
		ID3D11RenderTargetView* m_RenderTargetView = nullptr;
		ID3D11DepthStencilView* m_DepthStencilView = nullptr;
		ID3D11DepthStencilState* m_DepthStencilState = nullptr;
		ID3D11RasterizerState* m_RasterizerState = nullptr;
		ID3D11BlendState* m_BlendState = nullptr;
		IDXGISwapChain* m_SwapChain = nullptr;
		ID3D11Texture2D* m_DepthStencil = nullptr;
	};
}

#endif
