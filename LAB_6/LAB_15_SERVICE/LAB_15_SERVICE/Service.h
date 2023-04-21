#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>

#define SERVICENAME L"skm15"
#define TRACEPATH "C:\\univer\\semestr_6\\OS\\labs\\lab15\\HTService\\log.trace"

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv);
VOID WINAPI ServiceHandler(DWORD fdwControl);

void trace(const char* msg, int r = std::ofstream::app);