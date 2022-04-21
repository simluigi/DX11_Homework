//===============================================
//
//  DX11_Initialization: swapChain.h
//  Author: Luigi Sim
//  Last modified: 2022.04.20
//
//===============================================

#include "swapChain.h"

using namespace Microsoft::WRL;

CSwapChain::CSwapChain()
{

}

CSwapChain::~CSwapChain()
{

}

bool CSwapChain::CreateSwapChain(HWND hWnd, ComPtr<ID3D11Device2> device, int width, int height)
{
	HRESULT hr;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	swapChainDesc.Width = width;
	swapChainDesc.Height = height;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.Scaling = DXGI_SCALING_NONE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.Flags = 0;

	ComPtr<IDXGISwapChain1> tempSwapChain;
	CSwapChain::QueryDXGIFactory(device);
	
	hr = m_pFactory->CreateSwapChainForHwnd(
		device.Get(),
		hWnd,
		&swapChainDesc,
		nullptr,
		nullptr,
		&tempSwapChain
	);
	if (FAILED(hr))
	{
		return false;
	}

	tempSwapChain.As(&m_pSwapChain);

	return true;
}

ComPtr<IDXGISwapChain2> CSwapChain::GetSwapChain()
{
	return m_pSwapChain;
}

// retrieve factory used to make the device 
bool CSwapChain::QueryDXGIFactory(ComPtr<ID3D11Device2> device)
{
	HRESULT hr;

	IDXGIDevice* pDXGIDevice = nullptr;
	hr = device->QueryInterface(__uuidof(IDXGIDevice), (void**)&pDXGIDevice);
	if (FAILED(hr))
	{
		return false;
	}

	IDXGIAdapter* pDXGIAdapter = nullptr;
	hr = pDXGIDevice->GetAdapter(&pDXGIAdapter);
	if (FAILED(hr))
	{
		return false;
	}

	//  use IDXGI::GetParent to locate the factory
	hr = pDXGIAdapter->GetParent(__uuidof(IDXGIFactory2), (void**)&m_pFactory);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

