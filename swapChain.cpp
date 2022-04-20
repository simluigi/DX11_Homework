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

bool CSwapChain::CreateSwapChain(HWND hWnd, IUnknown* device, int width, int height)
{
	DXGI_SAMPLE_DESC sampleDesc{};
	sampleDesc.Count = 1;	// no multisampling for now
	sampleDesc.Quality = 0;

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc{};
	swapChainDesc.Width = width;
	swapChainDesc.Height = height;
	swapChainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.Stereo = false;
	swapChainDesc.SampleDesc = sampleDesc;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.Scaling = DXGI_SCALING_NONE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.Flags = 0;

	ComPtr<IDXGISwapChain1> tempSwapChain;

	HRESULT hr = m_pFactory->CreateSwapChainForHwnd(
		device,
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