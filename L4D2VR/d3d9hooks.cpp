#include "d3d9hooks.h"
#include "game.h"
#include "vr.h"

static bool g_DeviceHooksSetup = false;
static bool g_TextureHookSetup = false;
static bool g_BufferHookSetup = false;
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
	HRESULT hr;
	IDirect3D9Ex* d3d9ex = nullptr;
	d3d9->QueryInterface(IID_IDirect3D9Ex, (void**)&d3d9ex);

	std::cout << "[VR] dCreateDevice: using CreateDeviceEx\n";

	hr = d3d9ex->CreateDeviceEx(Adapter, DeviceType, hFocusWindow,
		BehaviorFlags, pPresentationParameters, nullptr,
		(IDirect3DDevice9Ex**)ppReturnedDevice);

	d3d9ex->Release();

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

		void** devVtable = *(void***)*ppReturnedDevice;

		if (!g_TextureHookSetup)
		{
			MH_CreateHook(devVtable[23], &D3D9Hooks::dCreateTexture, (LPVOID*)&D3D9Hooks::hkCreateTexture.fOriginal);
			MH_EnableHook(devVtable[23]);
			MH_CreateHook(devVtable[24], &D3D9Hooks::dCreateVolumeTexture, (LPVOID*)&D3D9Hooks::hkCreateVolumeTexture.fOriginal);
			MH_EnableHook(devVtable[24]);
			MH_CreateHook(devVtable[25], &D3D9Hooks::dCreateCubeTexture, (LPVOID*)&D3D9Hooks::hkCreateCubeTexture.fOriginal);
			MH_EnableHook(devVtable[25]);
			g_TextureHookSetup = true;
			std::cout << "[VR] dCreateDevice: CreateTexture hook installed (vtable[23])\n";
			std::cout << "[VR] dCreateDevice: CreateVolumeTexture hook installed (vtable[24])\n";
			std::cout << "[VR] dCreateDevice: CreateCubeTexture hook installed (vtable[25])\n";
		}

		if (!g_BufferHookSetup)
		{
			MH_CreateHook(devVtable[26], &D3D9Hooks::dCreateVertexBuffer, (LPVOID*)&D3D9Hooks::hkCreateVertexBuffer.fOriginal);
			MH_EnableHook(devVtable[26]);
			MH_CreateHook(devVtable[27], &D3D9Hooks::dCreateIndexBuffer, (LPVOID*)&D3D9Hooks::hkCreateIndexBuffer.fOriginal);
			MH_EnableHook(devVtable[27]);
			g_BufferHookSetup = true;
			std::cout << "[VR] dCreateDevice: CreateVertexBuffer hook installed (vtable[26])\n";
			std::cout << "[VR] dCreateDevice: CreateIndexBuffer hook installed (vtable[27])\n";
		}

		if (!g_PresentHookSetup)
		{
			MH_CreateHook(devVtable[17], &D3D9Hooks::dPresent, (LPVOID*)&D3D9Hooks::hkPresent.fOriginal);
			MH_EnableHook(devVtable[17]);
			g_PresentHookSetup = true;
			std::cout << "[VR] dCreateDevice: Present hook installed (vtable[17])\n";
		}
	}

	return hr;
}

// Mimics old D3DPOOL_MANAGED behaviour (CPU + GPU access)
static void OverrideTextureParams(DWORD& Usage, D3DPOOL& Pool, const char* name)
{
	if (Pool == D3DPOOL_MANAGED)
	{
		std::cout << "[VR] " << name << ": overriding pool MANAGED -> DEFAULT\n";
		Pool = D3DPOOL_DEFAULT;

		if (Usage == 0) {
			std::cout << "[VR] " << name << ": overriding usage None -> D3DUSAGE_DYNAMIC\n";
			Usage = D3DUSAGE_DYNAMIC;
		}
	}
}

HRESULT __stdcall D3D9Hooks::dCreateTexture(IDirect3DDevice9* device, UINT Width, UINT Height, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DTexture9** ppTexture, HANDLE* pSharedHandle)
{
	OverrideTextureParams(Usage, Pool, "dCreateTexture");

	if (!m_VR)
		return hkCreateTexture.fOriginal(device, Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);

	const auto& creatingID = m_VR->m_CreatingTextureID;
	if (creatingID == VR::Texture_None)
		return hkCreateTexture.fOriginal(device, Width, Height, Levels, Usage, Format, Pool, ppTexture, pSharedHandle);

	std::cout << "[VR] dCreateTexture: id=" << creatingID << " " << Width << "x" << Height
		<< " Levels=" << Levels << " Pool=" << Pool << " Usage=" << std::hex << Usage << std::dec << "\n";

	HANDLE sharedHandle = nullptr;
	HRESULT hr = hkCreateTexture.fOriginal(device, Width, Height, Levels, Usage, Format, Pool, ppTexture, &sharedHandle);

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

HRESULT __stdcall D3D9Hooks::dCreateVolumeTexture(IDirect3DDevice9* device, UINT Width, UINT Height, UINT Depth, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DVolumeTexture9** ppVolumeTexture, HANDLE* pSharedHandle)
{
	OverrideTextureParams(Usage, Pool, "dCreateVolumeTexture");
	return hkCreateVolumeTexture.fOriginal(device, Width, Height, Depth, Levels, Usage, Format, Pool, ppVolumeTexture, pSharedHandle);
}

HRESULT __stdcall D3D9Hooks::dCreateCubeTexture(IDirect3DDevice9* device, UINT EdgeLength, UINT Levels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DCubeTexture9** ppCubeTexture, HANDLE* pSharedHandle)
{
	OverrideTextureParams(Usage, Pool, "dCreateCubeTexture");
	return hkCreateCubeTexture.fOriginal(device, EdgeLength, Levels, Usage, Format, Pool, ppCubeTexture, pSharedHandle);
}

HRESULT __stdcall D3D9Hooks::dCreateVertexBuffer(IDirect3DDevice9* device, UINT Length, DWORD Usage, DWORD FVF, D3DPOOL Pool, IDirect3DVertexBuffer9** ppVertexBuffer, HANDLE* pSharedHandle)
{
	if (Pool != D3DPOOL_DEFAULT)
	{
		std::cout << "[VR] dCreateVertexBuffer: overriding pool " << Pool << " -> D3DPOOL_DEFAULT\n";
	}
	return hkCreateVertexBuffer.fOriginal(device, Length, Usage, FVF, D3DPOOL_DEFAULT, ppVertexBuffer, pSharedHandle);
}

HRESULT __stdcall D3D9Hooks::dCreateIndexBuffer(IDirect3DDevice9* device, UINT Length, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, IDirect3DIndexBuffer9** ppIndexBuffer, HANDLE* pSharedHandle)
{
	if (Pool != D3DPOOL_DEFAULT)
	{
		std::cout << "[VR] dCreateIndexBuffer: overriding pool " << Pool << " -> D3DPOOL_DEFAULT\n";
	}
	return hkCreateIndexBuffer.fOriginal(device, Length, Usage, Format, D3DPOOL_DEFAULT, ppIndexBuffer, pSharedHandle);
}

HRESULT __stdcall D3D9Hooks::dPresent(IDirect3DDevice9* device, const RECT* pSourceRect, const RECT* pDestRect, HWND hDestWindowOverride, const RGNDATA* pDirtyRegion)
{
	if (m_VR && m_VR->m_IsInitialized)
		m_VR->Update();
	return hkPresent.fOriginal(device, pSourceRect, pDestRect, hDestWindowOverride, pDirtyRegion);
}
