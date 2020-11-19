#include<Windows.h>
#include<tchar.h>
#include "resource.h"
#include "Animation.h"
#include "gdiplus.h"
#pragma comment(lib,"gdiplus.lib")//GDI+ библиотека

using namespace Gdiplus;//использование пространства имен GDI+

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName[] = _T("MainFrame");
HINSTANCE hInst;
int APIENTRY _tWinMain(HINSTANCE This, //Дескриптор текущего приложения
	HINSTANCE Prev, //В современных системах всегда 0
	LPTSTR cmd, //Командная строка
	int mode) //Режим отображения окна

{
	HWND hWnd; //Дескриптор главного окна программы
	MSG msg; //Структура для хранения сообщения
	hInst = This;
	WNDCLASS wc;//Класс окна
	//Определение класса окна
	wc.hInstance = This;
	wc.lpszClassName = WinName; //Имя класса окна
	wc.lpfnWndProc = WndProc; //Имя класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW; //Стиль окна
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Стандартная иконка
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); //Стандартный курсор
	wc.lpszMenuName = NULL; //Нет меню
	wc.cbClsExtra = 0; //Нет дополнительных данных класса
	wc.cbWndExtra = 0; //Нет дополнительных данных окна
	//Заполнение окна белым цветом
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(255, 150, 0));
	if (!RegisterClass(&wc)) return 0;//Регистрация класса окна
	//Создание окна
	hWnd = CreateWindow(WinName,//Имя класса окна
		_T("Каркас Windows-приложения"),//Заголовок окна
		WS_OVERLAPPEDWINDOW, //Стиль окна
		CW_USEDEFAULT,//x
		CW_USEDEFAULT,//y Размеры окна
		CW_USEDEFAULT,//Width
		CW_USEDEFAULT,//Height
		HWND_DESKTOP,//Дескриптор родительской информации нет
		NULL,//Нет меню
		This,//Дескриптор приложения
		NULL);//Дополнительной информации нет
	ShowWindow(hWnd, mode);//Показать окно
	//Цикл обработки сообщений
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//Функция трансляции кодов нажатой клавиши
		DispatchMessage(&msg);//Посылает сообщение функции WndProc()
	}
	return 0;

}
//Оконная функция вызывается операционной системой
//и получает сообщения из очереди для данного приложения
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	static ObjAnim ship;
	static ObjAnim Sea;
	static int caption, menu, border;
	static int t = 0;
	switch (message)
	{
	case WM_CREATE:
		SetTimer(hWnd, 10, 33, NULL);
		caption = GetSystemMetrics(SM_CYCAPTION);
		menu = GetSystemMetrics(SM_CYMENU);
		border = GetSystemMetrics(SM_CXFIXEDFRAME);
		hdc = GetDC(hWnd);
		ship = ObjAnim(_T("ship.bmp"), hdc);
		Sea = ObjAnim(_T("Sea.bmp"), hdc);
		ReleaseDC(hWnd, hdc);
		break;
	case WM_TIMER:
		t++;
		if (t > Sea.bm.bmWidth) t = -1* ship.bm.bmWidth;
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	case WM_SIZE:
		MoveWindow(hWnd, 100, 50, Sea.bm.bmWidth + 2 * border, Sea.bm.bmHeight*2 + caption
			+ menu + border, TRUE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDM_EXIT: DestroyWindow(hWnd); break;
		default: DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		ship.Draw(t, 10, hdc);
		Sea.Draw(0, Sea.bm.bmHeight + caption + menu + border, hdc);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:PostQuitMessage(0); break;
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}