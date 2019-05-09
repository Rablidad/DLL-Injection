#define UNICODE
#include <windows.h>
#include <stdio.h>
#include <tlhelp32.h>
#include <wchar.h>
#include <locale.h>

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
					_wprintf_l(TEXT("Processo Encontrado: %s\n") , setlocale(LC_ALL, "Portuguese") , PInfo.szExeFile );
					return PInfo.th32ProcessID;
				}
			}
		}
	}
	
	_wprintf_l(TEXT("Processo Não Encontrado: %s\n") , setlocale(LC_ALL, "Portuguese") , ProcessName );
	return NOT_FOUND;
}


DWORD InjectDll( DWORD PID , WCHAR * DllPath )
{
	
	DWORD Dll_Size = ( lstrlenW( DllPath ) + 1 ) * sizeof(wchar_t);
	HANDLE OpH = NULL;
	_wprintf_l(TEXT("Abrindo Processo.\n") , setlocale(LC_ALL, "Portuguese") );
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
	_wprintf_l(TEXT("DLL nao injetada!\n") , setlocale(LC_ALL, "Portuguese") );
	return NINJECTED;
}


int main( int argc , char ** argv )
{

	DWORD SWrt;
	
	int argt = 0;
	
	WCHAR ** argg = CommandLineToArgvW( GetCommandLine() , &argt );
	
	
	if( argt < 3 )
	{
		_wprintf_l(TEXT("Syntax: %s <ProcessToGetInjected> <DllToInject>\n") , setlocale(LC_ALL, "Portuguese") , argg[0] );
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
