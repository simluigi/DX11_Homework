//===============================================
//
//  DX11_Initialization: device.cpp
//  Author: Luigi Sim
//  Last modified: 2022.04.20
//
//===============================================

#include "device.h"

using namespace Microsoft::WRL;

CDevice::CDevice()
{

}

CDevice::~CDevice()
{

}

bool CDevice::CreateDevice()
{
	UINT createDeviceFlags = 0;

	D3D_FEATURE_LEVEL featureLevels [] =
	{
		D3D_FEATURE_LEVEL_11_1,  // explicitly define for D3D version 11.1 runtime
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

#ifdef _DEBUG
	createDeviceFlags = D3D11_CREATE_DEVICE_DEBUG;
#endif 

	ComPtr<ID3D11Device> tempDevice;
	ComPtr<ID3D11DeviceContext> tempContext;

	HRESULT hr = D3D11CreateDevice(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		createDeviceFlags,
		featureLevels, 
		_countof(featureLevels),
		D3D11_SDK_VERSION,
		&tempDevice,
		nullptr,
		&tempContext
		);

	if (FAILED(hr))
	{
		return false;
	}

	// converting DX11 versions to DX11.1
	tempDevice.As(&m_pDevice);
	tempContext.As(&m_pDeviceContext);

	return true;
}

ComPtr<ID3D11Device2> CDevice::GetDevice()
{
	return m_pDevice;
}

ComPtr<ID3D11DeviceContext2> CDevice::GetDeviceContext()
{
	return m_pDeviceContext;
}