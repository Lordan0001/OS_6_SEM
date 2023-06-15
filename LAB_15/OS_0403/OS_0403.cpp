#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
#include <string>
#include "../OS13_COMlib/HTlib.h"
#pragma comment(lib, "..\\Release\\OS13_COMlib.lib")

const wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	size_t outSize;
	mbstowcs_s(&outSize, wc, cSize, c, cSize - 1);
	return wc;
}

int main(int argc, char** argv)
{
	HANDLE hf = NULL;
	try
	{
		if (!HTlib::OpenCOM()) throw "OpenCOM error";
		HTlib::HTHANDLE* HT = HTlib::Open(GetWC(argv[1]));
		if (HT == NULL) throw "Invalid handle";
		hf = CreateFile(L"D:\\os15\\delete.log", GENERIC_WRITE | GENERIC_READ, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hf == INVALID_HANDLE_VALUE) throw "INVALID_HANDLE_VALUE";
		SetFilePointer(hf, NULL, NULL, FILE_END);

		std::string key;
		HTlib::Element* deleting;
		if (!WriteFile(hf, "START DELETE\n", 13, NULL, NULL)) throw "WriteFile";
		for (int i = 1; i <= 9; i++)
		{
			if (HT->Addr == NULL) throw "HT IS CLOSEN";
			key = "key" + std::to_string(i);
			deleting = new HTlib::Element(key.c_str(), key.length());
			std::cout << "deleting..." << std::endl;
			if (!HTlib::Delete(HT, deleting))
			{
				if (!WriteFile(hf, "-- Error: Deleting element\n", 27, NULL, NULL)) throw "WriteFile";
				std::cout << "--Error: " << HTlib::GetLastErrorHt(HT) << std::endl;
			}
			else if (!WriteFile(hf, "-- Deleting element\n", 20, NULL, NULL)) throw "WriteFile";
			Sleep(5000);
		}
		if (!CloseHandle(hf)) throw "CloseHandle";
		if (!HTlib::CloseCOM()) throw "CloseCOM error";
	}
	catch (const char* error)
	{
		std::cout << "-- Error: " << error << std::endl;
	}
}