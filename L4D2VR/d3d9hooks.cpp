#include "d3d9hooks.h"
#include "game.h"
#include "vr.h"

static bool g_DeviceHooksSetup = false;
static bool g_TextureHookSetup = false;
static bool g_PresentHookSetup = false;

D3D9Hooks::D3D9Hooks()
{
}

void D3D9Hooks::SetupDeviceHooks(IDirect3D9* pD3D)
{
	if (g_DeviceHooksSetup || !pD3D)
		return;

	void** vtable = *(void***)pD3D;
	MH_CreateHook(vtable[16], &D3D9Hooks::dCreateDevice, (LPVOID*)&D3D9Hooks::hkCreateDevice.fOriginal);
	MH_EnableHook(vtable[16]);
	g_DeviceHooksSetup = true;

	auto hModule = GetModuleHandle("shaderapidx9.dll");
	std::cout << "shaderapidx9 Base address: " << hModule << std::endl;
}

HRESULT __stdcall D3D9Hooks::dCreateDevice(
	IDirect3D9* d3d9, UINT Adapter, D3DDEVTYPE DeviceType, HWND hFocusWindow,
	DWORD BehaviorFlags, D3DPRESENT_PARAMETERS* pPresentationParameters,
	IDirect3DDevice9** ppReturnedDevice)
{
	HRESULT hr = hkCreateDevice.fOriginal(d3d9, Adapter, DeviceType, hFocusWindow,
		BehaviorFlags, pPresentationParameters, ppReturnedDevice);

	std::cout << "[VR] dCreateDevice: hr=" << std::hex << hr << " p=" << (void*)*ppReturnedDevice << std::dec << "\n";

	if (SUCCEEDED(hr) && *ppReturnedDevice)
	{
		if (m_Game)
		{
			m_Game->m_D3D9Device = *ppReturnedDevice;

			if (!m_Game->m_D3D11Device)
			{
				HRESULT d3d11hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
					D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0, D3D11_SDK_VERSION,
					&m_Game->m_D3D11Device, nullptr, &m_Game->m_D3D11Context);
				std::cout << "[VR] D3D11CreateDevice: hr=" << std::hex << d3d11hr << std::dec << "\n";
			}
		}

		if (!g_TextureHookSetup)
		{
			void** devVtable = *(void***)*ppReturnedDevice;
			MH_CreateHook(devVtable[23], &D3D9Hooks::dCreateTexture, (LPVOID*)&D3D9Hooks::hkCreateTexture.fOriginal);
			MH_EnableHook(devVtable[23]);
			g_TextureHookSetup = true;
			std::cout << "[VR] dCreateDevice: CreateTexture hook installed (vtable[23])\n";
		}

		if (!g_PresentHookSetup)
		{
			void** devVtable = *(void***)*ppReturnedDevice;
			MH_CreateHook(devVtable[17], &D3D9Hooks::dPresent, (LPVOID*)&D3D9Hooks::hkPresent.fOriginal);
			MH_EnableHook(devVtable[17]);
			g_PresentHookSetup = true;
			std::cout << "[VR] dCreateDevice: Present hook installed (vtable[17])\n";
		}
	}

	return hr;
}

HRESULT __stdcall D3D9Hooks::dCreateTexture(IDirect3DDevice9* device, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
	if (!m_VR)
		return hkCreateTexture.fOriginal(device, Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);

	const auto& creatingID = m_VR->m_CreatingTextureID;
	if (creatingID == VR::Texture_None)
		return hkCreateTexture.fOriginal(device, Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);

	std::cout << "[VR] dCreateTexture: id=" << creatingID << " " << Width << "x" << Height
		<< " Levels=" << Levels << " Pool=" << Pool << " Usage=" << std::hex << Usage << std::dec << "\n";

	HANDLE sharedHandle = nullptr;
	HRESULT hr = hkCreateTexture.fOriginal(device, Width, Height, 1, Usage, Format, D3DPOOL_DEFAULT, ppTexture, &sharedHandle);

	std::cout << "[VR] dCreateTexture: hr=0x" << std::hex << hr << " p=" << (void*)*ppTexture << " handle=" << (void*)sharedHandle << std::dec << "\n";

	if (SUCCEEDED(hr) && *ppTexture)
	{
		auto &dst = m_VR->m_D3D9Textures[creatingID];
		dst.texture = *ppTexture;
		dst.sharedHandle = sharedHandle;

		if (m_Game && m_Game->m_D3D11Device && sharedHandle)
		{
			HRESULT openHr = m_Game->m_D3D11Device->OpenSharedResource(sharedHandle, __uuidof(ID3D11Texture2D), (void**)&m_VR->m_D3D11Textures[creatingID]);
			std::cout << "[VR] dCreateTexture: OpenSharedResource hr=0x" << std::hex << openHr << " d3d11tex=" << (void*)m_VR->m_D3D11Textures[creatingID] << std::dec << "\n";
		}
		else
		{
			std::cout << "[VR] dCreateTexture: skip OpenSharedResource (d3d11=" << (void*)(m_Game ? m_Game->m_D3D11Device : nullptr) << " handle=" << (void*)sharedHandle << ")\n";
		}
	}

	return hr;
}

HRESULT __stdcall D3D9Hooks::dPresent(IDirect3DDevice9* device, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	if (m_VR && m_VR->m_IsInitialized)
		m_VR->Update();
	return hkPresent.fOriginal(device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}
