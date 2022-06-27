#include "fxpch.h"
#include "D3D11Texture2D.h"
#include "Rendering/Platform/D3D11Context.h"
#include "Core/Core.h"

namespace Photoxel
{
    D3D11Texture2D::D3D11Texture2D(const Image& image)
    {
        // Texture
        D3D11_TEXTURE2D_DESC desc = {};
        desc.Width = image.GetWidth();
        desc.Height = image.GetHeight();
        desc.MipLevels = 1u;
        desc.ArraySize = 1u;
        desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        desc.SampleDesc.Count = 1u;
        desc.SampleDesc.Quality = 0u;
        desc.Usage = D3D11_USAGE_DEFAULT;
        desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        desc.CPUAccessFlags = 0u;

        D3D11_SUBRESOURCE_DATA subResource;
        subResource.pSysMem = image.GetData();
        subResource.SysMemPitch = image.GetPitch();
        subResource.SysMemSlicePitch = 0;

        HRESULT result = D3D11Context::GetDevice()->CreateTexture2D(&desc, &subResource, &m_Texture);
        PX_ASSERT(SUCCEEDED(result), "No se pudo crear correctamente la textura");

        // Texture View
        D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
        ZeroMemory(&srvDesc, sizeof(srvDesc));
        srvDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
        srvDesc.Texture2D.MipLevels = desc.MipLevels;
        srvDesc.Texture2D.MostDetailedMip = 0;

        result = D3D11Context::GetDevice()->CreateShaderResourceView(m_Texture, &srvDesc, &m_ImageView);
        PX_ASSERT(SUCCEEDED(result), "No se pudo crear correctamente la texture");
        //pTexture->Release();

        D3D11_SAMPLER_DESC samplerDesc = {};
        samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
        samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
        samplerDesc.MipLODBias = 0.0f;
        samplerDesc.MinLOD = 0.0f;
        samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

        result = D3D11Context::GetDevice()->CreateSamplerState(&samplerDesc, &m_Sampler);
    }

    const void* D3D11Texture2D::GetEntityHandler() const
    {
        return m_ImageView;
    }

    void D3D11Texture2D::CreateTexture2D(uint32_t width, uint32_t height)
	{
        /*
		D3D11_TEXTURE2D_DESC textureDesc;
        UINT Width = width;
        UINT Height = height;
        UINT MipLevels; // 1 for multisampling
        UINT ArraySize = 1;
        DXGI_FORMAT Format; // Format
        DXGI_SAMPLE_DESC SampleDesc;
        // Count
        // Cuantity
        D3D11_USAGE Usage;
        UINT BindFlags;
        UINT CPUAccessFlags;
        UINT MiscFlags;
        */
	}
}