#pragma once
#ifndef _PHOTOXEL_D3D11_VERTEX_BUFFER_H_
#define _PHOTOXEL_D3D11_VERTEX_BUFFER_H_

#include <d3d11.h>

namespace Photoxel
{
	class D3D11VertexBuffer
	{
		D3D11VertexBuffer(const void* data, size_t size);
	private:
		ID3D11Buffer* m_HandlerID;
	};
}

#endif
