#include "Service.h"
#include "../OS13_COMlib//HTlib.h"
#pragma comment(lib, "..\\Release\\OS13_COMlib.lib")

WCHAR ServiceName[] = SERVICENAME;
SERVICE_STATUS_HANDLE hServiceStatusHandle;
SERVICE_STATUS ServiceStatus;

void trace(const char* msg, int r) {std::ofstream out; out.open(TRACEPATH, r); out << msg << "\n"; out.close();}

const wchar_t* GetWC(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	size_t outSize;
	mbstowcs_s(&outSize, wc, cSize, c, cSize - 1);
	return wc;
}

HTlib::HTHANDLE* ht = NULL;

VOID WINAPI ServiceMain(DWORD dwArgc, LPTSTR* lpszArgv) {
	char temp[121];

	ServiceStatus.dwServiceType = SERVICE_WIN32;
	ServiceStatus.dwCurrentState = SERVICE_START_PENDING;
	ServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN | SERVICE_ACCEPT_PAUSE_CONTINUE;
	ServiceStatus.dwWin32ExitCode = 0;
	ServiceStatus.dwServiceSpecificExitCode = 0;
	ServiceStatus.dwCheckPoint = 0;
	ServiceStatus.dwWaitHint = 0;

	if (!(hServiceStatusHandle = RegisterServiceCtrlHandler(ServiceName, ServiceHandler))) {
		sprintf_s(temp, "\nSetServiceStatusFailed, error code = %d\n", GetLastError());
		trace(temp);
	}
	else {
		ServiceStatus.dwCurrentState = SERVICE_RUNNING;
		ServiceStatus.dwCheckPoint = 0;
		ServiceStatus.dwWaitHint = 0;
		if (!SetServiceStatus(hServiceStatusHandle, &ServiceStatus)) {
			sprintf_s(temp, "\nSetSetviceStatus failed, error code =%d\n", GetLastError());
			trace(temp);
		}
		else {
			trace("\nstart service", std::ofstream::out);
			if (HTlib::OpenCOM())
			{
				ht = HTlib::Open(GetWC("HTUser01"), GetWC("HTUser01"), GetWC("D:\\os15\\storage.ht"));
				if (ht != NULL)	trace("\nOpening HT...");
				else trace("\n--Error: Invalid handle");

				while (ServiceStatus.dwCurrentState == SERVICE_RUNNING && ht != NULL)
				{
					Sleep(5000);
					trace("\nserver running...");
				}

				if (ht != NULL) {
					trace("\nClosing HT...");
					HTlib::Close(ht);
					HTlib::CloseCOM();
				}
				else trace("\n--Error: Invalid handle while closing..");
			}
			else trace("\n--Error: OpenCOM...");
		}
	}
}


VOID WINAPI ServiceHandler(DWORD fdwControl) {
	char temp[121];
	switch (fdwControl) {
	case SERVICE_CONTROL_STOP:
		HTlib::Close(ht);
	case SERVICE_CONTROL_SHUTDOWN:
		ServiceStatus.dwWin32ExitCode = 0;
		ServiceStatus.dwCurrentState = SERVICE_STOPPED;
		ServiceStatus.dwCheckPoint = 0;
		ServiceStatus.dwWaitHint = 0;
		break;
	case SERVICE_CONTROL_PAUSE:
		ServiceStatus.dwCurrentState = SERVICE_PAUSED;
		HTlib::Close(ht);
		break;
	case SERVICE_CONTROL_CONTINUE:
		ServiceStatus.dwCurrentState = SERVICE_RUNNING;
		ht = HTlib::Open(GetWC("HTUser01"), GetWC("HTUser01"), GetWC("D:\\os15\\storage.ht"));
		break; 
	case SERVICE_CONTROL_INTERROGATE: break;
	default:
		sprintf_s(temp, "Unrecognized opcode%d\n", fdwControl);
		trace(temp);
	};
	if (!SetServiceStatus(hServiceStatusHandle, &ServiceStatus)) {
		sprintf_s(temp, "SetServiceStatus failed, error code = %d\n", GetLastError());
		trace(temp);
	}
}