#pragma once
#include <Windows.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <LMaccess.h>
#include <Lm.h>

#define CREATE_HTFILE_ERROR "Create HTFile error";
#define CREATE_FILEMAPPING_ERROR "Create FileMapping error";
#define MAPPING_VIEW_ERROR "Mapping view failed";

#define MATHLIBRARY_API  __declspec(dllexport)

namespace HT    // HT API
{
	// API HT - программный интерфейс для доступа к НТ-хранилищу 
	//          НТ-хранилище предназначено для хранения данных в ОП в формате ключ/значение
	//          Персистестеность (сохранность) данных обеспечивается с помощью snapshot-менханизма 
	//          Create - создать  и открыть HT-хранилище для использования   
	//          Open   - открыть HT-хранилище для использования
	//          Insert - создать элемент данных
	//          Delete - удалить элемент данных    
	//          Get    - читать  элемент данных
	//          Update - изменить элемент данных
	//          Snap   - выпонить snapshot
	//          Close  - выполнить Snap и закрыть HT-хранилище для использования
	//          GetLastError - получить сообщение о последней ошибке

	MATHLIBRARY_API struct HTHANDLE    // блок управления HT
	{
		MATHLIBRARY_API HTHANDLE();
		MATHLIBRARY_API HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const wchar_t HTUsersGroup[512], const wchar_t FileName[512]);
		int     Capacity;               // емкость хранилища в количестве элементов 
		int     SecSnapshotInterval;    // переодичность сохранения в сек. 
		int     MaxKeyLength;           // максимальная длина ключа
		int     MaxPayloadLength;       // максимальная длина данных
		char    FileName[512];          // имя файла 
		HANDLE  File;                   // File HANDLE != 0, если файл открыт
		HANDLE  FileMapping;            // Mapping File HANDLE != 0, если mapping создан  
		LPVOID  Addr;                   // Addr != NULL, если mapview выполнен  
		char    LastErrorMessage[512];  // сообщение об последней ошибке или 0x00  
		time_t  lastsnaptime;           // дата последнего snap'a (time())  
		char HTUsersGroup[512];          // группа OS-пользователей 

		HANDLE Mutex;
		int N;//текущее заполнение
		HANDLE SnapshotThread;
	};

	extern "C" MATHLIBRARY_API struct Element   // элемент 
	{
		MATHLIBRARY_API Element();
		MATHLIBRARY_API Element(const void* key, int keylength);                                             // for Get
		MATHLIBRARY_API Element(const void* key, int keylength,  const void* payload, int  payloadlength);    // for Insert
		MATHLIBRARY_API Element(Element* oldelement,  const void* newpayload, int  newpayloadlength);         // for update
		void* key;                 // значение ключа 
		int             keylength;           // рахмер ключа
		void* payload;             // данные 
		int             payloadlength;       // размер данных
	};

	extern "C" MATHLIBRARY_API HTHANDLE* Create   //  создать HT             
	(
		int	  Capacity,					   // емкость хранилища
		int   SecSnapshotInterval,		   // переодичность сохранения в сек.
		int   MaxKeyLength,                // максимальный размер ключа
		int   MaxPayloadLength,            // максимальный размер данных
		const wchar_t  HTUsersGroup[512],  // группа пользователей
		const wchar_t  FileName[512]       // имя файла 
	); 	// != NULL успешное завершение  

	MATHLIBRARY_API HTHANDLE* Open     //  открыть HT             
	(
		const wchar_t    HTUser[512],
		const wchar_t    HTPassword[512],
		const wchar_t    FileName[512]         // имя файла
	); 	// != NULL успешное завершение  

	MATHLIBRARY_API HTHANDLE* Open     //  открыть HT             
	(
		const wchar_t    FileName[512]         // имя файла
	); 	// != NULL успешное завершение  

	extern "C" MATHLIBRARY_API BOOL Snap         // выполнить Snapshot
	(
		HTHANDLE* hthandle           // управление HT (File, FileMapping)
	);


	extern "C" MATHLIBRARY_API BOOL Close        // Snap и закрыть HT  и  очистить HTHANDLE
	(
		HTHANDLE* hthandle           // управление HT (File, FileMapping)
	);	//  == TRUE успешное завершение   


	extern "C" MATHLIBRARY_API BOOL Insert      // добавить элемент в хранилище
	(
		 HTHANDLE* hthandle,            // управление HT
		 Element* element              // элемент
	);	//  == TRUE успешное завершение 


	extern "C" MATHLIBRARY_API BOOL Delete      // удалить элемент в хранилище
	(
		 HTHANDLE* hthandle,            // управление HT (ключ)
		 Element* element              // элемент 
	);	//  == TRUE успешное завершение 

	extern "C" MATHLIBRARY_API Element* Get     //  читать элемент в хранилище
	(
		 HTHANDLE* hthandle,            // управление HT
		 Element* element              // элемент 
	); 	//  != NULL успешное завершение 


	extern "C" MATHLIBRARY_API BOOL Update     //  именить элемент в хранилище
	(
		HTHANDLE* hthandle,            // управление HT
		Element* oldelement,          // старый элемент (ключ, размер ключа)
		void* newpayload,          // новые данные  
		int             newpayloadlength     // размер новых данных
	); 	//  != NULL успешное завершение 

	extern "C" MATHLIBRARY_API char* GetLastErrorHt  // получить сообщение о последней ошибке
	(
		HTHANDLE* ht                         // управление HT
	);

	extern "C" MATHLIBRARY_API BOOL print                               // распечатать элемент 
	(
		char* key, int keyl, char* payload, int payloadl         // элемент 
	);


};
