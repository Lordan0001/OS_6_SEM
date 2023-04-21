#pragma once
#include <objbase.h>
#include "OS11_HTAPI.h"

#define FNAME L"SLab15.CA.COM"
#define VINDX L"SLab15.CA.1"
#define PRGID L"SLab15.CA"

// {A87118BB-A1E7-4499-933C-0A354893E749}
static const GUID CLSID_CA =
{ 0xa87118bb, 0xa1e7, 0x4499, { 0x93, 0x3c, 0xa, 0x35, 0x48, 0x93, 0xe7, 0x49 } };

// {8B8976E6-9974-4B73-AC1A-10C1E4364430}
static const GUID IID_IOS13 =
{ 0x8b8976e6, 0x9974, 0x4b73, { 0xac, 0x1a, 0x10, 0xc1, 0xe4, 0x36, 0x44, 0x30 } };


interface IOS13 :IUnknown {
    STDMETHOD(Add(const double, const double, double*)) PURE;
    
	STDMETHOD(Sub(const double, const double, double*)) PURE;

	STDMETHOD(Create   //  создать HT             
	(
		int	  Capacity,					   // емкость хранилища
		int   SecSnapshotInterval,		   // переодичность сохранения в сек.
		int   MaxKeyLength,                // максимальный размер ключа
		int   MaxPayloadLength,            // максимальный размер данных
		const wchar_t  FileName[512],          // имя файла 
		const wchar_t  HTUsersGroup[512],          // имя файла 
		HT::HTHANDLE** result
	)) PURE; 	// != NULL успешное завершение  

	STDMETHOD(Open     //  открыть HT             
	(
		const wchar_t    FileName[512],         // имя файла 
		HT::HTHANDLE** result
	)) PURE; 	// != NULL успешное завершение 

	STDMETHOD(Open     //  открыть HT             
	(
		const wchar_t    FileName[512],         // имя файла 
		const wchar_t    userName[512],         // имя файла 
		const wchar_t    password[512],         // имя файла 
		HT::HTHANDLE** result
	)) PURE; 	// != NULL успешное завершение  

	STDMETHOD(Close     //  открыть HT             
	(
		HT::HTHANDLE** hthandle           // управление HT (File, FileMapping)
	)) PURE; 	// != NULL успешное завершение 

	STDMETHOD(OpenExist     //  открыть HT             
	(
		const wchar_t    FileName[512],         // имя файла 
		HT::HTHANDLE** result
	)) PURE; 	// != NULL успешное завершение 

	STDMETHOD(Snap     //  открыть HT             
	(
		HT::HTHANDLE** hthandle
	)) PURE; 	// != NULL успешное завершение 

	STDMETHOD(Insert     //  открыть HT             
	(
		HT::HTHANDLE** hthandle,            // управление HT
		HT::Element** element              // элемент
	)) PURE; 	// != NULL успешное завершение

	STDMETHOD(Get     //  открыть HT             
	(
		HT::Element** result,
		HT::HTHANDLE** hthandle,            // управление HT
		HT::Element** element              // элемент 
	)) PURE; 	// != NULL успешное завершение

	STDMETHOD(Delete     //  открыть HT             
	(
		HT::HTHANDLE** hthandle,            // управление HT (ключ)
		HT::Element** element              // элемент 
	)) PURE; 	// != NULL успешное завершение

	STDMETHOD(Update     //  открыть HT             
	(
		HT::HTHANDLE** hthandle,            // управление HT
		HT::Element** oldelement,          // старый элемент (ключ, размер ключа)
		void** newpayload,          // новые данные  
		int*   newpayloadlength     // размер новых данных
	)) PURE; 	// != NULL успешное завершение

	STDMETHOD(GetLastErrorProg     //  открыть HT             
	(
		std::string& error,
		HT::HTHANDLE** ht                         // управление HT
	)) PURE; 	// != NULL успешное завершение

	STDMETHOD(CreateElement     //  открыть HT             
	(
		std::string* key,
		HT::Element** el                         // управление HT
	)) PURE; 	// != NULL успешное завершение

	STDMETHOD(CreateElement     //  открыть HT             
	(
		std::string* key,
		std::string* payload,
		HT::Element** el                         // управление HT
	)) PURE; 	// != NULL успешное завершение

	STDMETHOD(print     //  открыть HT             
	(
		HT::Element** element              // элемент 
	)) PURE; 	// != NULL успешное завершение
};

