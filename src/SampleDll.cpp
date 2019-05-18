// dllmain.cpp : Define o ponto de entrada para o aplicativo DLL.
#include "stdafx.h"

extern "C" BOOL WINAPI MakeTheWork(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved);

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
	{
    case DLL_PROCESS_ATTACH:
		MakeTheWork( hModule , ul_reason_for_call , lpReserved);
		break;
    case DLL_THREAD_ATTACH:
		break;
    case DLL_THREAD_DETACH:
		break;
    case DLL_PROCESS_DETACH:
		MakeTheWork(hModule, ul_reason_for_call , lpReserved);
        break;
    }
    return TRUE;
}

BOOL WINAPI MakeTheWork(
	HINSTANCE hinstDLL,
	DWORD     fdwReason,
	LPVOID    lpvReserved
)
{
	if (fdwReason = DLL_PROCESS_ATTACH)
	{
		MessageBox(
			NULL,
			TEXT("Computer HACKED!!!!!!!"),
			TEXT("Very Super Warning!"),
			MB_OK
		);
	}
	else if (fdwReason == DLL_PROCESS_DETACH)
	{
		MessageBox(
			NULL,
			TEXT("deHacking Computer!!!!!!!"),
			TEXT("No more Very Super Warning!"),
			MB_OK
		);
	}
	return true;
}