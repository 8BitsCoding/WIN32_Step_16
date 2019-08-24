// Project1.cpp : 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "Project1.h"

int g_pos[2] = { 0, };

void CALLBACK MyMoveTimer(HWND hWnd, UINT nMsg, UINT_PTR nIDEvent, DWORD dwTime)
{
	g_pos[0]++;
	if (g_pos[0] >= 300) g_pos[0] = 0;		// 일정 범위 이상 넘어가면 원점복귀
	InvalidateRect(hWnd, NULL, TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_PAINT) {
		PAINTSTRUCT ps;
		HDC h_dc = BeginPaint(hWnd, &ps);

		Ellipse(h_dc, g_pos[0], 10, 100 + g_pos[0], 110);
		Ellipse(h_dc, g_pos[1], 100, 100 + g_pos[1], 210);

		EndPaint(hWnd, &ps);
		return 0;
	}
	else if (uMsg == WM_CREATE) {
		SetTimer(hWnd, 1, 500, MyMoveTimer);
		SetTimer(hWnd, 2, 200, NULL);		// WM_TIMER를 호출해준다.
		return 0;
	}
	else if (uMsg == WM_TIMER) {
		if (wParam == 2) {
			g_pos[1]++;
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
	else if (uMsg == WM_DESTROY) {
		KillTimer(hWnd, 1);
		KillTimer(hWnd, 2);
		PostQuitMessage(0);
	}
		

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASS wc;

	wchar_t my_class_name[] = L"tipssoft";

	wc.cbClsExtra = NULL;
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = my_class_name;
	wc.lpszMenuName = NULL;
	wc.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wc);

	HWND hWnd = CreateWindow(my_class_name, L"www.tipssoft.com",
		WS_OVERLAPPEDWINDOW, 100, 90, 400, 350, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}