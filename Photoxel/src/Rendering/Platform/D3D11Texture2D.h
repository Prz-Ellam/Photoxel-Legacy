#pragma once
#ifndef _PHOTOXEL_D3D11_TEXTURE_2D_H_
#define _PHOTOXEL_D3D11_TEXTURE_2D_H_

#include <d3d11.h>
#include "Utils/Image.h"

namespace Photoxel
{
	class D3D11Texture2D
	{
	public:
		D3D11Texture2D(const Image& image);

		const void* GetEntityHandler() const;

	private:

		void CreateTexture2D(uint32_t width, uint32_t height);

		ID3D11Texture2D* m_Texture;
		ID3D11ShaderResourceView* m_ImageView;
		ID3D11SamplerState* m_Sampler;


	};
}

#endif
