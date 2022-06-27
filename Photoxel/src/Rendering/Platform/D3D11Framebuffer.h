#pragma once
#ifndef _PHOTOXEL_D3D11_FRAMEBUFFER_H_
#define _PHOTOXEL_D3D11_FRAMEBUFFER_H_

#include <d3d11.h>
#include <wrl.h>

namespace Photoxel
{
	class D3D11Framebuffer
	{
	public:
		D3D11Framebuffer(uint32_t width, uint32_t height);
		D3D11Framebuffer(const D3D11Framebuffer& other) = default;
		D3D11Framebuffer(D3D11Framebuffer&& other) noexcept = default;

		void BindFrameBuffer();

		void Clear(float r, float g, float b, float a);
		//void UnbindFramebuffer();

		const void* GetEntityHandler() const;

	private:
		ID3D11Texture2D* m_Texture;
		ID3D11RenderTargetView* m_RenderTargetView;
		ID3D11ShaderResourceView* m_ShaderResourceView;
		ID3D11SamplerState* m_Sampler;
	};
}

#endif
