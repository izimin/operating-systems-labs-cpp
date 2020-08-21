#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctime>
#include <windows.h>
#include <io.h>

#define size_buf 1024

using namespace std;

void GenerationFile(size_t sizeFile)
{
	char *buf = new char[size_buf];
	ofstream fout("testFile.txt", ios::ate);

	for (int i = 0; i < size_buf; i++)
	{
		buf[i] = 'a' - (i % 24);
	}

	for (int i = 0; i < 1024 * sizeFile; i++)
	{
		fout.write(buf, size_buf);
	}
}

double CopyByStream(size_t sizeFile)
{
	unsigned int start_time =  clock();

    char *buf = new char[size_buf];

    ifstream fin("testFile.txt");
    ofstream fout("newFile1.txt", ios::ate);
  
	for (int i = 0; i < 1024 * sizeFile; i++) 
	{
		fin.read(buf, size_buf);					// Считываем в массив данные из файла, размером 1024 байта
        fout.write(buf, size_buf);					// Заносим данные в файл, размером 1024 байта
    }

    delete[] buf;
    fin.close();
    fout.close();

	unsigned int finish_time =  clock();
	return (finish_time - start_time) / 1000.0;
}

double CopyByFILE(size_t sizeFile) 
{
	unsigned int start_time =  clock();

	char *buf = new char[size_buf];
	
	FILE *fin = nullptr;
	fopen_s(&fin, "testFile.txt", "rt");

	FILE *fout = nullptr;
	fopen_s(&fout,"newFile2.txt", "wt");

	for (int i = 0; i < 1024 * sizeFile; i++) 
	{
		fread(buf, 1, size_buf, fin);				// Считываем из файла 1 элемент равный буферу в 1024 байта (массив)  
		fwrite(buf, 1, size_buf, fout);				// Заносим данные в новый файл
	}

	fclose(fin);
	fclose(fout);
	delete[] buf;

	unsigned int finish_time =  clock();
	return (finish_time - start_time) / 1000.0;
}

double CopyByWinApi()
{
	// Если файл существут - удаляем
	if (_access("newFile3.txt", 0) != 1)		
	{
		DeleteFile(L"newFile3.txt");
	}

	unsigned int start_time =  clock();

    char *buf = new char[size_buf];

    HANDLE hSrc, hDst;

    hSrc = CreateFile(L"testFile.txt",GENERIC_READ, FILE_SHARE_READ,NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,0);
    hDst = CreateFile(L"newFile3.txt",GENERIC_WRITE, FILE_SHARE_WRITE,NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);

    int fileSize = GetFileSize(hSrc,NULL);

    DWORD buf1 = 0;
    DWORD buf2 = 0;

	for (int i = 0; i < fileSize / 1024; i++) 
	{
        ReadFile(hSrc, buf, size_buf, &buf1, NULL);
        WriteFile(hDst, buf, size_buf, &buf2, NULL);
    }

    CloseHandle(hSrc);
    CloseHandle(hDst);
	delete[] buf;

	unsigned int finish_time =  clock();
	return (finish_time - start_time) / 1000.0;
}

double CopyByMapping()
{
	// Если файл существут - удаляем
	if (_access("newFile4.txt", 0) != 1)
	{
		DeleteFile(L"newFile4.txt");
	}

	unsigned int start_time =  clock();

	struct TBuf
	{
		 char arr[1024];
	};
	typedef TBuf* PBuf;

    HANDLE hSrc, hDst, hMapFileIn, hMapFileOut;
	PBuf ptrIn, ptrOut;

    hSrc = CreateFile(L"testFile.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	hDst = CreateFile(L"newFile4.txt", GENERIC_WRITE | GENERIC_READ, FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, 0);

	int SrcSize = GetFileSize(hSrc, NULL);

	hMapFileIn = CreateFileMapping(hSrc, NULL, PAGE_READONLY, 0, 0, NULL);
	hMapFileOut = CreateFileMapping(hDst, NULL, PAGE_READWRITE, 0, SrcSize, NULL);

	ptrIn = (PBuf)MapViewOfFile(hMapFileIn, FILE_MAP_READ, 0, 0, 0);
	ptrOut = (PBuf)MapViewOfFile(hMapFileOut, FILE_MAP_WRITE, 0, 0, SrcSize);

	for (int i = 0; i < SrcSize / 1024; i++) 
	{ 
		*ptrOut = *ptrIn ;    // Или по красоте:  memcpy(ptrOut, ptrIn, size_buf);
		ptrOut++; ptrIn++;
	}

	UnmapViewOfFile(ptrIn);
	UnmapViewOfFile(ptrOut);
	CloseHandle(hMapFileIn);
	CloseHandle(hMapFileOut);
	CloseHandle(hSrc);
    CloseHandle(hDst);

	unsigned int finish_time =  clock();
	return (finish_time - start_time) / 1000.0;
}

int main()
{
	size_t fileSize;

	cout << "Enter size file: "; 
	cin >> fileSize;
	GenerationFile(fileSize);
	cout << "Time stream:  " << CopyByStream(fileSize) << endl;
	cout << "Time FILE*:   " << CopyByFILE(fileSize) << endl;
	cout << "Time winAPI:  " << CopyByWinApi() << endl;
	cout << "Time mapping:  " << CopyByMapping() << endl;
	return 0;
}