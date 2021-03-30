#pragma once


#include "windows.h"

#define uchar unsigned char
#define ushort unsigned short
#define ulong unsigned long
#define ulonglong unsigned long long

typedef struct _UNICODE_STRING
{
	unsigned short Length;
	unsigned short MaxLength;
	unsigned long Pad;
	wchar_t* Buffer;
}UNICODE_STRING;

typedef struct _OBJECT_ATTRIBUTES {
  ULONGLONG           Length;
  HANDLE          RootDirectory;
  _UNICODE_STRING* ObjectName;
  ULONGLONG           Attributes;
  PVOID           SecurityDescriptor;
  PVOID           SecurityQualityOfService;
} OBJECT_ATTRIBUTES;


extern "C"
{
	int __stdcall ZwOpenSymbolicLinkObject(HANDLE* LinkHandle,int DesiredAccess,_OBJECT_ATTRIBUTES* ObjectAttributes);
	int __stdcall ZwQuerySymbolicLinkObject(HANDLE LinkHandle,_UNICODE_STRING* LinkTarget,unsigned long* ReturnedLength);
	int __stdcall ZwClose(HANDLE);
}


#define MAX_UNICODE_STRING_LENGTH 0x10000-0x2


void DumpHex(const void* data, size_t size);
void DumpHex_8(const void* data, size_t size);