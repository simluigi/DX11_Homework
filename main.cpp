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

// forward declaration for use of WndProc within WinMain
LRESULT CALLBACK WndProc(_In_ HWND hWnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);

// entry point
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE prevInstance, _In_ LPSTR pCmdLine, _In_ int cmdShow)
{
	UNREFERENCED_PARAMETER(prevInstance);
	UNREFERENCED_PARAMETER(pCmdLine);

	CWindow window;

	if (window.CreateApplicationWindow(WndProc, hInstance, cmdShow) != 0)
	{
		MessageBox(nullptr, "Failed to create application window!", "Error", MB_OK);
		return -1;
	}

	CDevice device;

	if (!device.CreateDevice())
	{
		MessageBox(nullptr, "Failed to create device!", "Error", MB_OK);
		return -1;
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