#ifndef __HEADER__
#define __HEADER__



#include <stdio.h>

#include <windows.h>
#include <bcrypt.h>

#include <ntstatus.h>

#pragma comment(lib,"Bcrypt.lib")

#define	NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
#define	STATUS_UNSUCCESSFULL	((NTSTATUS)0xC0000001L)

#define RSAKEYLEN (2048)

#define SAFE_FREE(x) if(x) {free(x); x = NULL;}
#define COUNTOF(x) (sizeof(x)/sizeof(x[0]))


extern int DumpBin(char* lpComment, void* lpTarget, size_t ullSize);
extern void* m_malloc(size_t ullSize);



#endif