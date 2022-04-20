//===============================================
//
//  DX11_Initialization: device.h
//  Author: Luigi Sim
//  Last modified: 2022.04.20
//
//===============================================

#pragma once

#include <d3d11_2.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

#pragma comment (lib, "d3d11.lib")

class CDevice
{
public:
	CDevice();
	~CDevice();

	bool CreateDevice();

	Microsoft::WRL::ComPtr<ID3D11Device2>			GetDevice();
	Microsoft::WRL::ComPtr<ID3D11DeviceContext2>	GetDeviceContext();

private:

	Microsoft::WRL::ComPtr<ID3D11Device2>			m_pDevice = 0;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext2>	m_pDeviceContext = 0;
};