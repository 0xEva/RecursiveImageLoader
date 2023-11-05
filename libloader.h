#pragma once
#include "common.h"
#include "apiset.h"
#include "peparser.h"
#include "PEBstructs.h"
#include <stdio.h>


#define APP_SET_DLL_1 "api-"
#define APP_SET_DLL_2 "ext-"
#define APP_SET_DLL_LEN 4

typedef void (__stdcall *MyTLSCallback)(PVOID DllHandle, DWORD Reason, PVOID Reserved);
typedef BOOL (WINAPI *MyDllMain)(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved);


typedef enum {
    DLL_READY, //0
    DLL_NOT_FOUND, //1
    DLL_IN_PROGRESS, //2
    DLL_IAT_REQUIRE_FIXING, //3
    DLL_TLS_REQUIRE_CALLBACK, //4
    DLL_CIRCULAR_IMPORT, //5
    DLL_ERROR, //5
    DLL_STATUS_INVALID //6
} DLL_STATUS;

typedef struct _MY_LDR_DATA_TABLE_ENTRY{
    struct _MY_LDR_DATA_TABLE_ENTRY* next;
    char* uniqueID;
    DLL_STATUS status;
    LPVOID DllBase;
}MY_LDR_DATA_TABLE_ENTRY, *PMY_LDR_DATA_TABLE_ENTRY;

extern MY_LDR_DATA_TABLE_ENTRY* myLdr;
extern char* loadOrder[];


void init();

DLL_STATUS
UpdateLdrEntryStatus(
    IN const char* uniqueID,
    DLL_STATUS status
);

LPVOID
GetModuleAddress(
    IN const char* uniqueID
);

FARPROC
MyGetProcAddressByAddr(
    IN LPVOID baseAddr,
    IN const char* lpProcName
);


FARPROC MyGetProcAddressByUID(
    IN const char* uniqueID,
    IN const char* lpProcName
);

void AddLdrEntry(
    IN LPVOID baseAddr,
    IN const char* uniqueID
);


static
inline __attribute__((always_inline))
size_t
MyGetFileSize(
    FILE* file
);

static
inline __attribute__((always_inline))
void
BuildAbsFilePath(
    char *absFilePath,
    const char *loadOrderElement,
    const char *name
);

LPVOID
MyLoadLibrary(
    IN unsigned char* rawData,
    IN const char* uniqueID
);

LPVOID
MyLoadLibraryByName(
    IN const char* dllName
);

LPVOID
MyLoadLibraryFromFile(
    IN const char* fileName
);

BOOLEAN
NTAPI
ApiSetResolveAA(
    IN const char* ApiSetNameA,
    OUT char* ResolvedHostLibraryA
);

BOOLEAN
isForwarding(const char* name);

BOOLEAN
isAPISetsDLL(
    const char* dllName
);
BOOLEAN
WriteHeader(
    LPVOID targetLibraryBuffer,
    unsigned char* rawData
);
BOOLEAN
WriteSection(
    LPVOID targetLibraryBuffer,
    unsigned char* rawData
);
BOOLEAN
PerformRelocation(
    LPVOID targetLibraryBuffer
);
BOOLEAN
FixIAT(
    LPVOID targetLibraryBuffer,
    IN const char* uniqueID
);
BOOLEAN
PerformTLSCallback(
    IN LPVOID targetLibraryBuffer
);