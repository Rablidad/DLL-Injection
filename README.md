

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

Once the DLL PathName gets loaded into any of the Windows Processes addresses space, a remote thread, provided by the DLL Injector, will ensure the DLL will be executed within the target process address space passing as argument the DLL PathName to the LoadLibraryW function in order to perform the malicous/non-malicious code contained inside the DllMain Function from the DLL injected. This technique is very useful to prevent antiviruses detection, as well as the windows' default security system.
its a technique also used in legitimate(non-malicious) cases.


Usage Example:
`C:\Users\Rablidad\>InjectDll.exe chrome.exe C:\Users\Rablidad\Documents\MyFavoriteDll.dll`

### Directory Contents ###
`bin\` -> The compiled Code ( InjectDll.exe , SampleDll.dll )

`src\` -> InjectDll.cpp & SampleDll.c

### DISCLAIMER ###
I'm not responsible for your acts.
