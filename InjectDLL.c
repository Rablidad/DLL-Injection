#define UNICODE
#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <wchar.h>

#define NOT_FOUND 0
#define INJECTED 1
#define NINJECTED 0

DWORD GetProcessInfo( LPWSTR ProcessName )
{
	DWORD Tw;
	HANDLE hSnapshot = NULL;
	PROCESSENTRY32 PInfo;
	PInfo.dwSize = sizeof( PROCESSENTRY32 );
	
	hSnapshot = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS , 0 );
	if ( hSnapshot != INVALID_HANDLE_VALUE )
	{
		BOOL PFirst = Process32First( hSnapshot , &PInfo );
		if ( PFirst != FALSE )
		{
			while( Process32Next( hSnapshot , &PInfo ) )
			{
				
				if( wcsncmp( ProcessName , PInfo.szExeFile , lstrlenW( ProcessName ) ) == 0 )
				{
					wprintf(TEXT("[++] Processo encontrado: %s\n") , PInfo.szExeFile );
					return PInfo.th32ProcessID;
				}
			}
		}
	}
	
	wprintf(TEXT("[--] Processo nao encontrado: %s\n") , ProcessName );
	return NOT_FOUND;
}


DWORD InjectDll( DWORD PID , WCHAR * DllPath )
{
	
	DWORD Dll_Size = ( lstrlenW( DllPath ) + 1 ) * sizeof(wchar_t);
	HANDLE OpH = NULL;
	wprintf(TEXT("Abrindo Processo.\n"));
	OpH = OpenProcess( PROCESS_ALL_ACCESS , FALSE , PID );
	if( OpH != NULL )
	{
		LPVOID hVA = VirtualAllocEx ( OpH , NULL , Dll_Size , MEM_COMMIT , PAGE_READWRITE );
		if( hVA != NULL )
		{
			DWORD PWrite = WriteProcessMemory( OpH , hVA , DllPath , Dll_Size , NULL );
			if( PWrite != 0 )
			{
				LPTHREAD_START_ROUTINE ProcH = (LPTHREAD_START_ROUTINE) GetProcAddress( GetModuleHandle( TEXT("kernel32") ) , "LoadLibraryW" );
				if( ProcH != NULL )
				{
					HANDLE ThreadH = CreateRemoteThread( OpH , NULL , 0 , ProcH , hVA , 0 , NULL );
					if( ThreadH != NULL )
					{
						wprintf(TEXT("DLL Injetada com sucesso!\n"));
						return INJECTED;
						
					}
				}
			}
		}
	}
	wprintf(TEXT("DLL Nao injetada!\n"));
	return NINJECTED;
}


int main( int argc , char ** argv )
{

	DWORD SWrt;
	
	int argt = 0;
	
	WCHAR ** argg = CommandLineToArgvW( GetCommandLine() , &argt );
	
	
	if( argt < 3 )
	{
		wprintf(TEXT("Syntax: %s <ProcessToGetInjected> <DllToInject>\n") , argg[0] );
		ExitProcess(1);
	}
	
	DWORD PID = GetProcessInfo( argg[1] );
	if( PID != NOT_FOUND )
	{
		InjectDll( PID , argg[2] );
	}
	else
	{
		ExitProcess(1);
	}
	
	return 0;
}


//	wmemset( PBuffer , 0 , lstrlenW(PBuffer) );
//	mbstowcs( PBuffer , PInfo.szExeFile , strlen( PInfo.szExeFile ) );
//	wprintf(TEXT("PInfo.szExeFile --> %s\n") , PInfo.szExeFile );
				
