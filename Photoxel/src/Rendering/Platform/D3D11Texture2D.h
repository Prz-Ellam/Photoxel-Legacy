#pragma once
#ifndef _PHOTOXEL_D3D11_TEXTURE_2D_H_
#define _PHOTOXEL_D3D11_TEXTURE_2D_H_

#include <d3d11.h>

namespace Photoxel
{
	enum class ImageFormat
	{
		None = 0,
		RGBA,
		RGB
	};


	class D3D11Texture2D
	{
	public:
	private:

		void CreateTexture2D(uint32_t width, uint32_t height);

		ID3D11Texture2D* m_Texture;
		ID3D11ShaderResourceView* m_RSV;
		ID3D11SamplerState* m_Sampler;

		uint32_t m_Width, m_Height;

	};
}

#endif
