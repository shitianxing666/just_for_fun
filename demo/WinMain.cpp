#include "stdafx.h"
#include "demo.h"
#include "WinMain.h"
#include <windows.h>
int ScreenWidth, ScreenHeight;
int Interval = 100;

LRESULT CALLBACK Melter(HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	switch (Msg)
	{
	case WM_CREATE: {
		HDC Desktop = GetDC(HWND_DESKTOP);
		HDC Window = GetDC(hwnd);
		BitBlt(Window, 0, 0, ScreenWidth, ScreenHeight, Desktop, 0, 0, SRCCOPY);
		ReleaseDC(hwnd, Window);
		ReleaseDC(HWND_DESKTOP, Desktop);
		SetTimer(hwnd, 0, Interval, 0);
		ShowWindow(hwnd, SW_SHOW);
		break;
	}
	case WM_PAINT: {
		ValidateRect(hwnd, 0);
		break;
	}
	case WM_TIMER: {
		HDC Window = GetDC(hwnd);
		int K = (rand() % ScreenHeight) - (150 / 2), Y = (rand() % 15), Width = (rand() % 150);
		BitBlt(Window, K, Y, Width, ScreenHeight, Window, K, 0, SRCCOPY);
		ReleaseDC(hwnd, Window);
		break;
	}
	case WM_DESTROY: {
		KillTimer(hwnd, 0);
		PostQuitMessage(0);
		break;
	}
					 return 0;
	}
	return DefWindowProc(hwnd, Msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE Inst, HINSTANCE Prev, LPSTR Cmd, int showcmd)
{
	Demo demo;
	demo.run();
	system("pause");

	//获得屏幕长宽
	ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	ScreenHeight = GetSystemMetrics(SM_CXSCREEN);
	WNDCLASS wndclass = { 0,Melter,0,0,Inst,0,LoadCursor(0,IDC_ARROW),0,0,L"ScreenMelter" };
	if (RegisterClass(&wndclass))//对所有窗口进行溶解
	{
		HWND hwnd = CreateWindowExA(WS_EX_TOPMOST, "ScreenMelter", 0, WS_POPUP, 0, 0, ScreenWidth, ScreenHeight, HWND_DESKTOP, 0, Inst, 0);
		if (hwnd)//获得随机种子
		{
			srand(GetTickCount());
			MSG msg = { 0 };
			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					;
				}
			}
			return msg.wParam;
		}
	}
}
