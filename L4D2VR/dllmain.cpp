// dllmain.cpp : Defines the entry point for the DLL application.
#include <Windows.h>
#include <iostream>
#include "game.h"
#include "hooks.h"
#include "vr.h"
#include "sdk.h"

DWORD WINAPI InitL4D2VR(HMODULE hModule)
{
// Release if buggy, so we'll be releasing the debug binary
#ifdef _DEBUG
    AllocConsole();
    FILE *fp;
    freopen_s(&fp, "CONOUT$", "w", stdout);
#endif

    // Make sure -insecure is used
    LPWSTR *szArglist;
    int nArgs;
    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    bool insecureEnabled = false;
    bool insecureIgnored = false;
    for (int i = 0; i < nArgs; ++i)
    {
        if (wcscmp(szArglist[i], L"-insecure") == 0)
            insecureEnabled = true;
    }
    for (int i = 0; i < nArgs; ++i)
    {
        if (wcscmp(szArglist[i], L"-secure_ignore") == 0)
            insecureIgnored = true;
    }
    LocalFree(szArglist);

    if (!insecureEnabled && !insecureIgnored)
        // If not, show a warning to the user
        MessageBox(NULL, "-insecure flag not set, this is not recommended.\nAdd -secure_ignore flag to hide warning", "Warning: Running in secure mode!", MB_ICONWARNING | MB_OK);
    //ExitProcess(0);

    g_Game = new Game();

    return 0;
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
            CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)InitL4D2VR, hModule, 0, NULL);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


