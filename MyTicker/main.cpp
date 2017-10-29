#include <iostream>
#include <string>
#include <windows.h>
#include <tchar.h>
#include "ticker.h"

#define ScreenX GetSystemMetrics(SM_CXSCREEN)
#define ScreenY GetSystemMetrics(SM_CYSCREEN)
#define WindowTitle "Clock"
#define ClassName "SalamanderClock"
#define WindowWidth  500
#define WindowHeight 300
#define IDT_TIMER 303



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR szCmdLine, int iCmdShow)
{
	static TCHAR appTitle[] = TEXT(WindowTitle);
	static TCHAR szAppName[] = TEXT(ClassName);


	int xCtr = (ScreenX - WindowWidth) / 2;
	int yCtr = (ScreenY - WindowHeight) / 2;



	HWND       hwnd;
	MSG        msg;
	WNDCLASS   wndclass;


	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;

	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"),
			szAppName, MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(
		szAppName,
		appTitle,
		WS_OVERLAPPEDWINDOW,
		xCtr,
		yCtr,
		WindowWidth,
		WindowHeight,
		NULL,
		NULL,
		hInstance,
		NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

void Paint(HWND hwnd, LPCTSTR txt)
{

	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;

	GetClientRect(hwnd, &rect);

	InvalidateRect(hwnd, &rect, false);

	hdc = BeginPaint(hwnd, &ps);
	DrawText(hdc, txt, -1, &rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	EndPaint(hwnd, &ps);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
	{
		SetTimer(hwnd, IDT_TIMER, 1000, (TIMERPROC)NULL);
	}
	return 0;
	case WM_PAINT:
		Paint(hwnd, Ticker::GetCurrentTimeStr().c_str());
		return 0;
	case WM_TIMER:
		switch (wParam)
		{
		case IDT_TIMER:
			string dateStr = Ticker::GetCurrentTimeStr();
			Paint(hwnd, dateStr.c_str());
			return 0;
		}
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

