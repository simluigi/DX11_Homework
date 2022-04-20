//===============================================
//
//  DX11_Initialization: swapChain.h
//  Author: Luigi Sim
//  Last modified: 2022.04.20
//
//===============================================

#pragma once

#include <d3d11_2.h>
#include <dxgi1_2.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

class CSwapChain
{
public:
	
	CSwapChain();
	~CSwapChain();

	bool CreateSwapChain(HWND hWnd, IUnknown* device, int width, int height);

private:

	Microsoft::WRL::ComPtr<IDXGISwapChain2> m_pSwapChain;
	Microsoft::WRL::ComPtr<IDXGIFactory2>	m_pFactory;

};