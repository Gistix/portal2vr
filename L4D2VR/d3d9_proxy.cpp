#include <Windows.h>
#include <d3d9.h>
#include <iostream>

extern void SetupD3D9DeviceHooks(IDirect3D9* pD3D);

EXTERN_C const IID IID_IDirect3D9 = { 0x81bdcbca, 0x64d4, 0x426d, {0xae, 0x8d, 0xad, 0x1, 0x47, 0xf4, 0x27, 0x5c} };
EXTERN_C const IID IID_IDirect3D9Ex = { 0x02177241, 0x69FC, 0x400C, {0x8F, 0xF1, 0x93, 0xA4, 0x4D, 0xF6, 0x86, 0x1D} };

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

    auto realExFn = (HRESULT(WINAPI*)(UINT, IDirect3D9Ex**))GetProcAddress(g_hRealD3D9, "Direct3DCreate9Ex");
    IDirect3D9Ex* pD3D9Ex = nullptr;
    auto hr = realExFn(SDKVersion, &pD3D9Ex);

    if (pD3D9Ex)
    {
        SetupD3D9DeviceHooks(pD3D9Ex);
    }
    return pD3D9Ex;
}
