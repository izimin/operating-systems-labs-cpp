#include <windows.h>

int main(int argc, char **argv)
{
	// Create empty process startup info.
	STARTUPINFO sInfo;
	ZeroMemory(&sInfo, sizeof(STARTUPINFO));

	// Reserve memoryt for process information.
	PROCESS_INFORMATION pInfo;

	// Create process.
	CreateProcess(L"C:\\Windows\\Notepad.exe",
		          NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &sInfo, &pInfo);

	return 0;
}