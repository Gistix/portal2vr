#include <Windows.h>
#include <d3d9.h>
#include <iostream>

static HMODULE g_hRealD3D9 = nullptr;

void LoadRealD3D9()
{
    if (g_hRealD3D9)
        return;

    std::cout << "[VR] LoadRealD3D9: starting\n";
    char sysPath[MAX_PATH];
    GetSystemDirectoryA(sysPath, MAX_PATH);
    strcat_s(sysPath, "\\d3d9.dll");
    std::cout << "[VR] LoadRealD3D9: sysPath=" << sysPath << "\n";
    g_hRealD3D9 = LoadLibraryA(sysPath);
    std::cout << "[VR] LoadRealD3D9: LoadLibrary=" << (void*)g_hRealD3D9 << " lastError=" << GetLastError() << "\n";
}

HMODULE GetRealD3D9() { 
    if (!g_hRealD3D9)
        LoadRealD3D9();

    return g_hRealD3D9; 
}

extern "C" void WINAPI D3DPERF_SetOptions(DWORD dwOptions)
{
    LoadRealD3D9();
    auto realFn = (void(WINAPI*)(DWORD))GetProcAddress(g_hRealD3D9, "D3DPERF_SetOptions");
    realFn(dwOptions);
}

extern "C" IDirect3D9* WINAPI Direct3DCreate9(UINT SDKVersion)
{
    std::cout << "[VR] Direct3DCreate9: SDKVersion=" << SDKVersion << " returnAddress=" << _ReturnAddress() << "\n";
    LoadRealD3D9();

    auto realFn = (HRESULT(WINAPI*)(UINT, IDirect3D9Ex**))GetProcAddress(g_hRealD3D9, "Direct3DCreate9Ex");
    IDirect3D9Ex* pEx = nullptr;
    auto hr = realFn(SDKVersion, &pEx);
    return pEx;
}
