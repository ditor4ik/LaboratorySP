#include<Windows.h>
#include<Windowsx.h>
#include<tchar.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR szClassName[] = _T("MainFrame");
HPEN hPen;
HBRUSH hYellowBrush;
//==================================================================================
int APIENTRY WinMain(HINSTANCE This,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow) {
	TCHAR szTitle[] = _T("Программа Текст Фигуры");
	MSG msg;
	WNDCLASS wc;
	//Заполняем структуру класса окна
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = This;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(200, 255, 200));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szClassName;
	//Регистрируем класс окна
	if (!RegisterClass(&wc)) return 0;

	//Создаем основное окно приложения
	HWND hwnd = CreateWindow(szClassName,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		20,
		20,
		800,
		800,
		HWND_DESKTOP,
		NULL,
		This,
		NULL);
	ShowWindow(hwnd, nCmdShow);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessageW(&msg);
	}
	return 0;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg,
	WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC hdc;
	switch (uMsg) {
	case WM_CREATE:
		hPen = CreatePen(PS_SOLID, 4, RGB(200, 200, 200));
		hYellowBrush = CreateSolidBrush(RGB(255, 255, 0));
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SelectPen(hdc, hPen);
		SelectBrush(hdc, GetStockObject(NULL_BRUSH));
		Pie(hdc, 370, 40, 470, 140, 370, 90, 470, 90);
		SelectBrush(hdc, hYellowBrush);
		Pie(hdc, 370, 140, 470, 240, 470, 190, 370, 190);
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