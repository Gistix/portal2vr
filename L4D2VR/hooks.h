#pragma once
#include <iostream>
#include "MinHook.h"
#include "bitbuf.h"

class Game;
class VR;
class ITexture;
class CViewSetup;
class CUserCmd;
class QAngle;
class Vector;
class edict_t;
class ModelRenderInfo_t;
struct trace_tx;
class IMatRenderContext;
struct vrect_t;
struct Ray_t;
struct VMatrix;
struct Rect_t;
class bf_write;
class bf_read;


template <typename T>
struct Hook {
	T fOriginal;
	LPVOID pTarget;
	bool isEnabled;

	int createHook(LPVOID targetFunc, LPVOID detourFunc)
	{
		if (MH_CreateHook(targetFunc, detourFunc, reinterpret_cast<LPVOID *>(&fOriginal)) != MH_OK)
		{
			char errorString[512];
			sprintf_s(errorString, 512, "Failed to create hook with this signature: %s", typeid(T).name());
			Game::errorMsg(errorString);
			return 1;
		}
		pTarget = targetFunc;
	}

	int enableHook()
	{
		if (!pTarget)
			throw std::invalid_argument("pTarget is empty, did you miss a call to createHook?");

		MH_STATUS status = MH_EnableHook(pTarget);
		if (status != MH_OK)
		{
			char errorString[256];
			sprintf_s(errorString, 256, "Failed to enable hook: %i", status);
			Game::errorMsg(errorString);
			return 1;
		}
		isEnabled = true;
	}

	int disableHook()
	{
		if (MH_DisableHook(pTarget) != MH_OK)
		{
			Game::errorMsg("Failed to disable hook");
			return 1;
		}
		isEnabled = false;
	}
};


// Source Engine functions
typedef ITexture *(__thiscall *tGetRenderTarget)(void *thisptr);
typedef void(__thiscall *tRenderView)(void *thisptr, CViewSetup &setup, CViewSetup &hudViewSetup, int nClearFlags, int whatToDraw);
typedef bool(__thiscall *tCreateMove)(void *thisptr, float flInputSampleTime, CUserCmd *cmd);
typedef void(__thiscall *tEndFrame)(PVOID);
typedef void(__thiscall *tCalcViewModelView)(void *thisptr, const Vector &eyePosition, const QAngle &eyeAngles);
typedef float(__thiscall *tProcessUsercmds)(void *thisptr, edict_t *player, void *buf, int numcmds, int totalcmds, int dropped_packets, bool ignore, bool paused);
typedef int(__cdecl *tReadUsercmd)(void *buf, CUserCmd *move, CUserCmd *from);
typedef void(__thiscall *tWriteUsercmdDeltaToBuffer)(void *thisptr, int a1, void *buf, int from, int to, bool isnewcommand);
typedef int(__cdecl *tWriteUsercmd)(void *buf, CUserCmd *to, CUserCmd *from);
typedef int(__cdecl *tAdjustEngineViewport)(int &x, int &y, int &width, int &height);
typedef void(__thiscall *tViewport)(void *thisptr, int x, int y, int width, int height);
typedef void(__thiscall *tGetViewport)(void *thisptr, int &x, int &y, int &width, int &height);
typedef int(__thiscall *tGetPrimaryAttackActivity)(void *thisptr, void *meleeInfo);
typedef Vector *(__thiscall *tEyePosition)(void *thisptr, Vector *eyePos);
typedef void(__thiscall *tDrawModelExecute)(void *thisptr, void *state, const ModelRenderInfo_t &info, void *pCustomBoneToWorld);
typedef void(__thiscall *tPushRenderTargetAndViewport)(void *thisptr, ITexture *pTexture, ITexture *pDepthTexture, int nViewX, int nViewY, int nViewW, int nViewH);
typedef void(__thiscall *tPopRenderTargetAndViewport)(void *thisptr);
typedef void(__thiscall *tVgui_Paint)(void *thisptr, int mode);
typedef int(__cdecl *tIsSplitScreen)();
typedef DWORD *(__thiscall *tPrePushRenderTarget)(void *thisptr, int a2);
typedef ITexture* (__thiscall* tGetFullScreenTexture)();

typedef bool(__thiscall* tTraceFirePortal)(void* thisptr, const Vector& vTraceStart, const Vector& vDirection, bool bPortal2, int iPlacedBy, void* tr);

typedef void(__thiscall* tPlayerPortalled)(void* thisptr, void* a2, __int64 a3);

typedef int(__thiscall* tGetModeHeight)(void* thisptr);
typedef int(__thiscall* tDrawSelf)(void* thisptr, int x, int y, int w, int h, const void* clr, float flApparentZ);
typedef bool(__cdecl* tClipTransform)(const Vector& point, Vector* pClip);
typedef void(__cdecl* tVGui_GetHudBounds)(int slot, int& x, int& y, int& w, int& h);
typedef void(__cdecl* tVGui_GetPanelBounds)(int slot, int& x, int& y, int& w, int& h);

// HUD
typedef void(__cdecl* tVGUI_UpdateScreenSpaceBounds)(int nNumSplits, int sx, int sy, int sw, int sh);
typedef void(__cdecl* tVGui_GetTrueScreenSize)(int &w, int &h);

typedef void(__cdecl* tGetHudSize)(int& w, int& h);

typedef void(__thiscall* tSetBounds)(void* thisptr, int x, int y, int w, int h);
typedef void(__thiscall* tSetSize)(void* thisptr, int wide, int tall);
typedef void(__thiscall* tGetScreenSize)(void* thisptr, int& wide, int& tall);
typedef void(__thiscall* tPush2DView)(void* thisptr, IMatRenderContext* pRenderContext, const CViewSetup& view, int nFlags, ITexture* pRenderTarget, void* frustumPlanes);
typedef void(__thiscall* tRender)(void* thisptr, vrect_t* rect);
typedef void(__thiscall* tGetClipRect)(void* thisptr, int& x0, int& y0, int& x1, int& y1);

typedef Vector* (__thiscall* tWeapon_ShootPosition)(void* thisptr, Vector* shootPos);
typedef double(__thiscall* tComputeError)(void* thisptr);
typedef bool(__thiscall* tUpdateObject)(void* thisptr, void* pPlayer, float flError, bool bIsTeleport);
typedef bool(__thiscall* tUpdateObjectVM)(void* thisptr, void* pPlayer, float flError);
typedef void(__thiscall* tRotateObject)(void* thisptr, void* pPlayer, float fRotAboutUp, float fRotAboutRight, bool bUseWorldUpInsteadOfPlayerUp);
typedef QAngle&(__thiscall* tEyeAngles)(void* thisptr);

typedef void(__cdecl* tMatrixBuildPerspectiveX)(void*& dst, double flFovX, double flAspect, double flZNear, double flZFar);

typedef int(__cdecl* tGetDefaultFOV)(void*& thisptr);
typedef double(__cdecl* tGetFOV)(void*& thisptr);
typedef double(__cdecl* tGetViewModelFOV)(void*& thisptr);

typedef void(__thiscall* tCreatePingPointer)(void* thisptr, Vector vecDestintaion);
typedef void(__thiscall* tSetDrawOnlyForSplitScreenUser)(void* thisptr, int nSlot);
typedef void(__thiscall* tClientThink)(void* thisptr);
typedef void*(__cdecl* tGetPortalPlayer)(int index);
typedef int(__cdecl* tPrecacheParticleSystem)(const char* pParticleSystemName);
typedef void(__thiscall* tPrecache)(void* thisptr);
typedef bool(__thiscall* tCHudCrosshair_ShouldDraw)(void* thisptr);

typedef void*(__cdecl* tUTIL_Portal_FirstAlongRay)(const Ray_t& ray, float& fMustBeCloserThan);
typedef float(__cdecl* tUTIL_IntersectRayWithPortal)(const Ray_t& ray, const void* pPortal);
typedef void(__cdecl* tUTIL_Portal_AngleTransform)(const VMatrix& matThisToLinked, const QAngle& qSource, QAngle& qTransformed);
typedef int(__thiscall* tEntindex)(void* thisptr);
typedef void*(__thiscall* tGetOwner)(void* thisptr);
typedef void* (__thiscall* tCWeaponPortalgun_FirePortal)(void* thisptr, bool bPortal2, Vector* pVector);

class Hooks
{
public:
	static inline Game *m_Game;
	static inline VR *m_VR;

	static inline Hook<tGetRenderTarget> hkGetRenderTarget;
	static inline Hook<tRenderView> hkRenderView;
	static inline Hook<tCreateMove> hkCreateMove;
	static inline Hook<tEndFrame> hkEndFrame;
	static inline Hook<tCalcViewModelView> hkCalcViewModelView;
	static inline Hook<tProcessUsercmds> hkProcessUsercmds;
	static inline Hook<tReadUsercmd> hkReadUsercmd;
	static inline Hook<tWriteUsercmdDeltaToBuffer> hkWriteUsercmdDeltaToBuffer;
	static inline Hook<tWriteUsercmd> hkWriteUsercmd;
	static inline Hook<tAdjustEngineViewport> hkAdjustEngineViewport;
	static inline Hook<tViewport> hkViewport;
	static inline Hook<tGetViewport> hkGetViewport;
	static inline Hook<tGetPrimaryAttackActivity> hkGetPrimaryAttackActivity;
	static inline Hook<tEyePosition> hkEyePosition;
	static inline Hook<tDrawModelExecute> hkDrawModelExecute;
	static inline Hook<tPushRenderTargetAndViewport> hkPushRenderTargetAndViewport;
	static inline Hook<tPopRenderTargetAndViewport> hkPopRenderTargetAndViewport;
	static inline Hook<tVgui_Paint> hkVgui_Paint;
	static inline Hook<tIsSplitScreen> hkIsSplitScreen;
	static inline Hook<tPrePushRenderTarget> hkPrePushRenderTarget;
	static inline Hook<tGetFullScreenTexture> hkGetFullScreenTexture;
	static inline Hook<tWeapon_ShootPosition> hkWeapon_ShootPosition;
	static inline Hook<tTraceFirePortal> hkTraceFirePortal;

	static inline Hook<tGetModeHeight> hkGetModeHeight;
	static inline Hook<tDrawSelf> hkDrawSelf;
	static inline Hook<tClipTransform> hkClipTransform;
	static inline Hook<tPlayerPortalled> hkPlayerPortalled;
	static inline Hook<tVGui_GetHudBounds> hkVGui_GetHudBounds;
	static inline Hook<tVGui_GetPanelBounds> hkVGui_GetPanelBounds;

	static inline Hook<tVGUI_UpdateScreenSpaceBounds> hkVGUI_UpdateScreenSpaceBounds;
	static inline Hook<tVGui_GetTrueScreenSize> hkVGui_GetTrueScreenSize;

	static inline Hook<tSetBounds> hkSetBounds;
	static inline Hook<tGetScreenSize> hkGetScreenSize;
	static inline Hook<tPush2DView> hkPush2DView;
	static inline Hook<tRender> hkRender;
	static inline Hook<tGetClipRect> hkGetClipRect;
	static inline Hook<tGetHudSize> hkGetHudSize;
	static inline Hook<tSetSize> hkSetSize;
	
	static inline Hook<tComputeError> hkComputeError;
	static inline Hook<tUpdateObject> hkUpdateObject;
	static inline Hook<tUpdateObjectVM> hkUpdateObjectVM;
	static inline Hook<tRotateObject> hkRotateObject;
	static inline Hook<tEyeAngles> hkEyeAngles;

	static inline Hook<tMatrixBuildPerspectiveX> hkMatrixBuildPerspectiveX;
	
	static inline Hook<tGetDefaultFOV> hkGetDefaultFOV;
	static inline Hook<tGetFOV> hkGetFOV;
	static inline Hook<tGetViewModelFOV> hkGetViewModelFOV;

	static inline Hook<tSetDrawOnlyForSplitScreenUser> hkSetDrawOnlyForSplitScreenUser;
	static inline Hook<tClientThink> hkClientThink;
	static inline Hook<tPrecache> hkPrecache;
	static inline Hook<tCHudCrosshair_ShouldDraw> hkCHudCrosshair_ShouldDraw;
	static inline Hook<tCWeaponPortalgun_FirePortal> hkCWeaponPortalgun_FirePortal;

	//Precache

	Hooks() {};
	Hooks(Game *game);

	~Hooks();

	int initSourceHooks();

	// Detour functions
	static ITexture *__fastcall dGetRenderTarget(void *ecx, void *edx);
	static void __fastcall dRenderView(void *ecx, void *edx, CViewSetup &setup, CViewSetup &hudViewSetup, int nClearFlags, int whatToDraw);
	static bool __fastcall dCreateMove(void *ecx, void *edx, float flInputSampleTime, CUserCmd *cmd);
	static void __fastcall dEndFrame(void *ecx, void *edx);
	static void __fastcall dCalcViewModelView(void *ecx, void *edx, const Vector &eyePosition, const QAngle &eyeAngles);
	static int dServerFireTerrorBullets(int playerId, const Vector &vecOrigin, const QAngle &vecAngles, int a4, int a5, int a6, float a7);
	static int dClientFireTerrorBullets(int playerId, const Vector &vecOrigin, const QAngle &vecAngles, int a4, int a5, int a6, float a7);
	static float __fastcall dProcessUsercmds(void *ecx, void *edx, edict_t *player, void *buf, int numcmds, int totalcmds, int dropped_packets, bool ignore, bool paused);
	static int dReadUsercmd(bf_read *buf, CUserCmd *move, CUserCmd *from);
	static int dWriteUsercmd(bf_write *buf, CUserCmd *to, CUserCmd *from);
	static void dAdjustEngineViewport(int &x, int &y, int &width, int &height);
	static void __fastcall dViewport(void *ecx, void *edx, int x, int y, int width, int height);
	static void __fastcall dGetViewport(void *ecx, void *edx, int &x, int &y, int &width, int &height);
	static int __fastcall dTestMeleeSwingCollisionClient(void *ecx, void *edx, Vector const &vec);
	static int __fastcall dTestMeleeSwingCollisionServer(void *ecx, void *edx, Vector const &vec);
	static void __fastcall dDoMeleeSwingServer(void *ecx, void *edx);
	static void __fastcall dStartMeleeSwingServer(void *ecx, void *edx, void *player, bool a3);
	static int __fastcall dPrimaryAttackServer(void *ecx, void *edx);
	static void __fastcall dItemPostFrameServer(void *ecx, void *edx);
	static int __fastcall dGetPrimaryAttackActivity(void *ecx, void *edx, void* meleeInfo);
	static Vector *__fastcall dEyePosition(void *ecx, void *edx, Vector *eyePos);
	static void __fastcall dDrawModelExecute(void *ecx, void* edx, void *state, const ModelRenderInfo_t &info, void *pCustomBoneToWorld);
	static void __fastcall dPushRenderTargetAndViewport(void *ecx, void *edx, ITexture *pTexture, ITexture *pDepthTexture, int nViewX, int nViewY, int nViewW, int nViewH);
	static void __fastcall dPopRenderTargetAndViewport(void *ecx, void *edx);
	static void __fastcall dVGui_Paint(void *ecx, void *edx, int mode);
	static int __fastcall dIsSplitScreen();
	static DWORD *__fastcall dPrePushRenderTarget(void *ecx, void *edx, int a2);
	static ITexture *__fastcall dGetFullScreenTexture();

	// Fire portals from right controller
	static bool __fastcall dTraceFirePortal(void* ecx, void* edx, const Vector& vTraceStart, const Vector& vDirection, bool bPortal2, int iPlacedBy, void* tr);

	// Portalling angle fix
	static void __fastcall dPlayerPortalled(void* ecx, void* edx, void* a2, __int64 a3);

	// Crosshair
	static int __fastcall dGetModeHeight(void* ecx, void* edx);
	static int __fastcall dDrawSelf(void* ecx, void* edx, int x, int y, int w, int h, const void* clr, float flApparentZ);
	static bool dClipTransform(const Vector& point, Vector* pScreen);
	static void __fastcall dSetBounds(void* ecx, void* edx, int x, int y, int w, int h);
	static void __fastcall dSetSize(void* ecx, void* edx, int wide, int tall);
	static void __fastcall dGetScreenSize(void* ecx, void* edx, int& wide, int& tall);
	static void dGetHudSize(int& w, int& h);
	static void dVGui_GetHudBounds(int slot, int& x, int& y, int& w, int& h);
	static void dVGui_GetPanelBounds(int slot, int& x, int& y, int& w, int& h);

	static void dVGUI_UpdateScreenSpaceBounds(int nNumSplits, int sx, int sy, int sw, int sh);
	static void dVGui_GetTrueScreenSize(int &w, int &h);

	static void __fastcall dPush2DView(void* ecx, void* edx, IMatRenderContext* pRenderContext, const CViewSetup& view, int nFlags, ITexture* pRenderTarget, void* frustumPlanes);
	static void __fastcall dRender(void* ecx, void* edx, vrect_t* rect);
	static bool ScreenTransform(const Vector& point, Vector* pScreen, int width, int height);
	static void __fastcall dGetClipRect(void* ecx, void* edx, int& x0, int& y0, int& x1, int& y1);

	// Grabbable objects
	static Vector* __fastcall dWeapon_ShootPosition(void* ecx, void* edx, Vector* shootPos);
	static double __fastcall dComputeError(void* ecx, void* edx);
	static bool __fastcall dUpdateObject(void* ecx, void* edx, void* pPlayer, float flError, bool bIsTeleport = false);
	static bool __fastcall dUpdateObjectVM(void* ecx, void* edx, void* pPlayer, float flError);
	static void __fastcall dRotateObject(void* ecx, void* edx, void* pPlayer, float fRotAboutUp, float fRotAboutRight, bool bUseWorldUpInsteadOfPlayerUp);
	static QAngle& __fastcall dEyeAngles(void* ecx, void* edx);

	static int __fastcall dGetDefaultFOV(void* ecx, void* edx);
	static double __fastcall dGetFOV(void* ecx, void* edx);
	static double __fastcall dGetViewModelFOV(void* ecx, void* edx);

	static void __fastcall dSetDrawOnlyForSplitScreenUser(void* ecx, void* edx, int nSlot);
	static void __fastcall dClientThink(void* ecx, void* edx);
	static void __fastcall dPrecache(void* ecx, void* edx);
	static bool __fastcall dCHudCrosshair_ShouldDraw(void* ecx, void* edx);

	static void* __fastcall dCWeaponPortalgun_FirePortal(void* ecx, void* edx, bool bPortal2, Vector* pVector = 0);

	static inline int m_PushHUDStep;
	static inline bool m_PushedHud;

	static inline tCreatePingPointer CreatePingPointer;
	static inline tGetPortalPlayer GetPortalPlayer;
	static inline tPrecacheParticleSystem PrecacheParticleSystem;

	static inline tUTIL_Portal_FirstAlongRay UTIL_Portal_FirstAlongRay;
	static inline tUTIL_IntersectRayWithPortal UTIL_IntersectRayWithPortal;
	static inline tUTIL_Portal_AngleTransform UTIL_Portal_AngleTransform;
	static inline tEntindex EntityIndex;
	static inline tGetOwner GetOwner;
	static inline tGetFullScreenTexture GetFullScreenTexture;
};