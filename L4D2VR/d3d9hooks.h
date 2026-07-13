#pragma once
#include <d3d9.h>
#include <d3d11.h>
#include "MinHook.h"
#include "hooks.h"
#include <iostream>

class Game;
class VR;

template <typename T>
struct Hook;

typedef HRESULT(__stdcall* tCreateDeviceFn)(IDirect3D9* d3d9, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDevice);
typedef HRESULT(__stdcall* tCreateTexture)(IDirect3DDevice9* device, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle);
typedef HRESULT(__stdcall* tPresent)(IDirect3DDevice9* device, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);

class D3D9Hooks
{
public:
	D3D9Hooks();

	static inline Game* m_Game = nullptr;
	static inline VR* m_VR = nullptr;

	static inline Hook<tCreateDeviceFn> hkCreateDevice;
	static inline Hook<tCreateTexture> hkCreateTexture;
	static inline Hook<tPresent> hkPresent;

	static void SetupDeviceHooks(IDirect3D9* pD3D);
	static HRESULT __stdcall dCreateDevice(IDirect3D9* d3d9, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow, DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters, IDirect3DDevice9** ppReturnedDevice);
	static HRESULT __stdcall dCreateTexture(IDirect3DDevice9* device, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle);
	static HRESULT __stdcall dPresent(IDirect3DDevice9* device, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion);
};
