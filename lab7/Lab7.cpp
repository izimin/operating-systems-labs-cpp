// ThreadWar.cpp : Defines the entry point for the console application.
//
 
#include "stdafx.h"
 
//      ������� ������������ ���� Thread War
//      Thread War'
//      ����������� ������� "�����" � "������", ����� ���������� �����
//      ������� "������" ���������� �������
//      ���� 30 ������ ����� � ������ ���������������,  �� ���������
//      ���� ������ �� ������� ������� ����������
#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
// ������� �������������
HANDLE screenlock; // ���������� ������ ���������� ������ ���� �����
HANDLE bulletsem;  // ����� ���������� ������ ��� ���� ������
HANDLE startevt;     // ���� ���������� � �������� ������� "�����" ��� "������"
// conin - console input, coout - console output
HANDLE conin, conout;  // ����������� �������
HANDLE mainthread; // �������� ����� main
CRITICAL_SECTION gameover;
CONSOLE_SCREEN_BUFFER_INFO info; // ���������� � �������
// ���������� ��������� � ��������
long hit = 0;
long miss = 0;
long delayfactor = 7; // ������ �������� ��� �������� ����
 
// �������� ���������� ����� �� n0 �� n1
int random(int n0, int n1)
{
        if (n0 == 0 && n1 == 1) return rand() % 2;
        return rand() % (n1 - n0) + n0;
}
 
// ������� ������ �������
void cls()
{
        COORD org = {0,0};
        DWORD res; 
		// ������� FillConsoleOutputCharacter ���������� ������, ������������ � �������� ����������� � �������� ������ �������, �������� ����� ���.
		//  BOOL FillConsoleOutputCharacter(
		//	HANDLE hConsoleOutput,			      // ���������� ��������� ������
		//	TCHAR cCharacter,					  // ������
		//	DWORD nLength,						  // ����� �����
		//	COORD dwWriteCoord,					  // ��������� ����������
		//	DWORD lpNumberOfCharsWritten		  // ����� ����� ��� ������
		//);
		FillConsoleOutputCharacter(conout, ' ', info.dwSize.X*info.dwSize.Y, org, &res);
}
 
// ������� �� ����� ������ � ������� � � �
void writeat (int x, int y, char c)
{
// ����������� ����� �� ����� ��� ������ ��������
		//WaitForSingleObject ����, ����� ������, ����� �������� ��� ������� ������ ����������, �������� � ���������� ��������� (signaled state).
        //������ �������� ������ ����� �������� � �������������. ����� ����� �����, ������� ����������� �������� INFINITE. 
	    //���� ������� ����, ��������� �� ��������� � ����� ��������, � ���������� ���������� ����������.
		WaitForSingleObject(screenlock, INFINITE);
        COORD pos = {x, y};
        DWORD res;
		//������� WriteConsoleOutputCharacter �������� ��� �������� � ���������������� ������ ��������� ������ �������, ������������ � �������� �����.
		//BOOL WriteConsoleOutputCharacter(
		//	HANDLEhConsoleOutpu,           // ���������� ��������� ������
		//	LPCTSTR lpCharacter,           // �������
		//	DWORD nLength,                 // ����� �������� ��� ������
		//	COORD dwWriteCoord,            // ���������� ������ ������
		//	DWORD lpNumberOfCharsWritten   // ����� ���������� �����
		//);
		WriteConsoleOutputCharacter(conout, &c , 2 , pos , &res );
		//ReleaseMutex ������� ����� ���������� �������. � ������ ������ ��������� ���������� ��������, �������� �� ����. � ������ ������ ������������ ����
        ReleaseMutex(screenlock);
}

// �������� ������� �� ������� (������� ����������� � ct)
int getakey(int &ct)
{
        INPUT_RECORD input; //��������� INPUT_RECORD ������������ ��� ����������� ���������� � ������� ���������� � ���������� ������� ������. 
        DWORD res;
        while (1)
        {
			   // ������� ReadConsoleInput ������ ������ �� ����������� ������ ����� � ������� �� �� ������.
			   //BOOL ReadConsoleInput(
					//HANDLE hConsoleInput,    // ���������� ������ ����� �������
					//INPUT_RECORD lpBuffer , // ����� ������
					//DWORD nLength ,          // ����� ������� ��� ������
					//DWORD lpNumberOfEventsRead // ����� ����������� �������
			   //);
               ReadConsoleInput (conin, &input, 1, &res);
               // ������������ ������ �������
               if (input.EventType != KEY_EVENT) continue;

			   // ��������� KEY_EVENT_RECORD ������������ ��� ��������� ������� ������� � ���������� ��������� INPUT_RECORD.
			   // bKeyDown - ����� TRUE ���� ������� ������, ����� FALSE.
			   // wRepeatCount ����� �������� ������� �������. ��������, ����� ������� ������, �� ������ �������� ����
			   // ��������� � ���� ������ ������ 1, ���� ��������� � ������ 5, ��� ��������� ��������� � ��������� �������, ���� ������ 1.
			   // wVirtualKeyCode ����������� ��� �������, ������������ ������ ������� � ����������� �� ���������� �����.
				  // ������������ ������� ���������� ������, ��� ���������� ������ �������
			   if (!input.Event.KeyEvent.bKeyDown) continue;
               ct=input.Event.KeyEvent.wRepeatCount;
               return input.Event.KeyEvent.wVirtualKeyCode;
        }
}
 
// ��������� ���������� ^�. ^Break, � �.�.
BOOL WINAPI ctrl (DWORD type)
{
        exit(0);
        return TRUE; // �� ���������� ������� ����
}
 
// ���������� ������ � �������� ������� ������
int getat(int x, int y)
{
        char c;
        DWORD res;
        COORD org={x, y};
        // ����������� ������ � ������� �� ��� ���, ���� ��������� �� ����� ���������
        WaitForSingleObject(screenlock, INFINITE);
		// ������� ReadConsoleOutputCharacter �������� ��� �������� �� ���������������� ����� ��������� ������ �������, ������������ � �������� �����.
        // BOOL ReadConsoleOutputCharacter(
			//HANDLE hConsoleOutput,      // ���������� ��������� ������
			//LPTSTR lpCharacter,         // ���������� �����
			//DWORD nLength,              // ����� ����� ��� ������
			//COORD dwReadCoord,          // ���������� ������ ������
			//LPDWORD lpNumberOfCharsRead // ����� ����������� �����
		//);
		ReadConsoleOutputCharacter(conout, &c, 1, org, &res);
        ReleaseMutex(screenlock); // unlock
        return c;
}
 
 
// ���������� ���� � ��������� ���� � ��������� ������� ���������� ����
void score(void)
{
        char s[128];   // ����� � ������� ����� ������������� ������ �-� sprintf_s
        sprintf_s(s, "Thread War! hits:%d  misses:%d", hit, miss); // ��������� ������ 
        SetConsoleTitle(s);		// �������� ��������� ����������� ���� �� ������ s
        if (miss>=30)		// ���� ����� �������� ������ 30 
        {
			   // EnterCriticalSection - ���������� ������ ����������� ������ 
			   // 1-� �������� - LPCRITICAL_SECTION lpCriticalSection ��������� �� ���������� ����������� ������
               EnterCriticalSection(&gameover);
			   // ������� SuspendThread ���������������� ������ ��������� ������.
			   // 1-� �������� - HANDLE hThread ���������� ������
               SuspendThread(mainthread); // stop main thread
			   //������� MessageBox �������, ���������� �� ������ � ���������� ���� ���������. ���� ��������� 
			   //�������� ������������ ���������� ��������� � ���������, ���� ����� ���������� ���������������� ������� � ��������� ������.
			   //int MessageBox(
			   //	HWND hWnd,				//���������� ���� ���������, ������� ������� ���� ���������. ���� ���� �������� - ����� (NULL), ���� ��������� �� ����� ���� ���������.
			   //	LPCTSTR lpText,			//��������� �� ���������� ������ � ����� � �����, ������� �������� ��������� ������������ �� ������.
			   //	LPCTSTR lpCaption,      //��������� �� ���������� ������ � ����� � �����, ������� �������� ��������� ����������� ���� (���� ���������). ���� ���� �������� - ����� (NULL), ������������ �������� �� ��������� ��������� Error
			   //	UINT uType				//������������� ���������� � ����� ������ ����������� ����.
			   //);
			   //MB_OK	���� ��������� �������� ���� ��������� ������: OK. ��� - �������� �� ���������.
			   //MB_SETFOREGROUND	���� ��������� ���������� ������������������ �����.
			   MessageBox(NULL, "Game Over!" , "Thread War", MB_OK|MB_SETFOREGROUND);
			   //������� exit ��������� ��������� �� ����� C++.
               exit(0); // �� ������� �� ����������� ������
        }
        if ((hit + miss) % 20 == 0)
			   // InterlockedDecrement �������� ��������� ���������� ���������� �� 1
			   // 1-� �������� - ���������� ��� ����������
               InterlockedDecrement(&delayfactor); // ������ ���� ilock
}
 
char badchar[] = "-\\|/";   // ������ ��������� ���������� 
 
// ��� ����� ����������
void badguy(void *_y)
{
        int y = (int)_y; // ��������� ���������� �
        int dir;
        int x;
        // �������� � ���������� �����, ������ � ���������� ������
        x = y%2 ? 0 : info.dwSize.X;
        // ���������� ����������� � ����������� �� ��������� �������
        dir = x ? -1 : 1;
        // ���� ��������� ��������� � �������� ������
        while ((dir == 1&&x != info.dwSize.X)||(dir == -1&&x != 0))
        {
               int dly;
               BOOL hitme = FALSE;
               // �������� �� ��������� (����?)
               if (getat(x, y) == '*') hitme = TRUE;
               // ����� ������� �� �����
               writeat(x, y, badchar[x % 4]);
               // ��� ���� �������� �� ���������
               if (getat(x, y)=='*') hitme=TRUE;
               // �������� �� ��������� ����� ���������
               //  ���������� �������
               if (delayfactor < 3) dly = 3;
               else dly = delayfactor + 3;
               for (int i = 0; i < dly; i++)
               {
                       Sleep(40);
                       if (getat(x, y) == '*')
                       {
                               hitme = TRUE;
                               break;
                       }
               }
               writeat(x, y, ' ');
// ��� ���� �������� �� ���������
               if (getat(x, y) == '*') hitme = TRUE;
               if (hitme)
               {
                       // � ���������� ������!
                       MessageBeep(-1);
                       InterlockedIncrement(&hit) ;
                       score();
                       _endthread();
               }
               x += dir;
        }
// ��������� ������!
		// InterlockedIncrement �������� ����������� ���������� ���������� �� 1
		// 1-� �������� - ���������� ��� ����������
        InterlockedIncrement(&miss) ;
        score();
}
 
// ���� ����� ���������� ��������� ������� �����������
void badguys(void *)
{
// ���� ������� � ������ ���� � ������� 15 ������
	    //������� WaitForSingleObject (link is external)������������� ���������� ��������� �� ��� ��� ���� ������ , ������������� �������� ������� 
	    //� ������� ,�� �������� � "����������" ��������� (� ��������� ���� �������� ���� Handle - "���������" ������ (����) ,�� ������� ��������� 
	    //���������� ���� ������, � ������ �������� ��� �������� ,�� ���������� ������ ���� ������, Handle �������� �� �������� ) - �� �� ������ ���������� ���������� ���������.
        WaitForSingleObject(startevt, 15000);
        // ������� ���������� �����
        // ������ 5 ������ ���������� ���� �������
        // ���������� � ������������ �� 1 �� 10
        while (1)
        {
               if (random(0,100) < (hit + miss)/25 + 20)
               // �� �������� ����������� �������������
               _beginthread(badguy, 0, (void *)(random(1,10)));
               Sleep(1000); // ������ �������
        }
}
 
// ��� ����� ����
// ������ ���� - ��� ��������� �����
void bullet(void *_xy_)
{
        COORD xy = *(COORD *)_xy_;
        if (getat(xy.X, xy.Y) == '*') return; // ����� ��� ���� ����
        // ���� ���������
        // ��������� �������
        // ���� ������� ����� 0, �������� �� ����������
        if (WaitForSingleObject(bulletsem, 0) == WAIT_TIMEOUT) return;
 
        while (--xy.Y)
        {
               writeat(xy.X, xy.Y, '*'); // ���������� ����
               Sleep(100);
               writeat(xy.X, xy.Y, ' ');    // ������� ����
        }
		
		//BOOL ReleaseSemaphore
		//(
		//	HANDLE hSemaphore,		// ���� ��������
		//	LONG lReleaseCount, 	// �� ������� �������� �������
		//	LPLONG lpPreviousCount	// ���������� ��������
		//);
        // ������� ������.- �������� 1 � ��������
        ReleaseSemaphore ( bulletsem, 1, NULL);
}
// �������� ���������
void main()
{
		//HANDLE - ����������, ��������������� ��� �������� ��������� ��������. 
		//�� ����� ���� ���� ��� ������������ ����� �� ��� ����, ��� ��������� �� void, �.�. ��� �� �� ����� ���.
        HANDLE me;
        
		//������� GetStdHandle ��������� ���������� ��� ������������ ����� ������, ������������ ������ ��� ����������� ������ ����������.
		//STD_INPUT_HANDLE ���������� ������������ ���������� ����� ������. �������, ��� - ���������� ����������� ������ �����, CONIN$.
		//STD_OUTPUT_HANDLE ���������� ���������� ������������ ������. �������, ��� - ���������� ��������� ��������� ������ �������, CONOUT$. 
        // ��������� ���������� ����������
		conin = GetStdHandle(STD_INPUT_HANDLE ); 
        conout = GetStdHandle(STD_OUTPUT_HANDLE); 

		//������� SetConsoleCtrlHandler ��������� ��� ������� ������������ ���������� ������� 
		//HandlerRoutine �� ������ ������� ������������ ������ �������� ��� ����������� ��������.
        // 1-� �������� PHANDLER_ROUTINE HandlerRoutine  ���������� �������
		// 2-� �������� BOOL Add  �������� ��� ������� ����������
//		SetConsoleCtrlHandler(ctrl, TRUE);

		//������� SetConsoleMode ������������� ����� ����� ������ ������ ����� ������� ��� ������ ������ ��������� ������ �������.
		//1-� �������� -  HANDLE hConsoleHandle  ���������� ��������� ������ ��� ������ ����� �������
		//2-� �������� -  DWORD dwMode ����� ����� ��� ������ ������
		//ENABLE_WINDOW_INPUT ������������ ������������, ����� �������� ������ ��������� ������ ������� ���������� � ������ ����� �������. 
        SetConsoleMode(conin, ENABLE_WINDOW_INPUT);

		//������� GetCurrentThread ��������� �������� ����������������� ��� �������� ������.
        me = GetCurrentThread(); // �� �������� �������� ������������

		//������� DuplicateHandle ������ ����� ����������� �������. ���������������� ���������� ��������� � ���� �� ������ �������, ��� � �������� ����������. 
		//�������, ����� ��������� ������� ���������� ����� ��� �����������. ��������, ���������� �����, ������������������ ��� �������� �����, �������� ������ ����� � ��� �� ��� ����� ������������.
		//  BOOL DuplicateHandle(
		//  HANDLE hSourceProcessHandle,  // ���������� �������� - ��������� 
		//  HANDLEhSourceHandle,          // �������� �����������
		//  HANDLE hTargetProcessHandle,  // ���������� �������� ��������
		//  LPHANDLE lpTargetHandle,      // �������� �����������
		//  DWORD dwDesiredAccess,        // ������ �������
		//  BOOL bInheritHandle,          // �������� ������������ �����������
		//  DWORD dwOptions               // �������������� ��������
		//); 
		//������� GetCurrentProcess ��������� ���������������� ��� �������� ��������.
		//DUPLICATE_SAME_ACCESS ���������� �������� dwDesiredAccess. ���������������� ���������� ����� ��� �� ����� ������, ��� � �������� ����������. 
		// �������� ���������������� �� �������� ���������� �������� ������
        DuplicateHandle(GetCurrentProcess(), me, GetCurrentProcess(), &mainthread, 0, FALSE, DUPLICATE_SAME_ACCESS);

		
		//CreateEvent ������� ��� ��������� ����������� ��� ����������� ������ �������.
		//HANDLE CreateEvent
		//(
		//	LPSECURITY_ATTRIBUTES lpEventAttributes,	// ������� ������
		//	BOOL bManualReset,							// ��� ������ TRUE - ������
		//	BOOL bInitialState,							// ��������� ��������� TRUE - ����������
		//	LPCTSTR lpName								// ��� �������
		//);
        startevt=CreateEvent(NULL, TRUE, FALSE, NULL);

		// CreateMutex - ������ ������
		//HANDLE CreateMutex
		//(
		//	LPSECURITY_ATTRIBUTES lpMutexAttributes,	// ������� �������������
		//	BOOL bInitialOwner,							// ���� ���������� ���������
		//	LPCTSTR lpName								// ��� �������
		//);	
        screenlock=CreateMutex(NULL, FALSE, NULL);

		// InitializeCriticalSection �������������� ����������� ������
		// 1-� �������� - ��������� �� ���������� ����������� ������
        InitializeCriticalSection ( &gameover);

		//CreateSemaphore - ������ �������
		//HANDLE CreateSemaphore
		//(
		//	LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,	// ������� �������
		//	LONG lInitialCount,								// ������������������ ��������� ��������� ��������
		//	LONG lMaximumCount,								// ������������ ���������� ���������
		//	LPCTSTR lpName									// ��� �������
		//);
        bulletsem=CreateSemaphore(NULL, 3, 3, NULL);

		//������� GetConsoleScreenBufferInfo ��������� ���������� � �������� �������� ������ �������.
		//BOOL GetConsoleScreenBufferInfo
		//(
		// HANDLE hConsoleOutput,								 // ���������� ��������� ������
		// PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo // ���������� �� ���. ������				   
		//);
        GetConsoleScreenBufferInfo(conout, &info);
 
        // ���������������� ����������� ���������� �� �����
        score();

        // ��������� ��������� ��������� �����
        srand((unsigned)time(NULL));

        cls(); // �� ����� ���� �� �����

        // ��������� ��������� ������� �����
        int y=info.dwSize.Y-1;
        int x=info.dwSize.X/2;
        // ��������� ����� badguys; ������ �� ������ �� ��� ���,
        // ���� �� ���������� ������� ��� ������� 15 ������
		// ������� _beginthread ������������� ��� �������� ������ ������
		// 1-� �������� - ��������� ����� ���������, ������� �������� ���������� ������ ������. 
		// 2-� �������� - ������ ����� ������ ������ ��� 0.
		// 3-� �������� - ������ ����������, ������� ������ ���� ������� ������ ������, ��� NULL.
        _beginthread (badguys, 0, NULL); // �������� ���� ����
        while (1)
        {
               int c, ct;
               writeat(x, y, '|');		// ���������� �����
               c = getakey(ct);			// �������� ������
               switch (c)
               {
               case VK_SPACE:
               {
                       static COORD xy;
					   xy.X = x;
                       xy.Y = y;
                       _beginthread(bullet, 0, (void *)&xy);
                       Sleep(100); // ���� ���� ����� ������� �� ��������� ����������  
					   break;
               }
               case VK_LEFT:  // ������� "�����!"
                       SetEvent(startevt);    // ����� badguys ��������
                       writeat(x, y, ' ');      // ������ � ������ �����
                       while (ct--)        // �������������
                               if (x) x--;
                       break;
               case VK_RIGHT: // ������� "������!"; ������ �� ��
                       SetEvent(startevt);
                       writeat(x, y, ' ');
                       while (ct--)
                               if (x != info.dwSize.X-1) x++;
                       break;
               }
        }
}
 
 