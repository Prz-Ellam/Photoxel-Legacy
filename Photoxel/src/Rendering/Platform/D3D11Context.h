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
		friend class D3D11Renderer;
	public:
		D3D11Context(Window* window);
		~D3D11Context();

		void Present();

		static ID3D11Device* GetDevice()
		{
			return m_Device;
		}

		static ID3D11DeviceContext* GetDeviceContext()
		{
			return m_DeviceContext;
		}

		static ID3D11RenderTargetView*& GetRenderTargetView()
		{
			return m_RenderTargetView;
		}

		static ID3D11ShaderResourceView* GetShaderResourceView()
		{
			return m_ShaderResourceView;
		}

		static void InvalidateRenderTargetView(uint32_t width, uint32_t height);
	private:

		void CreateDevice();

		Window* m_Window;
		static ID3D11Device* m_Device;
		static ID3D11DeviceContext* m_DeviceContext;
		static ID3D11RenderTargetView* m_RenderTargetView;
		static ID3D11ShaderResourceView* m_ShaderResourceView;
		ID3D11DepthStencilView* m_DepthStencilView = nullptr;
		ID3D11DepthStencilState* m_DepthStencilState = nullptr;
		ID3D11RasterizerState* m_RasterizerState = nullptr;
		ID3D11BlendState* m_BlendState = nullptr;
		static IDXGISwapChain* m_SwapChain;
		ID3D11Texture2D* m_DepthStencil = nullptr;
	};
}

#endif
