//===============================================
//
//  DX11_Initialization: main.cpp
//  Author: Luigi Sim
//  Last modified: 2022.04.20
//
//===============================================

#include "main.h"

#include <Windows.h>
#include <iostream>

#include "window.h"
#include "device.h"
#include "swapChain.h"
#include "renderer.h"

constexpr int width = 1280;
constexpr int height = 720;

// forward declaration for use of WndProc within WinMain
LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

// entry point
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR pCmdLine, _In_ int cmdShow)
{
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);

	CWindow window;
	if (window.CreateApplicationWindow(WndProc, hInstance, cmdShow, width, height) != 0)
	{
		MessageBox(nullptr, TEXT("Failed to create application window!"), TEXT("Error"), MB_OK);
		return -1;
	}

	CDevice device;
	if (!device.CreateDevice())
	{
		MessageBox(nullptr, TEXT("Failed to create device!"), TEXT("Error"), MB_OK);
		return -1;
	}

	CSwapChain swapChain;
	if (!swapChain.CreateSwapChain(window.GetWindowHandle(), device.GetDevice(), width, height))
	{
		MessageBox(nullptr, TEXT("Failed to create swap chain!"), TEXT("Error"), MB_OK);
		return -1;
	}

	CRenderer renderer;
	if (!renderer.CreateRenderTargetView(device.GetDevice(), swapChain.GetSwapChain()))
	{
		MessageBox(nullptr, TEXT("Failed to create render target view!"), TEXT("Error"), MB_OK);
		return -1;
	}

	if (!renderer.CreateDepthStencilView(device.GetDevice(), width, height))
	{
		MessageBox(nullptr, TEXT("Failed to create depth stencil view!"), TEXT("Error"), MB_OK);
		return -1;
	}

	if (!renderer.CreateDepthStencilState(device.GetDevice()))
	{
		MessageBox(nullptr, TEXT("Failed to create depth stencil state!"), TEXT("Error"), MB_OK);
		return -1;
	}

	if (!renderer.CreateRasterizerState(device.GetDevice()))
	{
		MessageBox(nullptr, TEXT("Failed to create rasterizer state!"), TEXT("Error"), MB_OK);
		return -1;
	}

	// message loop
	MSG	 msg;
	BOOL bRet;

	while ((bRet = GetMessageA(&msg, window.GetWindowHandle(), 0, 0)) != 0)  // returns 0 on WM_QUIT, returns -1 on error
	{
		if (bRet == -1)
		{
			// error handling here
			return -1;
		}
		else
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return 0;
}


// window listener
LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}