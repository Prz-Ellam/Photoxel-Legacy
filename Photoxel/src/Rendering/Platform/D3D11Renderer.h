#pragma once
#ifndef _PHOTOXEL_D3D11_RENDERER_H_
#define _PHOTOXEL_D3D11_RENDERER_H_

#include "D3D11Context.h"

namespace Photoxel
{
	class D3D11Renderer
	{
	public:
		void Clear()
		{
			const FLOAT colour[4] = { 0.9f, 0.1f, 0.3f, 1.0f };
			D3D11Context::GetDeviceContext()->OMSetRenderTargets(1, &D3D11Context::GetRenderTargetView(), nullptr);
			D3D11Context::GetDeviceContext()->ClearRenderTargetView(D3D11Context::GetRenderTargetView(), colour);
		}
	private:
	};
}

#endif // _PHOTOXEL_D3D11_RENDERER_H_
