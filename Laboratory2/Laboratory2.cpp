#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <Windowsx.h>
#include <tchar.h>
#include "menudemo.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[] = _T("MyClass");
int sw;
//==================================================================================
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	HWND hMainWnd;

	MSG msg;
	WNDCLASSEX wc;
	//Заполняем структуру класса окна
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	//Регистрируем класс окна
	if (!RegisterClassExW(&wc)) {
		MessageBoxW(NULL, _T("Cannot registr class"), _T("Error"), MB_OK);
		return 0;
	}
	//Создаем основное окно приложения
	hMainWnd = CreateWindow(szClassName, _T("A Hello1 Application"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL,
		hInstance, NULL);

	if (!hMainWnd) {
		MessageBox(NULL, _T("Cannot create main window"), _T("Error"), MB_OK);
		return 0;
	}

	//Показываем окно
	ShowWindow(hMainWnd, nCmdShow);

	//UpdateWindow(hMainWnd);
	//Выполняем цикл обработки сообщений до закрытия окна
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;

}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	static int sx, sy;
	HDC hdc;
	PAINTSTRUCT ps;
	HMENU hmenu, hpopupmenu;
	TCHAR FullName[] = _T("Фамилия");
	TCHAR Group[] = _T("Группа");
	TCHAR List[] = _T("Студент");


	switch (uMsg) {
	case WM_COMMAND:
		hmenu = GetMenu(hWnd);
		switch (LOWORD(wParam)) {
		case MI_FULLNMAE:
			sw = 1;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case MI_GROUP:
			sw = 2;
			InvalidateRect(hWnd, NULL, TRUE);
			break;

		}
	case WM_CREATE:
		hmenu = CreateMenu();
		hpopupmenu = CreatePopupMenu();
		AppendMenu(hpopupmenu, MF_STRING, MI_FULLNMAE, FullName);
		AppendMenu(hpopupmenu, MF_STRING, MI_GROUP, Group);

		AppendMenu(hmenu, MF_POPUP, (UINT)hpopupmenu, List);
		SetMenu(hWnd, hmenu);
		break;
	case WM_SIZE:
		sx = LOWORD(lParam) / 2;
		sy = HIWORD(lParam) / 2;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		if (sw == 1) 
		{
			SetTextColor(hdc, RGB(0, 0, 255));
			TextOut(hdc, sx - 16, sy, _T("Авдюнин Дмитрий"), 16);
		}
			
		if (sw == 2)
		{
			SetTextColor(hdc, RGB(255, 0, 0));
			TextOut(hdc, sx - 9, sy, _T("МП-31-18"), 9);
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;

}