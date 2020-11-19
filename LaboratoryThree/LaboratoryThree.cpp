#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<vector>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
#define ID_COMBO1 100
#define ID_COMBO2 102
#define GET_MESS 103
LPSTR ReturnDate(int day, int month, int year);

char szAppName[] = "PopPad1";

HINSTANCE hInst;
HBRUSH hBrush;

HWND hComboBox1, hComboBox2;



char Buf1[80], Buf[80];
HDC hdc1, memdc;
PAINTSTRUCT ps;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX wc;
	MSG lpMsg;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) return 0;
	hWnd = CreateWindow(szAppName, "Демонстрация списков", WS_OVERLAPPEDWINDOW, 100, 100, 300, 400, (HWND)NULL, (HMENU)NULL,
		hInstance, (LPSTR)NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessageW(&lpMsg);
	}
	return (int)lpMsg.wParam;
}
LPCSTR ArrText[12] = {
	"Строка 1", "Строка 2", "Строка 3", "Строка 4","Строка 5","Строка 6",
	"Строка 7","Строка 8","Строка 9","Строка 10","Строка 11","Строка 12"
};
LPCSTR Buff[11];
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	int i;
	int date, month, year;
	int maxX = 0, maxY = 0;

	char day[2];

	HBITMAP hbit;

	
	
	switch (uMsg) {
	case WM_CREATE:
		hdc1 = GetDC(hWnd);

		maxX = GetSystemMetrics(SM_CXSCREEN);
		maxY = GetSystemMetrics(SM_CYSCREEN);

		hComboBox2 = CreateWindow("Combobox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | CBS_DROPDOWNLIST,
			150, 80, 100, 200, hWnd, (HMENU)ID_COMBO2, hInst, NULL);

		hComboBox1 = CreateWindow("Combobox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL ,
			30, 80, 100, 200, hWnd, (HMENU)ID_COMBO1, hInst, NULL);

		for (i = 0; i < 12; i++)
		{
			SendMessage(hComboBox1, CB_ADDSTRING, 1, (LPARAM)ArrText[i]);
		}

		SendMessage(hComboBox1, CB_SETCURSEL, (WPARAM)5, 0L);
		memdc = CreateCompatibleDC(hdc1);
		hbit = CreateCompatibleBitmap(hdc1, maxX, maxY);
		SelectObject(memdc, hbit);
		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		SelectObject(memdc, hBrush);
		PatBlt(memdc, 0, 0, maxX, maxY, PATCOPY);
		ReleaseDC(hWnd, hdc1);
		break;
	case WM_SIZE:
		InvalidateRect(hWnd, NULL, 1);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_COMBO1:
			if (HIWORD(wParam) == CBN_DBLCLK)
			{
				i = SendMessage(hComboBox1, CB_GETCURSEL, 0, 0L);
				SendMessage(hComboBox2, CB_ADDSTRING, 1, (LPARAM)ArrText[i]);
				i = SendMessage(hComboBox2, CB_GETCOUNT, 0, 0L);
				SendMessage(hComboBox2, CB_SETCURSEL, i-1, 0L);
				return 0;
			}
			return 0;
		default:
			return 0;
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}