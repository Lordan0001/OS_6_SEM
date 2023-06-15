#include "pch.h"
#include "framework.h"
#include "HTlib.h"

namespace HTlib 
{
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
			HTlib::HTHANDLE** result,
			int	  Capacity,					   // емкость хранилища
			int   SecSnapshotInterval,		   // переодичность сохранения в сек.
			int   MaxKeyLength,                // максимальный размер ключа
			int   MaxPayloadLength,            // максимальный размер данных
			const wchar_t HTUsersGroup[512],
			const wchar_t  FileName[512]          // имя файла 
		) = 0; 	// != NULL успешное завершение  

		virtual HRESULT STDMETHODCALLTYPE Open     //  открыть HT             
		(
			const wchar_t    HTUser[512],
			const wchar_t    HTPassword[512],
			const wchar_t    FileName[512],         // имя файла 
			HTlib::HTHANDLE** result
		) = 0; 	// != NULL успешное завершение  

		virtual HRESULT STDMETHODCALLTYPE Open     //  открыть HT             
		(
			const wchar_t    FileName[512],         // имя файла 
			HTlib::HTHANDLE** result
		) = 0; 	// != NULL успешное завершение  

		virtual HRESULT __stdcall Snap         // выполнить Snapshot
		(
			HTlib::HTHANDLE** hthandle           // управление HT (File, FileMapping)
		) = 0;


		virtual HRESULT __stdcall Close        // Snap и закрыть HT  и  очистить HTHANDLE
		(
			HTlib::HTHANDLE** hthandle       // управление HT (File, FileMapping)
		) = 0;	//  == TRUE успешное завершение   


		virtual HRESULT __stdcall Insert      // добавить элемент в хранилище
		(
			HTlib::HTHANDLE** hthandle,            // управление HT
			HTlib::Element* element              // элемент
		) = 0;	//  == TRUE успешное завершение 


		virtual HRESULT __stdcall Delete      // удалить элемент в хранилище
		(
			HTlib::HTHANDLE** hthandle,            // управление HT (ключ)
			HTlib::Element* element              // элемент 
		) = 0;	//  == TRUE успешное завершение 

		virtual HRESULT __stdcall Get     //  читать элемент в хранилище
		(
			HTlib::Element& result,
			HTlib::HTHANDLE** hthandle,            // управление HT
			HTlib::Element* element              // элемент 
		) = 0; 	//  != NULL успешное завершение 


		virtual HRESULT __stdcall Update     //  именить элемент в хранилище
		(
			HTlib::HTHANDLE** hthandle,            // управление HT
			HTlib::Element* oldelement,          // старый элемент (ключ, размер ключа)
			void* newpayload,          // новые данные  
			int             newpayloadlength     // размер новых данных
		) = 0; 	//  != NULL успешное завершение 

		virtual HRESULT __stdcall GetLastErrorHt  // получить сообщение о последней ошибке
		(
			HTlib::HTHANDLE** ht                         // управление HT
		) = 0;

		virtual HRESULT __stdcall Print
		(
			char* key, int keyl, char* payload, int payloadl
		) = 0;
	};

	IHashTable* pIHashTable = nullptr;
	IUnknown* pIUnknown = NULL;

	HTHANDLE::HTHANDLE() {
	}
	HTHANDLE::HTHANDLE(
		int Capacity,
		int SecSnapshotInterval,
		int MaxKeyLength,
		int MaxPayloadLength,
		const wchar_t HTUsersGroup[512],
		const wchar_t FileName[512]
	) {
		this->Capacity = Capacity;
		this->SecSnapshotInterval = SecSnapshotInterval;
		this->MaxKeyLength = MaxKeyLength;
		this->MaxPayloadLength = MaxPayloadLength;
		this->N = 0;
		memcpy(this->HTUsersGroup, HTUsersGroup, sizeof(this->HTUsersGroup));
		memcpy(this->FileName, FileName, sizeof(this->FileName));
	}
	Element::Element() {
		this->key = nullptr;
		this->keylength = NULL;
		this->payload = nullptr;
		this->payloadlength = NULL;
	}
	Element::Element(const void* key, int keylength) {
		Element();
		this->key = (void*)key;
		this->keylength = keylength;
	}
	Element::Element(const void* key, int keylength, const void* payload, int  payloadlength) {
		this->key = (void*)key;
		this->keylength = keylength;
		this->payload = (void*)payload;
		this->payloadlength = payloadlength;
	}
	Element::Element(Element* oldelement, const void* newpayload, int  newpayloadlength) {
		this->key = oldelement->key;
		this->keylength = oldelement->keylength;
		this->payload = (void*)payload;
		this->payloadlength = payloadlength;
	}

	bool  HTlib::OpenCOM() {
		CoInitialize(NULL);  // инициализация библиотеки OLE32
		HRESULT hr0 = CoCreateInstance(CLSID_CA, NULL, CLSCTX_INPROC_SERVER, IID_IUnknown, (void**)&pIUnknown);
		if (SUCCEEDED(hr0))
		{
			std::cout << "CoCreateInstance succeeded" << std::endl;
			if (SUCCEEDED(pIUnknown->QueryInterface(IID_IHashTable, (void**)&pIHashTable)))
			{
				return true;
			}
		}
		return false;
	}

	bool  HTlib::CloseCOM() {
		bool res = true;
		if (!SUCCEEDED(pIHashTable->Release()))
			res = false;
		if (!SUCCEEDED(pIUnknown->Release()))
			res = false;
		CoFreeUnusedLibraries();
		return true;
	}


	HTlib::HTHANDLE* HTlib::Create   //  создать HT             
	(
		int	  Capacity,					   // емкость хранилища
		int   SecSnapshotInterval,		   // переодичность сохранения в сек.
		int   MaxKeyLength,                // максимальный размер ключа
		int   MaxPayloadLength,            // максимальный размер данных
		const wchar_t  HTUsersGroup[512],
		const wchar_t  FileName[512]          // имя файла 
	) {
		HTlib::HTHANDLE* pht;
		if (SUCCEEDED(pIHashTable->Create(
			&pht, Capacity, SecSnapshotInterval, MaxKeyLength, MaxPayloadLength, HTUsersGroup, FileName))) {
			return pht;
		}
		else {
			return NULL;
		}
	}

	HTlib::HTHANDLE* HTlib::Open     //  открыть HT             
	(
		const wchar_t HTUser[512],
		const wchar_t HTPassword[512],
		const wchar_t    FileName[512]         // имя файла
	) {
		HTlib::HTHANDLE* pht;
		if (SUCCEEDED(pIHashTable->Open(HTUser, HTPassword, FileName, &pht))) {
			return pht;
		}
		else {
			return NULL;
		}
	}

	HTlib::HTHANDLE* HTlib::Open     //  открыть HT             
	(
		const wchar_t    FileName[512]         // имя файла
	) {
		HTlib::HTHANDLE* pht;
		if (SUCCEEDED(pIHashTable->Open(FileName, &pht))) {
			return pht;
		}
		else {
			return NULL;
		}
	}

	BOOL Snap         // выполнить Snapshot
	(
		HTlib::HTHANDLE* hthandle           // управление HT (File, FileMapping)
	) {
		if (SUCCEEDED(pIHashTable->Snap(&hthandle))) {
			return true;
		}
		else {
			return false;
		}
	}


	BOOL Close        // Snap и закрыть HT  и  очистить HT::HTHANDLE
	(
		HTlib::HTHANDLE* hthandle           // управление HT (File, FileMapping)
	) {

		if (SUCCEEDED(pIHashTable->Close(&hthandle))) {
			return true;
		}
		else {
			return false;
		}
	}


	BOOL Insert      // добавить элемент в хранилище
	(
		HTlib::HTHANDLE* hthandle,            // управление HT
		HTlib::Element* element              // элемент
	) {
		if (SUCCEEDED(pIHashTable->Insert(&hthandle, element))) {
			return true;
		}
		else {
			return false;
		}
	}


	BOOL Delete      // удалить элемент в хранилище
	(
		HTlib::HTHANDLE* hthandle,            // управление HT (ключ)
		HTlib::Element* element              // элемент 
	) {
		if (SUCCEEDED(pIHashTable->Delete(&hthandle, element))) {
			return true;
		}
		else {
			return false;
		}
	}

	HTlib::Element* Get     //  читать элемент в хранилище
	(
		HTlib::HTHANDLE* hthandle,            // управление HT
		HTlib::Element* element              // элемент 
	) {
		HTlib::Element result;
		if (SUCCEEDED(pIHashTable->Get(result, &hthandle, element))) {
			return &result;
		}
		else {
			return NULL;
		}
	}

	BOOL Update     //  именить элемент в хранилище
	(
		HTlib::HTHANDLE* hthandle,            // управление HT
		HTlib::Element* oldelement,          // старый элемент (ключ, размер ключа)
		void* newpayload,          // новые данные  
		int             newpayloadlength     // размер новых данных
	) {
		if (SUCCEEDED(pIHashTable->Update(&hthandle, oldelement, newpayload, newpayloadlength))) {
			return true;
		}
		else {
			return false;
		}
	}

	char* GetLastErrorHt  // получить сообщение о последней ошибке
	(
		HTlib::HTHANDLE* ht                         // управление HT
	) {
		if (SUCCEEDED(pIHashTable->GetLastErrorHt(&ht))) {
			return ht->LastErrorMessage;
		}
		else {
			return NULL;
		}
	}

	BOOL Print
	(
		char* key, int keyl, char* payload, int payloadl
	) {
		if (SUCCEEDED(pIHashTable->Print(key, keyl, payload, payloadl))) {
			return true;
		}
		else {
			return false;
		}
	}
}