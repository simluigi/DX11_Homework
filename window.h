//===============================================
//
//  DX11_Initialization: window.h
//  Author: Luigi Sim
//  Last modified: 2022.04.20
//
//===============================================

#pragma once

#include <Windows.h>

class CWindow
{
public:

	CWindow();
	~CWindow();

	int		CreateApplicationWindow(WNDPROC wndProc, HINSTANCE hInstance, int cmdShow, int width, int height);
	HWND	GetWindowHandle();

private:
		
	HWND	m_hWnd;
};