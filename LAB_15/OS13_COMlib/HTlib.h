#pragma once
#include <Windows.h>
#include <objbase.h>
#include <iostream>
#include <iomanip>
#include <string>

namespace HTlib    // HT API
{
	extern "C" struct HTHANDLE    // блок управления HT
	{
		HTHANDLE();
		HTHANDLE(int Capacity, int SecSnapshotInterval, int MaxKeyLength, int MaxPayloadLength, const wchar_t HTUsersGroup[512], const wchar_t FileName[512]);
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
		char HTUsersGroup[512];

		HANDLE Mutex;
		int N;//текущее заполнение
		HANDLE SnapshotThread;
	};

	extern "C" struct Element   // элемент 
	{
		Element();
		Element(const void* key, int keylength);                                             // for Get
		Element(const void* key, int keylength, const void* payload, int  payloadlength);    // for Insert
		Element(Element* oldelement, const void* newpayload, int  newpayloadlength);         // for update
		void* key;                 // значение ключа 
		int             keylength;           // рахмер ключа
		void* payload;             // данные 
		int             payloadlength;       // размер данных
	};

	bool OpenCOM();
	bool CloseCOM();

	HTlib::HTHANDLE* Create   //  создать HT             
	(
		int	  Capacity,					   // емкость хранилища
		int   SecSnapshotInterval,		   // переодичность сохранения в сек.
		int   MaxKeyLength,                // максимальный размер ключа
		int   MaxPayloadLength,            // максимальный размер данных
		const wchar_t  HTUsersGroup[512],
		const wchar_t  FileName[512]          // имя файла 
	);

	HTlib::HTHANDLE* Open     //  открыть HT             
	(
		const wchar_t    HTUser[512],
		const wchar_t    HTPassword[512],
		const wchar_t    FileName[512]         // имя файла
	); 	// != NULL успешное завершение  

	HTlib::HTHANDLE* Open     //  открыть HT             
	(
		const wchar_t    FileName[512]         // имя файла
	); 	// != NULL успешное завершение  

	BOOL Snap         // выполнить Snapshot
	(
		HTlib::HTHANDLE* hthandle           // управление HT (File, FileMapping)
	);


	BOOL Close        // Snap и закрыть HT  и  очистить HT::HTHANDLE
	(
		HTlib::HTHANDLE* hthandle           // управление HT (File, FileMapping)
	);	//  == TRUE успешное завершение   


	BOOL Insert      // добавить элемент в хранилище
	(
		HTlib::HTHANDLE* hthandle,            // управление HT
		HTlib::Element* element              // элемент
	);	//  == TRUE успешное завершение 


	BOOL Delete      // удалить элемент в хранилище
	(
		HTlib::HTHANDLE* hthandle,            // управление HT (ключ)
		HTlib::Element* element              // элемент 
	);	//  == TRUE успешное завершение 

	HTlib::Element* Get     //  читать элемент в хранилище
	(
		HTlib::HTHANDLE* hthandle,            // управление HT
		HTlib::Element* element              // элемент 
	); 	//  != NULL успешное завершение 


	BOOL Update     //  именить элемент в хранилище
	(
		HTlib::HTHANDLE* hthandle,            // управление HT
		HTlib::Element* oldelement,          // старый элемент (ключ, размер ключа)
		void* newpayload,          // новые данные  
		int newpayloadlength     // размер новых данных
	); 	//  != NULL успешное завершение 

	char* GetLastErrorHt  // получить сообщение о последней ошибке
	(
		HTlib::HTHANDLE* ht                         // управление HT
	);

	BOOL Print // распечатать элемент
	(
		char* key, int keyl, char* payload, int payloadl // элемент
	);
};