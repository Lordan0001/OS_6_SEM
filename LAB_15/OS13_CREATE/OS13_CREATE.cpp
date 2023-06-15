#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include <iostream>
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
	try
	{
		if (!HTlib::OpenCOM()) throw "OpenCOM error";
		HTlib::HTHANDLE* HT = HTlib::Create(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), GetWC(argv[5]), GetWC(argv[6]));
		if (HT == NULL) throw "Invalid handle";

		std::cout << "--- HT-Storage Created ---" << std::endl;
		std::cout << "filename: " << argv[5] << std::endl;
		std::cout << "snapshotinterval: " << argv[2] << std::endl;
		std::cout << "capacity: " << argv[1] << std::endl;
		std::cout << "maxkeylength: " << argv[3] << std::endl;
		std::cout << "maxdatalength: " << argv[4] << std::endl;

		if (!HTlib::Close(HT)) throw "Error close";
		if (!HTlib::CloseCOM()) throw "CloseCOM error";
	}
	catch (const char* error) { std::cout << "-- Error: " << error << std::endl; }
}