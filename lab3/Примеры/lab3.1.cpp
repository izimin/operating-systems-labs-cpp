#include <windows.h>

// This function is called by the Windows function DispatchMessage().
LRESULT CALLBACK myWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) // Handle the messages.
    {
        case WM_CLOSE:
            PostQuitMessage(0); // Send WM_QUIT to the message queue.
            return 0;
    }

    // For messages that we don't deal with.
    return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int main(int argc, char **argv)
{
	// Get the handler of module that will be associated with a window.
	// In this case it will be handler of the executable file of current process.
	HINSTANCE hInstance = GetModuleHandle(NULL);

	// Create brush that will fill the background of the window.
	HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255));
	
	// Create window class.
	WNDCLASS winClass;
	winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    winClass.lpfnWndProc = (WNDPROC)myWndProc;
    winClass.cbClsExtra	= 0;
    winClass.cbWndExtra = 0;
    winClass.hInstance = hInstance;
    winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
    winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    winClass.hbrBackground = hBrush;
    winClass.lpszMenuName = NULL;
    winClass.lpszClassName = L"MyWindowClass";
	
	// Register class in the system.
	RegisterClass(&winClass);
	
	// Create window.
	HWND hWnd = CreateWindow(L"MyWindowclass", L"Window by raw API",
                             WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
                             100, 100, 320, 240,
                             NULL, NULL, hInstance, NULL);
							   
	// Show window.
	ShowWindow(hWnd, SW_SHOW);
	
	MSG message;
    BOOL bMessageOk;
	// Run the message loop. It will run until GetMessage() returns 0.
    while ((bMessageOk = GetMessage(&message, NULL, 0, 0)) != 0)
    {
        // Yep, wired logic: BOOL mb not only 1 or 0.
        // See msdn at https://msdn.microsoft.com/en-us/library/windows/desktop/ms644936(v=vs.85).aspx
        if (bMessageOk == -1)
        {
            puts("Suddenly, GetMessage failed! You can call GetLastError() to see what happend");
            break;
        }
        // Translate virtual-key message into character message.
        TranslateMessage(&message);
        // Send message to WindowProcedure.
        DispatchMessage(&message);
    }
	
	// Delete window.
	DestroyWindow(hWnd);
	
	// Remove window class.
	UnregisterClass(L"MyWindowclass", hInstance);

	// Delete brush.
	DeleteObject(hBrush);
	
	return 0;
}