#pragma once
#include <objbase.h>
#include "OS11_HTAPI.h"

#define FNAME L"Skm13.CA.COM"
#define VINDX L"Skm13.CA.1"
#define PRGID L"Skm13.CA"

// {1CB85228-E5EF-4CD6-9BD2-D45CFEFD2034}
static const GUID CLSID_CA =
{ 0x1cb85228, 0xe5ef, 0x4cd6, { 0x9b, 0xd2, 0xd4, 0x5c, 0xfe, 0xfd, 0x20, 0x34 } };

// {68F60FCB-0F40-46ED-B401-28B6C4F22384}
static const GUID IID_IOS13 =
{ 0x68f60fcb, 0xf40, 0x46ed, { 0xb4, 0x1, 0x28, 0xb6, 0xc4, 0xf2, 0x23, 0x84 } };

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

