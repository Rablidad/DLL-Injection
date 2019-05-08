### DLL Injection ###

DLL Injection technique, load a DLL file within an existente windows executable, the dll must contain the Dll Entry point function, i.e.


`
BOOL WINAPI DllMain(
   HINSTANCE hinstDLL,
   DWORD     fdwReason,
   LPVOID    lpvReserved
)
{
  /* Main code that will be executed within the remote process */
}`
