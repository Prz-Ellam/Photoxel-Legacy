#include "fxpch.h"
#include "D3D11Context.h"
#include "Core/Core.h"
#include "Window/Platform/Win32/Win32Window.h"

#define RELEASE_COM(x)\
	if (x) { x->Release(); x = nullptr; }\

namespace Photoxel
{
	ID3D11Device* D3D11Context::m_Device = nullptr;
	ID3D11DeviceContext* D3D11Context::m_DeviceContext = nullptr;
	ID3D11RenderTargetView* D3D11Context::m_RenderTargetView = nullptr;
	IDXGISwapChain* D3D11Context::m_SwapChain = nullptr;
	ID3D11ShaderResourceView* D3D11Context::m_ShaderResourceView;

	D3D11Context::D3D11Context(Window* window)
		: m_Window(window)
	{
		CreateDevice();
	}

	void D3D11Context::CreateDevice()
	{
		/*
		IDXGIFactory* pFactory;

		HRESULT result = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&pFactory);

		IDXGIAdapter* pAdapter;
		uint32_t index = 0;
		std::vector<IDXGIAdapter*> adapters;
		while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
		{
			adapters.push_back(pAdapter);
			index++;
		}

		index = 0;
		for (auto& adapter : adapters)
		{
			DXGI_ADAPTER_DESC desc;
			adapter->GetDesc(&desc);

			int dummy = -1;
		}

		int dummy2 = -1;
		//D3D11CreateDevice(nullptr, DriverType, Software, Flags, pFeatureLevels, FeatureLevels, SDKVersion,
		//	ppDevice, pFeatureLevel, ppInmediateContext)
		*/
		std::array<D3D_DRIVER_TYPE, 3> driverTypes = {
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_SOFTWARE
		};

		std::array<D3D_FEATURE_LEVEL, 3> featureLevels = {
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0
		};

		DXGI_SWAP_CHAIN_DESC scd = { 0 };
		scd.BufferCount = 2u;
		scd.BufferDesc.Width = 0u;
		scd.BufferDesc.Height = 0u;
		scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		scd.BufferDesc.RefreshRate.Numerator = 60;
		scd.BufferDesc.RefreshRate.Denominator = 1;
		scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
		scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scd.OutputWindow = reinterpret_cast<HWND>(m_Window->GetNativeHandler());
		scd.Windowed = TRUE;
		scd.SampleDesc.Count = 1u;
		scd.SampleDesc.Quality = 0u;

		uint32_t creationFlags = 0;

#ifdef _DEBUG
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		HRESULT hr = 0;

		for (auto& driver : driverTypes) {

			hr = D3D11CreateDeviceAndSwapChain(0, driver, 0, creationFlags,
				featureLevels.data(), static_cast<UINT>(featureLevels.size()), D3D11_SDK_VERSION,
				&scd, &m_SwapChain, &m_Device, nullptr, &m_DeviceContext);

			if (SUCCEEDED(hr)) {
				break;
			}

		}

		PX_ASSERT(!FAILED(hr), "No se pudo crear el Device y la Swap Chain");

		UINT a = 0;
		m_Device->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM, 4, &a);

		ID3D11Texture2D* m_Resource = nullptr;
		hr = m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&m_Resource));

		PX_ASSERT(!FAILED(hr), "No se pudo crear el Back Buffer");

		hr = m_Device->CreateRenderTargetView(m_Resource, nullptr, &m_RenderTargetView);

		PX_ASSERT(!FAILED(hr), "No se pudo crear el Render Target View");

		if (m_Resource) {
			m_Resource->Release();
		}
		/*
		D3D11_VIEWPORT viewport = { 0 };
		viewport.Width = static_cast<float>(m_Window->GetWidth());
		viewport.Height = static_cast<float>(m_Window->GetHeight());
		viewport.MinDepth = 0.0f;
		viewport.MaxDepth = 1.0f;
		viewport.TopLeftX = 0.0f;
		viewport.TopLeftY = 0.0f;

		m_DeviceContext->RSSetViewports(1, &viewport);
		m_DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		dsDesc.DepthEnable = TRUE;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
		dsDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		hr = m_Device->CreateDepthStencilState(&dsDesc, &m_DepthStencilState);

		PX_ASSERT(!FAILED(hr), "No se pudo crear el Depth Stencil");

		m_DeviceContext->OMSetDepthStencilState(m_DepthStencilState, 1u);

		D3D11_TEXTURE2D_DESC stencilDesc = { 0 };
		stencilDesc.Width = static_cast<UINT>(m_Window->GetWidth());
		stencilDesc.Height = static_cast<UINT>(m_Window->GetHeight());
		stencilDesc.MipLevels = 1u;
		stencilDesc.ArraySize = 1u;
		stencilDesc.Format = DXGI_FORMAT_D32_FLOAT;
		//stencilDesc.SampleDesc.Count = 4u;
		stencilDesc.SampleDesc.Count = 1u;
		stencilDesc.SampleDesc.Quality = 0u;
		stencilDesc.Usage = D3D11_USAGE_DEFAULT;
		stencilDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
		hr = m_Device->CreateTexture2D(&stencilDesc, nullptr, &m_DepthStencil);

		PX_ASSERT(!FAILED(hr), "No se pudo crear la Textura");

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc = { };
		dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;
		//dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		//dsvDesc.Texture2D.MipSlice = 1u;
		dsvDesc.Texture2D.MipSlice = 0u;

		hr = m_Device->CreateDepthStencilView(m_DepthStencil, &dsvDesc, &m_DepthStencilView);

		PX_ASSERT(!FAILED(hr), "No se pudo crear el Depth Stencil View");

		m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

		D3D11_BLEND_DESC blendDesc = {};
		auto& blendTarget = blendDesc.RenderTarget[0];
		blendTarget.BlendEnable = TRUE; // FALSE para no tener alpha blending
		blendTarget.SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendTarget.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendTarget.BlendOp = D3D11_BLEND_OP_ADD;
		blendTarget.SrcBlendAlpha = D3D11_BLEND_ZERO;
		blendTarget.DestBlendAlpha = D3D11_BLEND_ZERO;
		blendTarget.BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendTarget.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL; // FALSE
		hr = m_Device->CreateBlendState(&blendDesc, &m_BlendState);

		PX_ASSERT(!FAILED(hr), "No se pudo crear el Blend State");

		m_DeviceContext->OMSetBlendState(m_BlendState, nullptr, 0xFFFFFFFF);

		D3D11_RASTERIZER_DESC rasterDesc = { };
		rasterDesc.FillMode = D3D11_FILL_SOLID;
		rasterDesc.CullMode = D3D11_CULL_NONE;
		rasterDesc.MultisampleEnable = TRUE;
		rasterDesc.AntialiasedLineEnable = TRUE;
		hr = m_Device->CreateRasterizerState(&rasterDesc, &m_RasterizerState);

		PX_ASSERT(!FAILED(hr), "No se pudo crear el Rasterizer State");

		m_DeviceContext->RSSetState(m_RasterizerState);
		*/
	}

	D3D11Context::~D3D11Context()
	{
		RELEASE_COM(m_Device);
		RELEASE_COM(m_DeviceContext);
		RELEASE_COM(m_RenderTargetView);
		RELEASE_COM(m_DepthStencilView);
		RELEASE_COM(m_DepthStencilState);
		RELEASE_COM(m_RasterizerState);
		RELEASE_COM(m_BlendState);
		RELEASE_COM(m_SwapChain);
		RELEASE_COM(m_DepthStencil);
	}

	void D3D11Context::Present()
	{
		m_SwapChain->Present(1u, 0u);
	}


	void D3D11Context::InvalidateRenderTargetView(uint32_t width, uint32_t height)
	{
		RELEASE_COM(m_RenderTargetView);

		if (m_SwapChain && m_Device) {

			m_SwapChain->ResizeBuffers(0, width, height, DXGI_FORMAT_UNKNOWN, 0);

			ID3D11Texture2D* pBackBuffer;
			m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
			m_Device->CreateRenderTargetView(pBackBuffer, nullptr, &m_RenderTargetView);
			pBackBuffer->Release();
		}

	}




}