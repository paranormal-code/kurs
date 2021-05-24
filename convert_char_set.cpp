// convert_char_set.cpp : Defines the entry point for the console application.
// Конвертор для русских текстов между кодировками KOI-8, CP1251, DOS.

// Параметры запуска программы:
// 1й парметр - входная кодировка
// 2й параметр - выходная кодировка
// 3й параметр - входной файл
// 4й параметр - выходной файл



#include "stdafx.h"
#include "windows.h"
#include "convert.h"
#include "any_func.h"


int main(int argc, char* argv[])
{	
 if (argc != 5) return -1;

    SetThreadPriority((void*)GetCurrentThread(),THREAD_PRIORITY_HIGHEST);
	LONG time = GetTickCount(); //возвращает время работы в миллисекундах
	int InSize=Convert(argv);
	if (InSize == -1) return -1;
	time = GetTickCount() - time;
//выводим сообщение о том сколько времени работала программа
   char m[128] = {"Vremya raboty: "};
   itoa(time,&m[strlen(m)],10);
   strcat(&m[strlen(m)]," ms.");

  MessageBox(0,m,"All complete.",MB_OK | MB_SYSTEMMODAL);

  ZeroMemory(m,sizeof(m));

  itoa(InSize,m,10);

  strcat(&m[strlen(m)],"   ");

  itoa(time,&m[strlen(m)],10);

  strcat(&m[strlen(m)],"\x0D\x0A");

  WriteTime((char*)"info.txt",m);

	return 0;
}
