#pragma once

#include <afxmt.h>
#include <vector>
#include <Shlwapi.h>
#include <tchar.h>
#include <string>
#include <sstream>
#include <ctime>
#include <time.h>

enum
{
	TCP_PORT = 66666,
	MAX_BUF_SIZE = 1024
};


static const char s_HeadId = '&';
static const char s_CompleteId = '*';
static const char s_SeparatorId = '@';

//#define INI_PATH	".\\Settings.ini"

static float GetElapsedTime_ms(std::clock_t start)
{
	std::clock_t tmpTime = std::clock();
	clock_t timediff = tmpTime - start;
	float difftime = ((float)timediff) / ((float)CLOCKS_PER_SEC);
	difftime *= 1000.0;	//in ms
	return difftime;
}

static char* GetThisPath(char* dest, size_t destSize)
{
	if (!dest) return NULL;
	DWORD length = GetModuleFileNameA(NULL, dest, destSize);

	if (MAX_PATH > destSize) return NULL;

	PathRemoveFileSpecA(dest);

	return dest;
}





