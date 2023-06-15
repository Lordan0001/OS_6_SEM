#pragma once
#include <objbase.h>
#include "HT.h"
#include <string>

#define FNAME L"SDA.COM"
#define VINDX L"SDA.1"
#define PRGID L"SDA"

// {352CB0AE-1F06-4A76-AD11-D1B96F900115}
static GUID CLSID_CA =
{ 0x352cb0ae, 0x1f06, 0x4a76, { 0xad, 0x11, 0xd1, 0xb9, 0x6f, 0x90, 0x1, 0x15 } };


// {5533B146-DEE2-4647-AD2B-5E388DBDD7B4}
static GUID IID_IHashTable =
{ 0x5533b146, 0xdee2, 0x4647, { 0xad, 0x2b, 0x5e, 0x38, 0x8d, 0xbd, 0xd7, 0xb4 } };

interface IHashTable :IUnknown  
{
	virtual HRESULT STDMETHODCALLTYPE Create   //  создать HT             
	(
		HT::HTHANDLE** result,
		int	  Capacity,					   // емкость хранилища
		int   SecSnapshotInterval,		   // переодичность сохранения в сек.
		int   MaxKeyLength,                // максимальный размер ключа
		int   MaxPayloadLength,            // максимальный размер данных
		const wchar_t  HTUsersGroup[512],
		const wchar_t  FileName[512]          // имя файла 
	) = 0; 	// != NULL успешное завершение  

	virtual HRESULT __stdcall Open     //  открыть HT             
	(
		const wchar_t    HTUser[512],
		const wchar_t    HTPassword[512],
		const wchar_t    FileName[512],         // имя файла 
		HT::HTHANDLE** result
	) = 0; 	// != NULL успешное завершение  

	virtual HRESULT __stdcall Open     //  открыть HT             
	(
		const wchar_t    FileName[512],         // имя файла
		HT::HTHANDLE** result
	) = 0; 	// != NULL успешное завершение  

	virtual HRESULT __stdcall Snap         // выполнить Snapshot
	(
		HT::HTHANDLE** hthandle           // управление HT (File, FileMapping)
	) = 0;


	virtual HRESULT __stdcall Close        // Snap и закрыть HT  и  очистить HTHANDLE
	(

		HT::HTHANDLE** hthandle       // управление HT (File, FileMapping)
	) = 0;	//  == TRUE успешное завершение   


	virtual HRESULT __stdcall Insert      // добавить элемент в хранилище
	(
		HT::HTHANDLE** hthandle,            // управление HT
		HT::Element * element              // элемент
	) = 0;	//  == TRUE успешное завершение 


	virtual HRESULT __stdcall Delete      // удалить элемент в хранилище
	(
		HT::HTHANDLE** hthandle,            // управление HT (ключ)
		HT::Element * element              // элемент 
	) = 0;	//  == TRUE успешное завершение 

	virtual HRESULT __stdcall Get     //  читать элемент в хранилище
	(
		HT::Element & result,
		HT::HTHANDLE** hthandle,            // управление HT
		HT::Element * element              // элемент 
	) = 0; 	//  != NULL успешное завершение 


	virtual HRESULT __stdcall Update     //  именить элемент в хранилище
	(
		HT::HTHANDLE** hthandle,            // управление HT
		HT::Element * oldelement,          // старый элемент (ключ, размер ключа)
		void* newpayload,          // новые данные  
		int             newpayloadlength     // размер новых данных
	) = 0; 	//  != NULL успешное завершение 

	virtual HRESULT __stdcall GetLastErrorHt  // получить сообщение о последней ошибке
	(
		HT::HTHANDLE** ht                         // управление HT
	) = 0;

	virtual HRESULT __stdcall Print
	(
		char* key, int keyl, char* payload, int payloadl // элемент
	) = 0; 	//  != NULL успешное завершение
};
