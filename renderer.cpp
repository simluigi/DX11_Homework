//===============================================
//
//  DX11_Initialization: renderer.cpp
//  Author: Luigi Sim
//  Last modified: 2022.04.21
//
//===============================================

#include "renderer.h"

#include "swapChain.h"

using namespace Microsoft::WRL;

CRenderer::CRenderer()
{

}
CRenderer::~CRenderer()
{

}

bool CRenderer::CreateRenderTargetView(ComPtr<ID3D11Device2> device, ComPtr<IDXGISwapChain2> swapChain)
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer;
	hr = swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	D3D11_RENDER_TARGET_VIEW_DESC rtvDesc{};	
	hr = device->CreateRenderTargetView(backBuffer.Get(), nullptr, &m_pRenderTargetView);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool CRenderer::CreateDepthStencilView(ComPtr<ID3D11Device2> device, int width, int height)
{
	HRESULT hr;

	D3D11_TEXTURE2D_DESC depthStencilBufferDesc{};
	depthStencilBufferDesc.Width = width;
	depthStencilBufferDesc.Height = height;
	depthStencilBufferDesc.MipLevels = 1;
	depthStencilBufferDesc.ArraySize = 1;
	depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;  // 24 bits for depth, 8 bits for stencil
	depthStencilBufferDesc.SampleDesc.Count = 1;
	depthStencilBufferDesc.SampleDesc.Quality = 0;
	depthStencilBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilBufferDesc.CPUAccessFlags = 0;
	depthStencilBufferDesc.MiscFlags = 0;

	ComPtr<ID3D11Texture2D> depthStencilBuffer;
	hr = device->CreateTexture2D(&depthStencilBufferDesc, nullptr, &depthStencilBuffer);
	if (FAILED(hr))
	{
		return false;
	}

	hr = device->CreateDepthStencilView(depthStencilBuffer.Get(), nullptr, &m_pDepthStencilView);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool CRenderer::CreateDepthStencilState(ComPtr<ID3D11Device2> device)
{
	HRESULT hr;

	D3D11_DEPTH_STENCIL_DESC depthStencilStateDesc{};
	depthStencilStateDesc.DepthEnable = TRUE;
	depthStencilStateDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilStateDesc.DepthFunc = D3D11_COMPARISON_LESS;  // research more later
	depthStencilStateDesc.StencilEnable = FALSE;

	hr = device->CreateDepthStencilState(&depthStencilStateDesc, &m_pDepthStencilState);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool CRenderer::CreateRasterizerState(ComPtr<ID3D11Device2> device)
{
	HRESULT hr;

	D3D11_RASTERIZER_DESC rasterizerDesc{};
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_BACK;
	rasterizerDesc.FrontCounterClockwise = FALSE;
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0.0f;
	rasterizerDesc.SlopeScaledDepthBias = 0.0f;
	rasterizerDesc.DepthClipEnable = FALSE;
	rasterizerDesc.ScissorEnable = FALSE;
	rasterizerDesc.MultisampleEnable = FALSE;
	rasterizerDesc.AntialiasedLineEnable = FALSE;

	hr = device->CreateRasterizerState(&rasterizerDesc, &m_pRasterizerState);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

//bool CRenderer::CreateInputAssembly(ComPtr<ID3D11DeviceContext2> deviceContext)
//{
//	HRESULT hr;
//	
//	D3D11_INPUT_ELEMENT_DESC vertexLayoutDesc[] =
//	{
//		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,  offsetof(VertexPos, Position), D3D11_INPUT_PER_VERTEX_DATA, 0},
//		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0,  offsetof(VertexPos, TexCoord), D3D11_INPUT_PER_VERTEX_DATA, 0 }
//	};
//
//
//
//	return true;
//}



ComPtr<ID3D11RenderTargetView>	CRenderer::GetRenderTargetView()
{
	return m_pRenderTargetView;
}
ComPtr<ID3D11DepthStencilView>	CRenderer::GetDepthStencilView()
{
	return m_pDepthStencilView;
}
ComPtr<ID3D11DepthStencilState>	CRenderer::GetDepthStencilState()
{
	return m_pDepthStencilState;
}
ComPtr<ID3D11RasterizerState>	CRenderer::GetRasterizerState() 
{
	return m_pRasterizerState;
}