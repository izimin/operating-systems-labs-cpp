// ThreadWar.cpp : Defines the entry point for the console application.
//
 
#include "stdafx.h"
 
//      Простая компьютерная игра Thread War
//      Thread War'
//      Используйте клавиши "влево" и "вправо", чтобы перемещать пушку
//      клавиша "пробел" производит выстрел
//      Если 30 врагов уйдут с экрана неуничтоженными,  вы проиграли
//      Очки даются за каждого убитого противника
#include <windows.h>
#include <process.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
// Объекты синхронизации
HANDLE screenlock; // изменением экрана занимается только один поток
HANDLE bulletsem;  // можно выстрелить только три раза подряд
HANDLE startevt;     // игра начинается с нажатием клавиши "влево" или "вправо"
// conin - console input, coout - console output
HANDLE conin, conout;  // дескрипторы консоли
HANDLE mainthread; // Основной поток main
CRITICAL_SECTION gameover;
CONSOLE_SCREEN_BUFFER_INFO info; // информация о консоли
// количество попаданий и промахов
long hit = 0;
long miss = 0;
long delayfactor = 7; // фактор задержки для скорости пули
 
// Создание случайного числа от n0 до n1
int random(int n0, int n1)
{
        if (n0 == 0 && n1 == 1) return rand() % 2;
        return rand() % (n1 - n0) + n0;
}
 
// Очистка экрана консоли
void cls()
{
        COORD org = {0,0};
        DWORD res; 
		// Функция FillConsoleOutputCharacter записывает символ, начинающийся в заданных координатах в экранном буфере консоли, заданное число раз.
		//  BOOL FillConsoleOutputCharacter(
		//	HANDLE hConsoleOutput,			      // дескриптор экранного буфера
		//	TCHAR cCharacter,					  // символ
		//	DWORD nLength,						  // число ячеек
		//	COORD dwWriteCoord,					  // начальные координаты
		//	DWORD lpNumberOfCharsWritten		  // число ячеек для записи
		//);
		FillConsoleOutputCharacter(conout, ' ', info.dwSize.X*info.dwSize.Y, org, &res);
}
 
// вывести на экран символ в позицию х и у
void writeat (int x, int y, char c)
{
// Блокировать вывод на экран при помощи мьютекса
		//WaitForSingleObject ждет, когда объект, хэндл которого был передан первым аргументом, перейдет в сигнальное состояние (signaled state).
        //Второй аргумент задает время ожидания в миллисекундах. Можно ждать вечно, передав специальное значение INFINITE. 
	    //Если указать ноль, процедура не переходит в режим ожидания, а возвращает управление немедленно.
		WaitForSingleObject(screenlock, INFINITE);
        COORD pos = {x, y};
        DWORD res;
		//Функция WriteConsoleOutputCharacter копирует ряд символов в последовательные ячейки экранного буфера консоли, начинающиеся в заданном месте.
		//BOOL WriteConsoleOutputCharacter(
		//	HANDLEhConsoleOutpu,           // дескриптор экранного буфера
		//	LPCTSTR lpCharacter,           // символы
		//	DWORD nLength,                 // число символов для записи
		//	COORD dwWriteCoord,            // координаты первой ячейки
		//	DWORD lpNumberOfCharsWritten   // число записанных ячеек
		//);
		WriteConsoleOutputCharacter(conout, &c , 2 , pos , &res );
		//ReleaseMutex анлочит ранее залоченный мьютекс. В случае успеха процедура возвращает значение, отличное от нуля. В случае ошибки возвращается ноль
        ReleaseMutex(screenlock);
}

// Получить нажатие на клавишу (счетчик повторейний в ct)
int getakey(int &ct)
{
        INPUT_RECORD input; //Структура INPUT_RECORD используется для возвращения информации о входных сообщениях в консольном входном буфере. 
        DWORD res;
        while (1)
        {
			   // Функция ReadConsoleInput читает данные из консольного буфера ввода и удаляет их из буфера.
			   //BOOL ReadConsoleInput(
					//HANDLE hConsoleInput,    // дескриптор буфера ввода консоли
					//INPUT_RECORD lpBuffer , // буфер данных
					//DWORD nLength ,          // число записей для чтения
					//DWORD lpNumberOfEventsRead // число прочитанных записей
			   //);
               ReadConsoleInput (conin, &input, 1, &res);
               // игнорировать другие события
               if (input.EventType != KEY_EVENT) continue;

			   // Структура KEY_EVENT_RECORD используется для получения входных событий в консольной структуре INPUT_RECORD.
			   // bKeyDown - Равно TRUE если клавиша нажата, иначе FALSE.
			   // wRepeatCount Число повторов нажатия клавиши. Например, когда клавиша нажата, вы можете получить пять
			   // сообщений с этим членом равным 1, одно сообщение с равным 5, или несколько сообщений с элементом большим, либо равным 1.
			   // wVirtualKeyCode Виртуальный код клавиши, определяющий данную клавишу в независимой от устройства форме.
				  // игнорировать события отпускания клавиш, нас интересуют только нажатия
			   if (!input.Event.KeyEvent.bKeyDown) continue;
               ct=input.Event.KeyEvent.wRepeatCount;
               return input.Event.KeyEvent.wVirtualKeyCode;
        }
}
 
// Обработка комбинаций ^С. ^Break, и т.п.
BOOL WINAPI ctrl (DWORD type)
{
        exit(0);
        return TRUE; // не достижимый участок кода
}
 
// Определить символ в заданной позиции экрана
int getat(int x, int y)
{
        char c;
        DWORD res;
        COORD org={x, y};
        // Блокировать доступ к консоли до тех пор, пока процедура не будет выполнена
        WaitForSingleObject(screenlock, INFINITE);
		// Функция ReadConsoleOutputCharacter копирует ряд символов из последовательных ячеек экранного буфера консоли, начинающихся в заданном месте.
        // BOOL ReadConsoleOutputCharacter(
			//HANDLE hConsoleOutput,      // дескриптор экранного буфера
			//LPTSTR lpCharacter,         // символьный буфер
			//DWORD nLength,              // число ячеек для чтения
			//COORD dwReadCoord,          // координаты первой ячейки
			//LPDWORD lpNumberOfCharsRead // число прочитанных ячеек
		//);
		ReadConsoleOutputCharacter(conout, &c, 1, org, &res);
        ReleaseMutex(screenlock); // unlock
        return c;
}
 
 
// Отобразить очки в заголовке окна и проверить условие завершения игры
void score(void)
{
        char s[128];   // Буфер в который будет сформированна строка ф-й sprintf_s
        sprintf_s(s, "Thread War! hits:%d  misses:%d", hit, miss); // Формируем строку 
        SetConsoleTitle(s);		// Изменяем заголовок консольного окна на строку s
        if (miss>=30)		// Если число промахов больше 30 
        {
			   // EnterCriticalSection - объявления начала критической секции 
			   // 1-й параметр - LPCRITICAL_SECTION lpCriticalSection указатель на переменную критическая секция
               EnterCriticalSection(&gameover);
			   // Функция SuspendThread приостанавливает работу заданного потока.
			   // 1-й параметр - HANDLE hThread дескриптор потока
               SuspendThread(mainthread); // stop main thread
			   //Функция MessageBox создает, показывает на экране и использует окно сообщения. Окно сообщения 
			   //содержит определяемое программой сообщение и заголовок, плюс любая комбинация предопределенных значков и командных кнопок.
			   //int MessageBox(
			   //	HWND hWnd,				//Дескриптор окна владельца, которое создает окно сообщения. Если этот параметр - ПУСТО (NULL), окно сообщения не имеет окна владельца.
			   //	LPCTSTR lpText,			//Указатель на символьную строку с нулем в конце, которая содержит сообщение показываемое на экране.
			   //	LPCTSTR lpCaption,      //Указатель на символьную строку с нулем в конце, которая содержит заголовок диалогового окна (окна сообщения). Если этот параметр - ПУСТО (NULL), используется заданный по умолчанию заголовок Error
			   //	UINT uType				//Устанавливает содержание и режим работы диалогового окна.
			   //);
			   //MB_OK	Окно сообщения содержит одну командную кнопку: OK. Это - значение по умолчанию.
			   //MB_SETFOREGROUND	Окно сообщения становится высокоприоритетным окном.
			   MessageBox(NULL, "Game Over!" , "Thread War", MB_OK|MB_SETFOREGROUND);
			   //Функция exit завершает программу на языке C++.
               exit(0); // не выходит из критической секции
        }
        if ((hit + miss) % 20 == 0)
			   // InterlockedDecrement беопасно уменьшает содержимое переменной на 1
			   // 1-й параметр - переменная для уменьшения
               InterlockedDecrement(&delayfactor); // должен быть ilock
}
 
char badchar[] = "-\\|/";   // Массив состояний противника 
 
// это поток противника
void badguy(void *_y)
{
        int y = (int)_y; // случайная координата у
        int dir;
        int x;
        // нечетные у появляются слева, четные у появляются справа
        x = y%2 ? 0 : info.dwSize.X;
        // установить направление в зависимости от начальной позиции
        dir = x ? -1 : 1;
        // пока противник находится в пределах экрана
        while ((dir == 1&&x != info.dwSize.X)||(dir == -1&&x != 0))
        {
               int dly;
               BOOL hitme = FALSE;
               // проверка на попадание (пуля?)
               if (getat(x, y) == '*') hitme = TRUE;
               // вывод символа на экран
               writeat(x, y, badchar[x % 4]);
               // еще одна проверка на попадание
               if (getat(x, y)=='*') hitme=TRUE;
               // проверка на попадание через небольшие
               //  промежутки времени
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
// еще одна проверка на попадание
               if (getat(x, y) == '*') hitme = TRUE;
               if (hitme)
               {
                       // в противника попали!
                       MessageBeep(-1);
                       InterlockedIncrement(&hit) ;
                       score();
                       _endthread();
               }
               x += dir;
        }
// противник убежал!
		// InterlockedIncrement беопасно увеличивает содержимое переменной на 1
		// 1-й параметр - переменная для увеличения
        InterlockedIncrement(&miss) ;
        score();
}
 
// этот поток занимается созданием потоков противников
void badguys(void *)
{
// ждем сигнала к началу игры в течение 15 секунд
	    //Функция WaitForSingleObject (link is external)останавливает выполнения программы до тех пор пока объект , идентификатор которого передан 
	    //в функцию ,не окажется в "сигнальном" состоянии (в частности если передать сюда Handle - "держатель" потока (нити) ,то функция остановит 
	    //выполнения того потока, в рамках которого она запущена ,до завершения работы того потока, Handle которого ей передали ) - но не дольше указанного временного интервала.
        WaitForSingleObject(startevt, 15000);
        // создаем случайного врага
        // каждые 5 секунд появляется шанс создать
        // противника с координатами от 1 до 10
        while (1)
        {
               if (random(0,100) < (hit + miss)/25 + 20)
               // со временем вероятность увеличивается
               _beginthread(badguy, 0, (void *)(random(1,10)));
               Sleep(1000); // каждую секунду
        }
}
 
// Это поток пули
// каждая пуля - это отдельный поток
void bullet(void *_xy_)
{
        COORD xy = *(COORD *)_xy_;
        if (getat(xy.X, xy.Y) == '*') return; // здесь уже есть пуля
        // надо подождать
        // Проверить семафор
        // если семафор равен 0, выстрела не происходит
        if (WaitForSingleObject(bulletsem, 0) == WAIT_TIMEOUT) return;
 
        while (--xy.Y)
        {
               writeat(xy.X, xy.Y, '*'); // отобразить пулю
               Sleep(100);
               writeat(xy.X, xy.Y, ' ');    // стереть пулю
        }
		
		//BOOL ReleaseSemaphore
		//(
		//	HANDLE hSemaphore,		// хенд семафора
		//	LONG lReleaseCount, 	// на сколько изменять счетчик
		//	LPLONG lpPreviousCount	// предыдущее значение
		//);
        // выстрел сделан.- добавить 1 к семафору
        ReleaseSemaphore ( bulletsem, 1, NULL);
}
// Основная программа
void main()
{
		//HANDLE - дескриптор, предназначенный для описания различных объектов. 
		//На самом деле этот тип представляет собой ни что иное, как указатель на void, т.е. как бы на любой тип.
        HANDLE me;
        
		//Функция GetStdHandle извлекает дескриптор для стандартного ввода данных, стандартного вывода или стандартной ошибки устройства.
		//STD_INPUT_HANDLE Дескриптор стандартного устройства ввода данных. Вначале, это - дескриптор консольного буфера ввода, CONIN$.
		//STD_OUTPUT_HANDLE Дескриптор устройства стандартного вывода. Вначале, это - дескриптор активного экранного буфера консоли, CONOUT$. 
        // Настройка глобальных переменных
		conin = GetStdHandle(STD_INPUT_HANDLE ); 
        conout = GetStdHandle(STD_OUTPUT_HANDLE); 

		//Функция SetConsoleCtrlHandler добавляет или удаляет определяемую программой функцию 
		//HandlerRoutine из списка функций обработчиков особой ситуации для вызывающего процесса.
        // 1-й параметр PHANDLER_ROUTINE HandlerRoutine  обработчик функции
		// 2-й параемтр BOOL Add  добавить или удалить обработчик
//		SetConsoleCtrlHandler(ctrl, TRUE);

		//Функция SetConsoleMode устанавливает режим ввода данных буфера ввода консоли или режима вывода экранного буфера консоли.
		//1-й параметр -  HANDLE hConsoleHandle  дескриптор экранного буфера или буфера ввода консоли
		//2-й параметр -  DWORD dwMode режим ввода или вывода данных
		//ENABLE_WINDOW_INPUT Пользователь воздействует, чтобы изменить размер экранного буфера консоли записанный в буфере ввода консоли. 
        SetConsoleMode(conin, ENABLE_WINDOW_INPUT);

		//Функция GetCurrentThread извлекает значение псевдодескриптора для текущего потока.
        me = GetCurrentThread(); // не является реальным дескриптором

		//Функция DuplicateHandle делает копию дескриптора объекта. Продублированный дескриптор относится к тому же самому объекту, что и исходный дескриптор. 
		//Поэтому, любое изменение объекта отражается через оба дескриптора. Например, дескриптор файла, зарегистрированный для текущего файла, является всегда одним и тем же для обоих дескрипторов.
		//  BOOL DuplicateHandle(
		//  HANDLE hSourceProcessHandle,  // дескриптор процесса - источника 
		//  HANDLEhSourceHandle,          // дубликат дескриптора
		//  HANDLE hTargetProcessHandle,  // дескриптор целевого процесса
		//  LPHANDLE lpTargetHandle,      // дубликат дескриптора
		//  DWORD dwDesiredAccess,        // запрос доступа
		//  BOOL bInheritHandle,          // параметр наследования дескриптора
		//  DWORD dwOptions               // необязательные действия
		//); 
		//Функция GetCurrentProcess извлекает псевдодескриптор для текущего процесса.
		//DUPLICATE_SAME_ACCESS Игнорирует параметр dwDesiredAccess. Продублированный дескриптор имеет тот же самый доступ, что и исходный дескриптор. 
		// изменить псевдодескриптор на реальный дескриптор текущего потока
        DuplicateHandle(GetCurrentProcess(), me, GetCurrentProcess(), &mainthread, 0, FALSE, DUPLICATE_SAME_ACCESS);

		
		//CreateEvent Создает или открывает именованный или неназванный объект события.
		//HANDLE CreateEvent
		//(
		//	LPSECURITY_ATTRIBUTES lpEventAttributes,	// атрибут защиты
		//	BOOL bManualReset,							// тип сброса TRUE - ручной
		//	BOOL bInitialState,							// начальное состояние TRUE - сигнальное
		//	LPCTSTR lpName								// имя обьекта
		//);
        startevt=CreateEvent(NULL, TRUE, FALSE, NULL);

		// CreateMutex - создаёт мютекс
		//HANDLE CreateMutex
		//(
		//	LPSECURITY_ATTRIBUTES lpMutexAttributes,	// атрибут безопастности
		//	BOOL bInitialOwner,							// флаг начального владельца
		//	LPCTSTR lpName								// имя объекта
		//);	
        screenlock=CreateMutex(NULL, FALSE, NULL);

		// InitializeCriticalSection инициализирует критическую секцию
		// 1-й параметр - указатель на переменную критическая секция
        InitializeCriticalSection ( &gameover);

		//CreateSemaphore - создаёт семафор
		//HANDLE CreateSemaphore
		//(
		//	LPSECURITY_ATTRIBUTES lpSemaphoreAttributes,	// атрибут доступа
		//	LONG lInitialCount,								// инициализированное начальное состояние счетчика
		//	LONG lMaximumCount,								// максимальное количество обращений
		//	LPCTSTR lpName									// имя объекта
		//);
        bulletsem=CreateSemaphore(NULL, 3, 3, NULL);

		//Функция GetConsoleScreenBufferInfo извлекает информацию о заданном экранном буфере консоли.
		//BOOL GetConsoleScreenBufferInfo
		//(
		// HANDLE hConsoleOutput,								 // дескриптор экранного буфера
		// PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo // информация об экр. буфере				   
		//);
        GetConsoleScreenBufferInfo(conout, &info);
 
        // Инициализировать отображение информации об очках
        score();

        // Настроить генератор случайных чисел
        srand((unsigned)time(NULL));

        cls(); // на самом деле не нужно

        // установка начальной позиции пушки
        int y=info.dwSize.Y-1;
        int x=info.dwSize.X/2;
        // запустить поток badguys; ничего не делать до тех пор,
        // пока не произойдет событие или истекут 15 секунд
		// Функции _beginthread предназначена для создания нового потока
		// 1-й параметр - Начальный адрес процедуры, который начинает выполнение нового потока. 
		// 2-й параметр - Размер стека нового потока или 0.
		// 3-й параметр - Список аргументов, который должен быть передан новому потоку, или NULL.
        _beginthread (badguys, 0, NULL); // основной цикл игры
        while (1)
        {
               int c, ct;
               writeat(x, y, '|');		// нарисовать пушку
               c = getakey(ct);			// получить символ
               switch (c)
               {
               case VK_SPACE:
               {
                       static COORD xy;
					   xy.X = x;
                       xy.Y = y;
                       _beginthread(bullet, 0, (void *)&xy);
                       Sleep(100); // дать пуле время улететь на некоторое расстояние  
					   break;
               }
               case VK_LEFT:  // команда "влево!"
                       SetEvent(startevt);    // поток badguys работает
                       writeat(x, y, ' ');      // убрать с экрана пушку
                       while (ct--)        // переместиться
                               if (x) x--;
                       break;
               case VK_RIGHT: // команда "вправо!"; логика та же
                       SetEvent(startevt);
                       writeat(x, y, ' ');
                       while (ct--)
                               if (x != info.dwSize.X-1) x++;
                       break;
               }
        }
}
 
 