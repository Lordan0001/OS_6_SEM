// dllmain.cpp : Определяет точку входа для приложения DLL.
#include "pch.h"
#include <fstream>
#include "INSTALL.h"
#define SEQ LONG __XXCSeq=InterlockedIncrement(&Seq)
#define LOG(x,y) LogCOM<<__XXCSeq<<":"<<x<<y<<std::endl

#define SEQHT LONG __XXCSeqHT=InterlockedIncrement(&SeqHT)
#define LOGHT(x,y) LogHT<<__XXCSeqHT<<":"<<(x)<<(y)<<std::endl



HMODULE hmodule;
LONG Seq = 0;
std::fstream LogCOM;
LONG SeqHT = 0;
std::fstream LogHT;

ULONG g_Components = 0;
ULONG g_ServerLocks = 0;

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        hmodule = hModule;
        LogCOM.open("D:\\lab7\\LogsCom.txt", std::ios_base::out);
        LogHT.open("D:\\lab7\\LogsComHT.txt", std::ios_base::out);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        LogCOM.close();
        LogHT.close();
        break;
    }
    return TRUE;
}


