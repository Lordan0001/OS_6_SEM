#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>

#define SERVICENAME L"OS15_HTService"
#define TRACEPATH "D:\\University\\Current\\OSSP\All\\new\\lab7\\lab7\\Release\\OS13_START.exe"

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
VOID WINAPI ServiceHandler(DWORD fdwControl);

void trace(const char* msg, int r = std::ofstream::app);