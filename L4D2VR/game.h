#pragma once
#include <cstdint>
#include <array>
#include <Windows.h>
#include "vector.h"

struct IDirect3DDevice9;
struct ID3D11Device;
struct ID3D11DeviceContext;
class D3D9Hooks;

class IClientEntityList;
class IEngineTrace;
class IEngineClient;
class IMaterialSystem;
class IBaseClientDLL;
class IViewRender;
class IViewRender;
class CBaseEntity;
class IModelInfo;
class IModelRender;
class IMaterial;
class IInput;
class ISurface;
class IClientMode;
class C_BasePlayer;
struct model_t;

class Game;
class Offsets;
class VR;
class Hooks;

inline Game *g_Game;

struct Player
{
    C_BasePlayer *pPlayer;
    bool isUsingVR;
    QAngle controllerAngle;
    Vector controllerPos;
    QAngle prevControllerAngle;

    Player()
        : isUsingVR(false),
        controllerAngle({ 0,0,0 }),
        controllerPos({ 0,0,0 }),
        prevControllerAngle({ 0,0,0 })
    {}
};

class Game
{
public:
    IClientEntityList* m_ClientEntityList = nullptr;
    IEngineTrace* m_EngineTrace = nullptr;
    IEngineClient* m_EngineClient = nullptr;
    IMaterialSystem* m_MaterialSystem = nullptr;
    IBaseClientDLL* m_BaseClientDll = nullptr;
    IViewRender* m_ClientViewRender = nullptr;
    IViewRender* m_EngineViewRender = nullptr;
    IModelInfo* m_ModelInfo = nullptr;
    IModelRender* m_ModelRender = nullptr;
    IInput* m_VguiInput = nullptr;
    ISurface* m_VguiSurface = nullptr;
    IClientMode* m_ClientMode = nullptr;

    uintptr_t m_BaseEngine;
    uintptr_t m_BaseClient;
    uintptr_t m_BaseServer;
    uintptr_t m_BaseMaterialSystem;
    uintptr_t m_BaseVgui2;

    Vector m_singlePlayerPortalColors[3] = { Vector(255.0f, 255.0f, 255.0f), Vector(64.0f, 160.0f, 255.0f), Vector(255.0f, 160.0f, 32.0f) };

    Offsets *m_Offsets = nullptr;
    VR *m_VR = nullptr;
    Hooks *m_Hooks = nullptr;
    D3D9Hooks *m_D3D9Hooks = nullptr;

    IDirect3DDevice9 *m_D3D9Device = nullptr;
    ID3D11Device *m_D3D11Device = nullptr;
    ID3D11DeviceContext *m_D3D11Context = nullptr;

    bool m_Initialized = false;

    std::array<Player, 24> m_PlayersVRInfo;
    int m_CurrentUsercmdID = -1;

    model_t *m_ArmsModel = nullptr;
    IMaterial *m_ArmsMaterial = nullptr;
    bool m_CachedArmsModel = false;

    Game();
    void Initialize();

    void *GetInterface(const char *dllname, const char *interfacename);

    static void errorMsg(const char *msg);

    CBaseEntity *GetClientEntity(int entityIndex);
    char *getNetworkName(uintptr_t *entity);
    void ClientCmd(const char *szCmdString);
    void ClientCmd_Unrestricted(const char *szCmdString);

    typedef void *(__cdecl *tCreateInterface)(const char *name, int *returnCode);
};

