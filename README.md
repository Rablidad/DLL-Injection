### DLL Injection ###

DLL Injection technique, load a DLL file within an existente windows process, the dll must contain the Dll Entry point function, i.e.


`
BOOL WINAPI DllMain(
   HINSTANCE hinstDLL,
   DWORD     fdwReason,
   LPVOID    lpvReserved
)
{
  /* Main code that will be executed within the remote process */
}`

when the DLL file gets loaded into any of the Windows Processes, A remote thread, provided by the DLL Injector, will ensure it will be runned in order to perform the malicous/non-malicious code, this technique is very useful for preventing antiviruses detection.
its a technique also used in legitimate(non-malicious) cases.
