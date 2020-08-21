#include <windows.h>
#include <random>

HBRUSH Brush = CreateSolidBrush(RGB(0, 0, 255));

void Notepad()
{
	STARTUPINFO sInfo;
	ZeroMemory(&sInfo, sizeof(STARTUPINFO));

	PROCESS_INFORMATION pInfo;

	CreateProcess(L"C:\\Windows\\Notepad.exe",
		NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &sInfo, &pInfo);
}

void RepaintWindows(HWND& hWnd, int r, int g, int b) {

	HBRUSH hBrush = CreateSolidBrush(RGB(r, g, b));
	InvalidateRect(hWnd, 0, TRUE);
	Brush = hBrush

	HBRUSH oBrush = (HBRUSH)SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG)hBrush);
	DeleteObject(oBrush);
}

LRESULT CALLBACK myWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int x, y, red, green, blue, horizontal, vertical;

	switch (uMsg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:			// ESC
			PostQuitMessage(0);
			return 0;

		case VK_RETURN:			// ENTER
			red = rand() % 256;
			blue = rand() % 256;
			green = rand() % 256;
			RepaintWindows(hWnd, red, green, blue);
			return 0;

		case (WPARAM)0x51:		// Q
			if (GetAsyncKeyState(VK_CONTROL))
				PostQuitMessage(0);
			return 0;

		case (WPARAM)0x43:		// C
			if (GetAsyncKeyState(VK_SHIFT))
				Notepad();
			return 0;
		}
		return 0;

	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);

		RECT rect;
		GetClientRect(hWnd, &rect);
		horizontal = (rect.right - rect.left) / 2;
		vertical = (rect.bottom - rect.top) / 2;

		if (x <= horizontal && y <= vertical)  
			RepaintWindows(hWnd, 255, 0, 0);
		else if (x > horizontal && y < vertical) 
			RepaintWindows(hWnd, 255, 255, 0);
		else if (x < horizontal && y > vertical) 
			RepaintWindows(hWnd, 0, 255, 0);
		else 
			RepaintWindows(hWnd, 0, 0, 255);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int main(int argc, char **argv)
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	WNDCLASS winClass;
	winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winClass.lpfnWndProc = (WNDPROC)myWndProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = hInstance;
	winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = Brush;
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = L"MyWindowClass";

	RegisterClass(&winClass);

	HWND hWnd = CreateWindow(L"MyWindowclass", L"Window by raw API",
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		100, 100, 320, 240,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWnd, SW_SHOW);

	MSG message;
	BOOL bMessageOk;
	while ((bMessageOk = GetMessage(&message, NULL, 0, 0)) != 0)
	{
		if (bMessageOk == -1)
		{
			puts("Suddenly, GetMessage failed! You can call GetLastError() to see what happend");
			break;
		}
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	DestroyWindow(hWnd);
	UnregisterClass(L"MyWindowclass", hInstance);
	DeleteObject(Brush);

	return 0;
}