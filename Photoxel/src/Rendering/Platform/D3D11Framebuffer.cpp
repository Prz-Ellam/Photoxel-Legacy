#include "fxpch.h"
#include "D3D11Framebuffer.h"
#include "Core/Core.h"
#include "D3D11Context.h"

namespace Photoxel
{
	D3D11Framebuffer::D3D11Framebuffer(uint32_t width, uint32_t height)
	{
		D3D11_TEXTURE2D_DESC textureDesc = {};
		HRESULT hr;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

		textureDesc.Width = width;
		textureDesc.Height = height;
		textureDesc.MipLevels = 1u;
		textureDesc.ArraySize = 1u;
		textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		textureDesc.SampleDesc.Count = 1u;
		textureDesc.SampleDesc.Quality = 0u;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		textureDesc.CPUAccessFlags = 0;
		textureDesc.MiscFlags = 0;

		hr = D3D11Context::GetDevice()->CreateTexture2D(&textureDesc, NULL, &m_Texture);
		if (FAILED(hr))
		{
			return;
		}

		renderTargetViewDesc.Format = textureDesc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		hr = D3D11Context::GetDevice()->CreateRenderTargetView(m_Texture, &renderTargetViewDesc, &m_RenderTargetView);

		if (FAILED(hr)) {
			return;
		}

		shaderResourceViewDesc.Format = textureDesc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;

		// Create the shader resource view.
		hr = D3D11Context::GetDevice()->CreateShaderResourceView(m_Texture, &shaderResourceViewDesc, &m_ShaderResourceView);

		if (FAILED(hr)) {
			return;
		}

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		samplerDesc.MipLODBias = 0.0f;
		samplerDesc.MinLOD = 0.0f;
		samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

		hr = D3D11Context::GetDevice()->CreateSamplerState(&samplerDesc, &m_Sampler);
	}
	void D3D11Framebuffer::BindFrameBuffer()
	{
		D3D11Context::GetDeviceContext()->OMSetRenderTargets(1, &m_RenderTargetView, nullptr);
	}

	void D3D11Framebuffer::Clear(float r, float g, float b, float a)
	{
		FLOAT rgba[] = { r, g, b, a };
		D3D11Context::GetDeviceContext()->ClearRenderTargetView(m_RenderTargetView, rgba);
	}

	const void* D3D11Framebuffer::GetEntityHandler() const
	{
		return m_ShaderResourceView;
	}
}