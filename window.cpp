//===============================================
//
//  DX11_Initialization: window.cpp
//  Author: Luigi Sim
//  Last modified: 2022.04.20
//
//===============================================

#include "window.h"

CWindow::CWindow()
	:m_hWnd (0)
{

}

CWindow::~CWindow()
{

}

int CWindow::CreateApplicationWindow(WNDPROC wndProc, HINSTANCE hInstance, int cmdShow, int width, int height)
{
	WNDCLASSEXA wcex{};
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = wndProc;
	wcex.hInstance = hInstance;
	wcex.hIcon = nullptr;
	wcex.hCursor = LoadCursor(nullptr, IDC_CROSS);  // normally IDC_ARROW
	wcex.hbrBackground = nullptr;
	wcex.lpszClassName = "DX11";
	wcex.lpszMenuName = nullptr;

	if (!RegisterClassEx(&wcex))
	{
		return -1;
	}

	m_hWnd = CreateWindowExA
	(
		WS_EX_OVERLAPPEDWINDOW,
		wcex.lpszClassName,
		wcex.lpszClassName,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 
		CW_USEDEFAULT, 
		width,
		height,
		0, 
		0,
		hInstance, 
		nullptr
	);

	if (!m_hWnd)
	{
		return -1;
	}

	ShowWindow(m_hWnd, cmdShow);
	UpdateWindow(m_hWnd);

	// message loop
	MSG	 msg;
	BOOL bRet;
	
	while ((bRet = GetMessageA(&msg, m_hWnd, 0, 0)) != 0)  // returns 0 on WM_QUIT, returns -1 on error
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

HWND CWindow::GetWindowHandle()
{
	return m_hWnd;
}
