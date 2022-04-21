//===============================================
//
//  DX11_Initialization: renderer.h
//  Author: Luigi Sim
//  Last modified: 2022.04.21
//
//===============================================

#pragma once

#include <d3d11_2.h>
#include <dxgi1_2.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <wrl/client.h>

#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "dxgi.lib")

struct VertexPos
{
	DirectX::XMFLOAT3 Position;
	DirectX::XMFLOAT2 TexCoord;
};

class CRenderer
{
public:

	CRenderer();
	~CRenderer();

	bool CreateRenderTargetView(Microsoft::WRL::ComPtr<ID3D11Device2> device, Microsoft::WRL::ComPtr<IDXGISwapChain2> swapChain);
	bool CreateDepthStencilView(Microsoft::WRL::ComPtr<ID3D11Device2> device, int width, int height);
	bool CreateDepthStencilState(Microsoft::WRL::ComPtr<ID3D11Device2> device);
	bool CreateRasterizerState(Microsoft::WRL::ComPtr<ID3D11Device2> device);

	//bool CreateVertexBuffer(Microsoft::WRL::ComPtr<ID3D11Device2> device);
	//bool CreateIndexBuffer(Microsoft::WRL::ComPtr<ID3D11Device2> device);
	//bool CreateInputLayout(Microsoft::WRL::ComPtr<ID3D11Device2> device);
	
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	GetRenderTargetView();
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	GetDepthStencilView();
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>	GetDepthStencilState();
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>	GetRasterizerState();

private:

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	m_pRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	m_pDepthStencilView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState>	m_pDepthStencilState;
	Microsoft::WRL::ComPtr<ID3D11RasterizerState>	m_pRasterizerState;

	Microsoft::WRL::ComPtr<ID3D11InputLayout>		m_pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			m_pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>			m_pIndexBuffer;

	Microsoft::WRL::ComPtr<ID3D11VertexShader>		m_pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>		m_pPixelShader;


};
