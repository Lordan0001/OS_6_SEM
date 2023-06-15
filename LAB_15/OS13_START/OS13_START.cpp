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
		HTlib::HTHANDLE* HT = HTlib::Open(GetWC(argv[1]), GetWC(argv[2]), GetWC(argv[3]));
		if (HT == NULL) throw "Invalid handle";

		std::cout << "--- HT-Storage Started ---" << std::endl;
		std::cout << "filename: " << argv[1] << std::endl;
		std::cout << "snapshotinterval: " << HT->SecSnapshotInterval << std::endl;
		std::cout << "capacity: " << HT->Capacity << std::endl;
		std::cout << "maxkeylength: " << HT->MaxKeyLength << std::endl;
		std::cout << "maxdatalength: " << HT->MaxPayloadLength << std::endl;

		std::cout << std::endl << "Press any key to close HT: ";
		char a;
		std::cin >> a;
		if (!HTlib::Snap(HT)) throw HTlib::GetLastErrorHt(HT);

		if (!HTlib::Close(HT)) throw "Error close";
		if (!HTlib::CloseCOM()) throw "CloseCOM error";
	}
	catch (const char* error) { std::cout << "-- Error: " << error << std::endl; }
}