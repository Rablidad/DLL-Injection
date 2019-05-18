### DLL Injection ###

DLL Injection technique, load a DLL file within an existent windows process, the DLL must contain the DLL Entry point function, i.e.


`
BOOL WINAPI DllMain(
   HINSTANCE hinstDLL,
   DWORD     fdwReason,
   LPVOID    lpvReserved
)
{
  /* Main code that will be executed within the remote process */
}`

when the DLL PathName gets loaded into any of the Windows Processes addresses space, a remote thread, provided by the DLL Injector, will ensure it will be memory-mapped into the current process address space by the LoadLibraryW function in order to perform the malicous/non-malicious code contained within the DllMain Function from the Dll intended. this technique is very useful to prevent antiviruses detection.
its a technique also used in legitimate(non-malicious) cases.


Usage Example:
`C:\Users\Rablidad\>InjectDll.exe chrome.exe C:\Users\Rablidad\Documents\MyFavoriteDll.dll`
