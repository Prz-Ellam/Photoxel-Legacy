#include "fxpch.h"
#include "D3D11VertexBuffer.h"
#include "Core/Core.h"
#include "D3D11Context.h"

namespace Photoxel
{
	D3D11VertexBuffer::D3D11VertexBuffer(const void* data, size_t size)
	{
		D3D11_BUFFER_DESC bufferDesc = {};
		bufferDesc.ByteWidth = static_cast<UINT>(size);
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA subresourceData = {};
		subresourceData.pSysMem = data;
		subresourceData.SysMemPitch = 0;
		subresourceData.SysMemSlicePitch = 0;

		HRESULT hr = 0;
		hr = D3D11Context::GetDevice()->CreateBuffer(&bufferDesc, &subresourceData, &m_HandlerID);
	}
}