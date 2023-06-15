#pragma once
#include <objbase.h>
#include <iostream>
#include "INTERFACE.h"
#include <string>

class OS13:public IHashTable
{
public:
	OS13();
	~OS13();


	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);


	virtual HRESULT STDMETHODCALLTYPE Create   //  создать HT             
	(
		//DWORD& address,
		HT::HTHANDLE** result,
		int	  Capacity,					   // емкость хранилища
		int   SecSnapshotInterval,		   // переодичность сохранения в сек.
		int   MaxKeyLength,                // максимальный размер ключа
		int   MaxPayloadLength,            // максимальный размер данных
		const wchar_t  HTUsersGroup[512],
		const wchar_t  FileName[512]          // имя файла 
	); 	// != NULL успешное завершение  

	virtual HRESULT STDMETHODCALLTYPE Open     //  открыть HT             
	(
		const wchar_t    HTUser[512],
		const wchar_t    HTPassword[512],
		const wchar_t    FileName[512],         // имя файла 
		HT::HTHANDLE** result
	); 	// != NULL успешное завершение  

	virtual HRESULT STDMETHODCALLTYPE Open     //  открыть HT             
	(
		const wchar_t    FileName[512],         // имя файла 
		HT::HTHANDLE**  result
	); 	// != NULL успешное завершение  

	virtual HRESULT STDMETHODCALLTYPE Snap         // выполнить Snapshot
	(
		HT::HTHANDLE**  hthandle           // управление HT (File, FileMapping)
	);


	virtual HRESULT STDMETHODCALLTYPE Close        // Snap и закрыть HT  и  очистить HT::HTHANDLE
	(
		HT::HTHANDLE** hthandle
		//DWORD address     // управление HT (File, FileMapping)
	);	//  == TRUE успешное завершение   


	virtual HRESULT STDMETHODCALLTYPE Insert      // добавить элемент в хранилище
	(
		HT::HTHANDLE**  hthandle,            // управление HT
		HT::Element* element              // элемент
	);	//  == TRUE успешное завершение 


	virtual HRESULT STDMETHODCALLTYPE Delete      // удалить элемент в хранилище
	(
		HT::HTHANDLE**  hthandle,            // управление HT (ключ)
		HT::Element* element              // элемент 
	);	//  == TRUE успешное завершение 

	virtual HRESULT STDMETHODCALLTYPE Get     //  читать элемент в хранилище
	(
		HT::Element& result,
		HT::HTHANDLE**  hthandle,            // управление HT
		HT::Element* element              // элемент 
	); 	//  != NULL успешное завершение 


	virtual HRESULT STDMETHODCALLTYPE Update     //  именить элемент в хранилище
	(
		HT::HTHANDLE**  hthandle,            // управление HT
		HT::Element* oldelement,          // старый элемент (ключ, размер ключа)
		void* newpayload,          // новые данные  
		int             newpayloadlength     // размер новых данных
	); 	//  != NULL успешное завершение 

	virtual HRESULT STDMETHODCALLTYPE GetLastErrorHt  // получить сообщение о последней ошибке
	(
		HT::HTHANDLE**  ht                         // управление HT
	);

	virtual HRESULT STDMETHODCALLTYPE Print  // получить сообщение о последней ошибке
	(
		char* key, int keyl, char* payload, int payloadl               // элемент
	);

private:
	volatile ULONG m_Ref;
};
