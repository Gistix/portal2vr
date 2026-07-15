//========= Copyright Valve Corporation, All rights reserved. ============//

#pragma once

#include <math.h>
#include "game.h"
#include "offsets.h"
#include "cnewparticleeffect.h"
#include "usercmd.h"
#include "material.h"
#include "worldsize.h"
#include <unordered_map>

#define IN_ATTACK		(1 << 0)
#define IN_JUMP			(1 << 1)
#define IN_DUCK			(1 << 2)
#define IN_FORWARD		(1 << 3)
#define IN_BACK			(1 << 4)
#define IN_USE			(1 << 5)
#define IN_CANCEL		(1 << 6)
#define IN_LEFT			(1 << 7)
#define IN_RIGHT		(1 << 8)
#define IN_MOVELEFT		(1 << 9)
#define IN_MOVERIGHT	(1 << 10)
#define IN_ATTACK2		(1 << 11)
#define IN_RUN			(1 << 12)
#define IN_RELOAD		(1 << 13)
#define IN_ALT1			(1 << 14)
#define IN_ALT2			(1 << 15)
#define IN_SCORE		(1 << 16)   // Used by client.dll for when scoreboard is held down
#define IN_SPEED		(1 << 17)	// Player is holding the speed key
#define IN_WALK			(1 << 18)	// Player holding walk key
#define IN_ZOOM			(1 << 19)	// Zoom key for HUD zoom
#define IN_WEAPON1		(1 << 20)	// weapon defines these bits
#define IN_WEAPON2		(1 << 21)	// weapon defines these bits
#define IN_BULLRUSH		(1 << 22)
#define IN_GRENADE1		(1 << 23)	// grenade 1
#define IN_GRENADE2		(1 << 24)	// grenade 2
#define	IN_LOOKSPIN		(1 << 25)

#define MAX_LINEAR_SPEED 175

class C_BaseCombatWeapon;
class C_WeaponCSBase;

enum ClearFlags_t
{
	VIEW_CLEAR_COLOR = 0x1,
	VIEW_CLEAR_DEPTH = 0x2,
	VIEW_CLEAR_FULL_TARGET = 0x4,
	VIEW_NO_DRAW = 0x8,
	VIEW_CLEAR_OBEY_STENCIL = 0x10, // Draws a quad allowing stencil test to clear through portals
	VIEW_CLEAR_STENCIL = 0x20,
};

enum RenderViewInfo_t
{
	RENDERVIEW_UNSPECIFIED = 0,
	RENDERVIEW_DRAWVIEWMODEL = (1 << 0),
	RENDERVIEW_DRAWHUD = (1 << 1),
	RENDERVIEW_SUPPRESSMONITORRENDERING = (1 << 2),
};

struct Rect_t
{
	int x, y;
	int width, height;
};


struct vrect_t
{
	int				x, y, width, height;
	vrect_t* pnext;
};

struct PositionAngle
{
	Vector position;
	QAngle angle;
};

class IClientEntityList
{
public:
	virtual	~IClientEntityList() { }

	// Get IClientNetworkable interface for specified entity
	virtual void* GetClientNetworkable(int entnum) = 0;

	virtual void* GetClientNetworkableArray(void) = 0;
	virtual void* GetClientEntity(int entnum) = 0;

	// Returns number of entities currently in use
	virtual int  NumberOfEntities(bool bIncludeNonNetworkable) = 0;

	virtual void* GetClientUnknownFromHandle(int hEnt) = 0;
	virtual void* GetClientNetworkableFromHandle(int hEnt) = 0;

	// NOTE: This function is only a convenience wrapper.
	// It returns GetClientNetworkable( entnum )->GetIClientEntity().
	virtual void* GetClientEntityFromHandle(int hEnt) = 0;




    // Returns highest index actually used
    virtual int					GetHighestEntityIndex(void) = 0;

    // Sizes entity list to specified size
    virtual void				SetMaxEntities(int maxents) = 0;
    virtual int					GetMaxEntities() = 0;
};



typedef struct player_info_s
{
	char pad_0x00[0x10];
	char            name[128];
	int                userID;
	char            guid[33];
	unsigned long    friendsID;
	char            friendsName[128];
	bool            fakeplayer;
	bool            ishltv;
	unsigned int    customFiles[4];
	unsigned char    filesDownloaded;
	char pad_big[0x200];
} player_info_t;


class IClientEngineTools
{
public:
	virtual void *fn0() = 0;
	virtual void *fn1() = 0;
	virtual void *fn2() = 0;
	virtual void *fn3() = 0;
	virtual void *fn4() = 0;
	virtual void *fn5() = 0;
	virtual void *fn6() = 0;
	virtual void *fn7() = 0;
	virtual void *fn8() = 0;
	virtual void *fn9() = 0;
	virtual void *fn10() = 0;
	virtual void *fn11() = 0;
	virtual void *fn12() = 0;
	virtual bool IsThirdPersonCamera() = 0;
};

class IEngineClient
{
public:
	virtual void *GetIntersectingSurfaces() = 0;
	virtual void *GetLightForPoint() = 0;
	virtual void *TraceLineMaterialAndLighting() = 0;
	virtual void *ParseFile() = 0;
	virtual void *CopyLocalFile() = 0;
	virtual void *GetScreenSize() = 0;
	virtual void *ServerCmd() = 0;
	virtual void *ClientCmd(const char *szCmdString) = 0;
	virtual bool GetPlayerInfo(int ent_num, player_info_t *pinfo) = 0;
	virtual int GetPlayerForUserID(int userID) = 0;
	virtual void TextMessageGet(char const*) = 0;
	virtual bool Con_IsVisible() = 0;
	virtual int GetLocalPlayer(void) = 0;
	virtual int fn13() = 0;
	virtual int fn14() = 0;
	virtual int fn15() = 0;
	virtual int fn16() = 0;
	virtual int fn17() = 0;
	virtual QAngle* GetViewAngles(QAngle &angle) = 0;
	virtual QAngle* SetViewAngles(QAngle &angle) = 0;
	virtual void *sub_1005D230() = 0;
	virtual void *sub_1005D280() = 0;
	virtual void *sub_1005D2A0() = 0;
	virtual void *sub_1005D2C0() = 0;
	virtual void *sub_1005D2D0() = 0;
	virtual bool IsInGame() = 0;
	virtual void *sub_1005F150() = 0;
	virtual void *sub_1005D2F0() = 0;
	virtual void *sub_1005D300() = 0;
	virtual void *sub_1005D350() = 0;
	virtual void *sub_1005D3B0() = 0;
	virtual void *sub_1005D430() = 0;
	virtual void *sub_1005D460() = 0;
	virtual void *sub_1005D5A0() = 0;
	virtual void *sub_1005D4F0() = 0;
	virtual void *sub_1005D5B0() = 0;
	virtual void *sub_1005D5C0() = 0;
	virtual void *sub_1005D5D0() = 0;
	virtual void *sub_1005D5E0() = 0;
	virtual void *sub_1005D600() = 0;
	virtual void *sub_1005D620() = 0;
	virtual void *sub_1005D640() = 0;
	virtual void *sub_1005D710() = 0;
	virtual void *sub_1005D720() = 0;
	virtual void *sub_1005D790() = 0;
	virtual void *sub_1005D7C0() = 0;
	virtual void *sub_1005D840() = 0;
	virtual void *sub_1005D880() = 0;
	virtual void *sub_1005D890() = 0;
	virtual void *sub_1005D8A0() = 0;
	virtual void *sub_1005D8D0() = 0;
	virtual void *sub_1005F160() = 0;
	virtual void *sub_1005F190() = 0;
	virtual void *sub_1005DA90() = 0;
	virtual void *sub_1005DAA0() = 0;
	virtual void *sub_1005DAB0() = 0;
	virtual void *sub_1005DAC0() = 0;
	virtual void *sub_1005DAE0() = 0;
	virtual void *sub_1005DB40() = 0;
	virtual void *sub_1005DB70() = 0;
	virtual void *sub_1005DBA0() = 0;
	virtual void *sub_1005DBC0() = 0;
	virtual void *sub_1005DBE0() = 0;
	virtual void *sub_1005DC10() = 0;
	virtual void *sub_1005DC40() = 0;
	virtual void *sub_1005DC60() = 0;
	virtual void *sub_1005DC80() = 0;
	virtual void *sub_1005DCA0() = 0;
	virtual void *sub_1005D7E0() = 0;
	virtual void *sub_1005DCC0() = 0;
	virtual void *sub_1005DCE0() = 0;
	virtual void *sub_1005DD00() = 0;
	virtual void *sub_1005DD20() = 0;
	virtual void *sub_1005DD40() = 0;
	virtual void *sub_100606A0() = 0;
	virtual void *sub_10060670() = 0;
	virtual void *sub_1005DAD0() = 0;
	virtual void *sub_1005D7B0() = 0;
	virtual void *sub_1005DD50() = 0;
	virtual void *sub_1005DD60() = 0;
	virtual void *sub_1005DD70() = 0;
	virtual void *sub_1005DDE0() = 0;
	virtual void *sub_1005DDF0() = 0;
	virtual void *sub_1005DE00() = 0;
	virtual void *sub_1005DE10() = 0;
	virtual void *sub_1005DE20() = 0;
	virtual bool IsPaused() = 0;
	virtual void *sub_1005DD90() = 0;
	virtual void *sub_1005DDA0() = 0;
	virtual void *sub_1005DE30() = 0;
	virtual void *sub_1005D900() = 0;
	virtual void *sub_1005D910() = 0;
	virtual void *sub_1005D9B0() = 0;
	virtual void *sub_1005DE40() = 0;
	virtual void *sub_1005F1C0() = 0;
	virtual void *sub_1005DE80() = 0;
	virtual void *sub_1005DE90() = 0;
	virtual void *sub_1005DEB0() = 0;
	virtual void *sub_1005CB30() = 0;
	virtual void *sub_1005CB40() = 0;
	virtual void *sub_1005DF00() = 0;
	virtual void *sub_1005DF20() = 0;
	virtual void *sub_1005CF70() = 0;
	virtual void *sub_1005D000() = 0;
	virtual void *sub_1005DED0() = 0;
	virtual void *sub_1005CBB0() = 0;
	virtual void* sub_1005CBB0_1() = 0;
	virtual void* sub_1005CBB0_2() = 0;
	virtual void *ClientCmd_Unrestricted(const char *szCmdString) = 0;
};

class IModelInfo
{
public:
	virtual	~IModelInfo(void) { }
	// Returns model_t* pointer for a model given a precached or dynamic model index.
	virtual void *GetModel(int modelindex) = 0;

	// Returns index of model by name for precached or known dynamic models.
	// Does not adjust reference count for dynamic models.
	virtual int	GetModelIndex(const char *name) const = 0;

	// Returns name of model
	virtual char *GetModelName(void *model) const = 0;
};

struct model_t;

struct ModelRenderInfo_t
{
	Vector origin;
	QAngle angles;
	void *pRenderable;
	model_t *pModel;
	const matrix3x4_t *pModelToWorld;
	const matrix3x4_t *pLightingOffset;
	const Vector *pLightingOrigin;
	int flags;
	int entity_index;
	int skin;
	int body;
	int hitboxset;
	int instance;

	ModelRenderInfo_t()
	{
		pModelToWorld = NULL;
		pLightingOffset = NULL;
		pLightingOrigin = NULL;
	}
};


enum StereoEye_t
{
	STEREO_EYE_MONO = 0,
	STEREO_EYE_LEFT = 1,
	STEREO_EYE_RIGHT = 2,
	STEREO_EYE_MAX = 3,
};

enum MotionBlurMode_t
{
	MOTION_BLUR_DISABLE = 1,
	MOTION_BLUR_GAME = 2,			// Game uses real-time inter-frame data
	MOTION_BLUR_SFM = 3				// Use SFM data passed in CViewSetup structure
};

class VMatrix;

class CViewSetup
{
public:
	inline char* STR() {
		char errorString[512];
		sprintf_s(errorString, 512, "X: %i (%i), Y: %i (%i)", x, m_nUnscaledX, y, m_nUnscaledY, width, m_nUnscaledWidth, height, m_nUnscaledHeight, fov, fovViewmodel);
		return errorString;
	}

	int32_t x; //0x0000
	float m_nUnscaledX; //0x0004
	int32_t y; //0x0008
	float m_nUnscaledY; //0x000C
	int32_t width; //0x0010
	int32_t m_nUnscaledWidth; //0x0014
	int32_t height; //0x0018
	int32_t m_nUnscaledHeight; //0x001C
	char pad_0020[72]; //0x0020
	float fov; //0x0068
	float fovViewmodel; //0x006C
	Vector origin; //0x0070
	Vector angles; //0x007C
	float zNear; //0x0088
	float zFar; //0x008C
	float zNearViewmodel; //0x0090
	float zFarViewmodel; //0x0094
	float m_flAspectRatio; //0x0098
	float m_flNearBlurDepth; //0x009C
	float m_flNearFocusDepth; //0x00A0
	float m_flFarFocusDepth; //0x00A4
	float m_flFarBlurDepth; //0x00A8
	float m_flNearBlurRadius; //0x00AC
	float m_flFarBlurRadius; //0x00B0
	int m_nDoFQuality; //0x00B4
	MotionBlurMode_t m_nMotionBlurMode; //0x00B8
	char pad_00bc[68]; //0x00BC
	int32_t m_EdgeBlur; //0x0100
}; //Size: 0x0104
static_assert(sizeof(CViewSetup) == 0x0104);

class IBaseClientDLL
{
	virtual int				Connect(void* appSystemFactory, void *pGlobals) = 0;

	virtual int				Disconnect(void) = 0;

	// run other init code here
	virtual int				Init(void* appSystemFactory, void *pGlobals) = 0;

	virtual void			PostInit() = 0;

	// Called once when the client DLL is being unloaded
	virtual void			Shutdown(void) = 0;

	// Called at the start of each level change
	virtual void			LevelInitPreEntity(char const *pMapName) = 0;
	// Called at the start of a new level, after the entities have been received and created
	virtual void			LevelInitPostEntity() = 0;

	virtual void			LevelFastReload(void) = 0;

	// Called at the end of a level
	virtual void			LevelShutdown(void) = 0;

	// Request a pointer to the list of client datatable classes
	virtual void *GetAllClasses(void) = 0;

	// Called once per level to re-initialize any hud element drawing stuff
	virtual int				HudVidInit(void) = 0;
	// Called by the engine when gathering user input
	virtual void			HudProcessInput(bool bActive) = 0;
	// Called oncer per frame to allow the hud elements to think
	virtual void			HudUpdate(bool bActive) = 0;
	// Reset the hud elements to their initial states
	virtual void			HudReset(void) = 0;
	// Display a hud text message
	virtual void			HudText(const char *message) = 0;

	// Mouse Input Interfaces
	// Activate the mouse (hides the cursor and locks it to the center of the screen)
	virtual void			IN_ActivateMouse(void) = 0;
	// Deactivates the mouse (shows the cursor and unlocks it)
	virtual void			IN_DeactivateMouse(void) = 0;
	// This is only called during extra sound updates and just accumulates mouse x, y offets and recenters the mouse.
	//  This call is used to try to prevent the mouse from appearing out of the side of a windowed version of the engine if 
	//  rendering or other processing is taking too long
	virtual void			IN_Accumulate(void) = 0;
	// Reset all key and mouse states to their initial, unpressed state
	virtual void			IN_ClearStates(void) = 0;
	// If key is found by name, returns whether it's being held down in isdown, otherwise function returns false
	virtual bool			IN_IsKeyDown(const char *name, bool &isdown) = 0;
	// Notify the client that the mouse was wheeled while in game - called prior to executing any bound commands.
	virtual void			IN_OnMouseWheeled(int nDelta) = 0;
	// Raw keyboard signal, if the client .dll returns 1, the engine processes the key as usual, otherwise,
	//  if the client .dll returns 0, the key is swallowed.
	virtual int				IN_KeyEvent(void) = 0;

	// This function is called once per tick to create the player CUserCmd (used for prediction/physics simulation of the player)
	// Because the mouse can be sampled at greater than the tick interval, there is a separate input_sample_frametime, which
	//  specifies how much additional mouse / keyboard simulation to perform.
	virtual void			CreateMove(
		int sequence_number,			// sequence_number of this cmd
		float input_sample_frametime,	// Frametime for mouse input sampling
		bool active) = 0;				// True if the player is active (not paused)

// If the game is running faster than the tick_interval framerate, then we do extra mouse sampling to avoid jittery input
//  This code path is much like the normal move creation code, except no move is created
	virtual void			ExtraMouseSample(float frametime, bool active) = 0;

	// Encode the delta (changes) between the CUserCmd in slot from vs the one in slot to.  The game code will have
	//  matching logic to read the delta.
	virtual bool			WriteUsercmdDeltaToBuffer(void) = 0;
	// Demos need to be able to encode/decode CUserCmds to memory buffers, so these functions wrap that
	virtual void			EncodeUserCmdToBuffer(void) = 0;
	virtual void			DecodeUserCmdFromBuffer(void) = 0;

	// Set up and render one or more views (e.g., rear view window, etc.).  This called into RenderView below
	virtual void			View_Render(void) = 0;

	// Allow engine to expressly render a view (e.g., during timerefresh)
	// See IVRenderView.h, PushViewFlags_t for nFlags values
	virtual void			RenderView(const CViewSetup &view, int nClearFlags, int whatToDraw) = 0;
};

class IViewRender
{
public:
	// SETUP
	// Initialize view renderer
	virtual void		Init(void) = 0;

	// Clear any systems between levels
	virtual void		LevelInit(void) = 0;
	virtual void		LevelShutdown(void) = 0;

	// Shutdown
	virtual void		Shutdown(void) = 0;

	// RENDERING
	// Called right before simulation. It must setup the view model origins and angles here so 
	// the correct attachment points can be used during simulation.	
	virtual void		OnRenderStart() = 0;

	// Called to render the entire scene
	virtual	void		Render(void) = 0;

	// Called to render just a particular setup ( for timerefresh and envmap creation )
	virtual void		RenderView(const CViewSetup &view, int nClearFlags, int whatToDraw) = 0;

	// What are we currently rendering? Returns a combination of DF_ flags.
	virtual int GetDrawFlags() = 0;

	// MISC
	// Start and stop pitch drifting logic
	virtual void		StartPitchDrift(void) = 0;
	virtual void		StopPitchDrift(void) = 0;

	// This can only be called during rendering (while within RenderView).
	virtual VPlane *GetFrustum() = 0;

	virtual bool		ShouldDrawBrushModels(void) = 0;

	virtual const CViewSetup *GetPlayerViewSetup(void) const = 0;
	virtual const CViewSetup *GetViewSetup(void) const = 0;

	virtual void		DisableVis(void) = 0;

	virtual int			BuildWorldListsNumber() const = 0;

	virtual void		SetCheapWaterStartDistance(float flCheapWaterStartDistance) = 0;
	virtual void		SetCheapWaterEndDistance(float flCheapWaterEndDistance) = 0;

	virtual void		GetWaterLODParams(float &flCheapWaterStartDistance, float &flCheapWaterEndDistance) = 0;

	virtual void		DriftPitch(void) = 0;

	virtual void		SetScreenOverlayMaterial(void) = 0;
	virtual void *GetScreenOverlayMaterial() = 0;

	virtual void		WriteSaveGameScreenshot(const char *pFilename) = 0;
	virtual void		WriteSaveGameScreenshotOfSize(const char *pFilename, int width, int height, bool bCreatePowerOf2Padded = false, bool bWriteVTF = false) = 0;

	virtual void		WriteReplayScreenshot(void) = 0;
	virtual void		UpdateReplayScreenshotCache() = 0;

	// Draws another rendering over the top of the screen
	virtual void		QueueOverlayRenderView(const CViewSetup &view, int nClearFlags, int whatToDraw) = 0;

	// Returns znear and zfar
	virtual float		GetZNear() = 0;
	virtual float		GetZFar() = 0;

	virtual void		GetScreenFadeDistances(float *min, float *max) = 0;

	virtual void *GetCurrentlyDrawingEntity() = 0;
	virtual void		SetCurrentlyDrawingEntity(void) = 0;

	virtual bool		UpdateShadowDepthTexture(void) = 0;

	virtual void		FreezeFrame(float flFreezeTime) = 0;

	virtual void *GetReplayScreenshotSystem() = 0;
};

class IClientMode
{
	// Misc.
	public:

		virtual			~IClientMode() {}

		// Called before the HUD is initialized.
		virtual void	InitViewport() = 0;

		// One time init when .dll is first loaded.
		virtual void	Init() = 0;

		// Called when vgui is shutting down.
		virtual void	VGui_Shutdown() = 0;

		// One time call when dll is shutting down
		virtual void	Shutdown() = 0;

		// Called when switching from one IClientMode to another.
		// This can re-layout the view and such.
		// Note that Enable and Disable are called when the DLL initializes and shuts down.
		virtual void	Enable() = 0;

		// Called when it's about to go into another client mode.
		virtual void	Disable() = 0;

		// Called when initializing or when the view changes.
		// This should move the viewport into the correct position.
		virtual void	Layout() = 0;

		// Gets at the viewport, if there is one...
		virtual void *GetViewport() = 0;

		// Gets at the viewports vgui panel animation controller, if there is one...
		virtual void *GetViewportAnimationController() = 0;

		// called every time shared client dll/engine data gets changed,
		// and gives the cdll a chance to modify the data.
		virtual void	ProcessInput(bool bActive) = 0;

		// The mode can choose to draw/not draw entities.
		virtual bool	ShouldDrawDetailObjects() = 0;
		virtual bool	ShouldDrawEntity(void *pEnt) = 0;
		virtual bool	ShouldDrawLocalPlayer(void *pPlayer) = 0;
		virtual bool	ShouldDrawParticles() = 0;

		// The mode can choose to not draw fog
		virtual bool	ShouldDrawFog(void) = 0;

		virtual void	OverrideView(void *pSetup) = 0;
		virtual int		KeyInput(int down, int keynum, const char *pszCurrentBinding) = 0;
		virtual void	StartMessageMode(int iMessageModeType) = 0;
		virtual void *GetMessagePanel() = 0;
		virtual void	OverrideMouseInput(float *x, float *y) = 0;
		virtual bool	CreateMove(float flInputSampleTime, void *cmd) = 0;

		virtual void	LevelInit(const char *newmap) = 0;
		virtual void	LevelShutdown(void) = 0;

		// Certain modes hide the view model
		virtual bool	ShouldDrawViewModel(void) = 0;
		virtual bool	ShouldDrawCrosshair(void) = 0;

		// Let mode override viewport for engine
		virtual void	AdjustEngineViewport(int &x, int &y, int &width, int &height) = 0;

		// Called before rendering a view.
		virtual void	PreRender(void *pSetup) = 0;

		// Called after everything is rendered.
		virtual void	PostRender(void) = 0;

		virtual void	PostRenderVGui() = 0;

		virtual void	ActivateInGameVGuiContext(void *pPanel) = 0;
		virtual void	DeactivateInGameVGuiContext() = 0;
		virtual float	GetViewModelFOV(void) = 0;

		virtual bool	CanRecordDemo(char *errorMsg, int length) const = 0;

		virtual void	ComputeVguiResConditions(void *pkvConditions) = 0;

		//=============================================================================
		// HPE_BEGIN:
		// [menglish] Save server information shown to the client in a persistent place
		//=============================================================================

		virtual wchar_t *GetServerName() = 0;
		virtual void SetServerName(wchar_t *name) = 0;
		virtual wchar_t *GetMapName() = 0;
		virtual void SetMapName(wchar_t *name) = 0;

		//=============================================================================
		// HPE_END
		//=============================================================================

		virtual bool	DoPostScreenSpaceEffects(const void *pSetup) = 0;

		virtual void	DisplayReplayMessage(const char *pLocalizeName, float flDuration, bool bUrgent,
											  const char *pSound, bool bDlg) = 0;

		// Updates.
		public:

			// Called every frame.
			virtual void	Update() = 0;

			// Returns true if VR mode should black out everything around the UI
			virtual bool	ShouldBlackoutAroundHUD() = 0;

			// Returns true if VR mode should black out everything around the UI
			virtual int ShouldOverrideHeadtrackControl() = 0;

			virtual bool	IsInfoPanelAllowed() = 0;
			virtual void	InfoPanelDisplayed() = 0;
			virtual bool	IsHTMLInfoPanelAllowed() = 0;
};

#define  AssertMsg( _exp, _msg, ... )						((void)0)

template <class T>
class CBaseAutoPtr
{
public:
	CBaseAutoPtr() : m_pObject(0) {}
	CBaseAutoPtr(T *pFrom) : m_pObject(pFrom) {}

	operator const void *() const { return m_pObject; }
	operator void *() { return m_pObject; }

	operator const T *() const { return m_pObject; }
	operator const T *() { return m_pObject; }
	operator T *() { return m_pObject; }

	int			operator=(int i) { AssertMsg(i == 0, "Only NULL allowed on integer assign"); m_pObject = 0; return 0; }
	T *operator=(T *p) { m_pObject = p; return p; }

	bool        operator !() const { return (!m_pObject); }
	bool        operator!=(int i) const { AssertMsg(i == 0, "Only NULL allowed on integer compare"); return (m_pObject != NULL); }
	bool		operator==(const void *p) const { return (m_pObject == p); }
	bool		operator!=(const void *p) const { return (m_pObject != p); }
	bool		operator==(T *p) const { return operator==((void *)p); }
	bool		operator!=(T *p) const { return operator!=((void *)p); }
	bool		operator==(const CBaseAutoPtr<T> &p) const { return operator==((const void *)p); }
	bool		operator!=(const CBaseAutoPtr<T> &p) const { return operator!=((const void *)p); }

	T *operator->() { return m_pObject; }
	T &operator *() { return *m_pObject; }
	T **operator &() { return &m_pObject; }

	const T *operator->() const { return m_pObject; }
	const T &operator *() const { return *m_pObject; }
	T *const *operator &() const { return &m_pObject; }

protected:
	CBaseAutoPtr(const CBaseAutoPtr<T> &from) : m_pObject(from.m_pObject) {}
	void operator=(const CBaseAutoPtr<T> &from) { m_pObject = from.m_pObject; }

	T *m_pObject;
};

template <class T>
class CRefPtr : public CBaseAutoPtr<T>
{
	typedef CBaseAutoPtr<T> BaseClass;
public:
	CRefPtr() {}
	CRefPtr(T *pInit) : BaseClass(pInit) {}
	CRefPtr(const CRefPtr<T> &from) : BaseClass(from) {}
	~CRefPtr() { if (BaseClass::m_pObject) BaseClass::m_pObject->Release(); }

	void operator=(const CRefPtr<T> &from) { BaseClass::operator=(from); }

	int operator=(int i) { return BaseClass::operator=(i); }
	T *operator=(T *p) { return BaseClass::operator=(p); }

	operator bool() const { return !BaseClass::operator!(); }
	operator bool() { return !BaseClass::operator!(); }

	void SafeRelease() { if (BaseClass::m_pObject) BaseClass::m_pObject->Release(); BaseClass::m_pObject = 0; }
	void AssignAddRef(T *pFrom) { SafeRelease(); if (pFrom) pFrom->AddRef(); BaseClass::m_pObject = pFrom; }
	void AddRefAssignTo(T *&pTo) { ::SafeRelease(pTo); if (BaseClass::m_pObject) BaseClass::m_pObject->AddRef(); pTo = BaseClass::m_pObject; }
};

class IMaterial
{
public:
	virtual const char *GetName() const = 0;
	virtual const char *GetTextureGroupName() const = 0;
	virtual void * GetPreviewImageProperties(int *width, int *height, ImageFormat *imageFormat, bool *isTranslucent) const = 0;
	virtual void* GetPreviewImage(unsigned char *data, int width, int height, ImageFormat imageFormat) const = 0;
	virtual int				GetMappingWidth() = 0;
	virtual int				GetMappingHeight() = 0;
	virtual int				GetNumAnimationFrames() = 0;
	virtual bool			InMaterialPage(void) = 0;
	virtual	void			GetMaterialOffset(float *pOffset) = 0;
	virtual void			GetMaterialScale(float *pScale) = 0;
	virtual IMaterial *GetMaterialPage(void) = 0;
	virtual void *FindVar(const char *varName, bool *found, bool complain = true) = 0;
	virtual void			IncrementReferenceCount(void) = 0;
	virtual void			DecrementReferenceCount(void) = 0;
	virtual int 			GetEnumerationID(void) const = 0;
	virtual void			GetLowResColorSample(float s, float t, float *color) const = 0;
	virtual void			RecomputeStateSnapshots() = 0;
	virtual bool			IsTranslucent() = 0;
	virtual bool			IsAlphaTested() = 0;
	virtual bool			IsVertexLit() = 0;
	virtual void *GetVertexFormat() const = 0;
	virtual bool			HasProxy(void) const = 0;
	virtual bool			UsesEnvCubemap(void) = 0;
	virtual bool			NeedsTangentSpace(void) = 0;
	virtual bool			NeedsPowerOfTwoFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool			NeedsFullFrameBufferTexture(bool bCheckSpecificToThisFrame = true) = 0;
	virtual bool			NeedsSoftwareSkinning(void) = 0;
	virtual void			AlphaModulate(float alpha) = 0;
	virtual void			ColorModulate(float r, float g, float b) = 0;
	virtual void			SetMaterialVarFlag(MaterialVarFlags_t flag, bool on) = 0;
	virtual bool			GetMaterialVarFlag(void) const = 0;

	// Gets material reflectivity
	virtual void			GetReflectivity(Vector &reflect) = 0;

	// Gets material property flags
	virtual bool			GetPropertyFlag(void) = 0;

	// Is the material visible from both sides?
	virtual bool			IsTwoSided() = 0;

	// Sets the shader associated with the material
	virtual void			SetShader(const char *pShaderName) = 0;

	// Can't be const because the material might have to precache itself.
	virtual int				GetNumPasses(void) = 0;

	// Can't be const because the material might have to precache itself.
	virtual int				GetTextureMemoryBytes(void) = 0;

	// Meant to be used with materials created using CreateMaterial
	// It updates the materials to reflect the current values stored in the material vars
	virtual void			Refresh() = 0;

	// GR - returns true is material uses lightmap alpha for blending
	virtual bool			NeedsLightmapBlendAlpha(void) = 0;

	// returns true if the shader doesn't do lighting itself and requires
	// the data that is sent to it to be prelighted
	virtual bool			NeedsSoftwareLighting(void) = 0;

	// Gets at the shader parameters
	virtual int				ShaderParamCount() const = 0;
	virtual void **GetShaderParams(void) = 0;

	// Returns true if this is the error material you get back from IMaterialSystem::FindMaterial if
	// the material can't be found.
	virtual bool			IsErrorMaterial() const = 0;

	virtual void			SetUseFixedFunctionBakedLighting(bool bEnable) = 0;

	// Gets the current alpha modulation
	virtual float			GetAlphaModulation() = 0;
	virtual void			GetColorModulation(float *r, float *g, float *b) = 0;

	// Gets the morph format
	virtual void	GetMorphFormat() const = 0;

	// fast find that stores the index of the found var in the string table in local cache
	virtual void *FindVarFast(char const *pVarName, unsigned int *pToken) = 0;

	// Sets new VMT shader parameters for the material
	virtual void			SetShaderAndParams(void) = 0;
	virtual const char *GetShaderName() const = 0;

	virtual void			DeleteIfUnreferenced() = 0;

	virtual bool			IsSpriteCard() = 0;

	virtual void			CallBindProxy(void *proxyData) = 0;

	virtual IMaterial *CheckProxyReplacement(void *proxyData) = 0;

	virtual void			RefreshPreservingMaterialVars() = 0;

	virtual bool			WasReloadedFromWhitelist() = 0;

	virtual bool			IsPrecached() const = 0;
};

enum OverrideType_t
{
	OVERRIDE_NORMAL = 0,
	OVERRIDE_BUILD_SHADOWS,
	OVERRIDE_DEPTH_WRITE,
	OVERRIDE_SSAO_DEPTH_WRITE,
};

class IModelRender
{
public:
	virtual int		DrawModel(int flags,
								void * pRenderable,
								int instance,
								int entity_index,
								const void * model,
								Vector const &origin,
								QAngle const &angles,
								int skin,
								int body,
								int hitboxset,
								const matrix3x4_t * modelToWorld = NULL,
								const matrix3x4_t * pLightingOffset = NULL) = 0;

	// This causes a material to be used when rendering the model instead 
	// of the materials the model was compiled with
	virtual void	ForcedMaterialOverride(IMaterial *newMaterial, OverrideType_t nOverrideType = OVERRIDE_NORMAL) = 0;

};

class IRefCounted
{
public:
	virtual int AddRef() = 0;
	virtual int Release() = 0;
};

class IMatRenderContext : public IRefCounted
{
public:
	virtual void BeginRender();
	virtual void EndRender();
	virtual void Flush(bool flushHardware = false);
	virtual void BindLocalCubemap();
	virtual void SetRenderTarget(ITexture *pTexture);
	virtual ITexture *GetRenderTarget();
	virtual void GetRenderTargetDimensions(int& width, int& height) const = 0;
	virtual void Bind();
	virtual void BindLightmapPage();
	virtual void DepthRange();
	virtual void ClearBuffers(bool bClearColor, bool bClearDepth, bool bClearStencil = false);
	virtual void ReadPixels();
	virtual void SetLightingState();
	virtual void SetLights();
	virtual void SetAmbientLightCube();
	virtual void CopyRenderTargetToTexture(ITexture* pTexture);
	virtual void SetFrameBufferCopyTexture();
	virtual void GetFrameBufferCopyTexture();
	virtual void MatrixMode();
	virtual void PushMatrix();
	virtual void PopMatrix();
	virtual void sub_10028460();
	virtual void sub_10028410();
	virtual void sub_10028500();
	virtual void sub_100284B0();
	virtual void sub_100285E0();
	virtual void sub_10028590();
	virtual void sub_1002CE30();
	virtual void sub_1002CDF0();
	virtual void sub_10028670();
	virtual void sub_100286A0();
	virtual void sub_10028710();
	virtual void sub_100287F0();
	virtual void sub_10028850();
	virtual void sub_100288B0();
	virtual void sub_10028910();
	virtual void sub_100276D0();
	virtual void Viewport(int x, int y, int width, int height);
	virtual void sub_10016F00();
	virtual void sub_100173B0();
	virtual void sub_100173E0();
	virtual void sub_10027A10();
	virtual void sub_10027A40();
	virtual void sub_10027A70();
	virtual void sub_10023C90();
	virtual void sub_10023CA0();
	virtual void sub_10023D40();
	virtual void sub_10027B60();
	virtual void sub_10023DE0();
	virtual void sub_10023E10();
	virtual void sub_10027AD0();
	virtual void sub_10027B00();
	virtual void sub_10027B30();
	virtual void sub_100279E0();
	virtual void sub_10014420();
	virtual void sub_10016F30();
	virtual void sub_10023EC0();
	virtual void sub_10014450();
	virtual void sub_10014480();
	virtual void sub_100144A0();
	virtual void sub_100144C0();
	virtual void sub_100144E0();
	virtual void sub_10023EB0();
	virtual void sub_10014510();
	virtual void sub_10014550();
	virtual void sub_10014570();
	virtual void sub_10014590();
	virtual void sub_100145E0();
	virtual void sub_10016F60();
	virtual void sub_10016F80();
	virtual void sub_10016FB0();
	virtual void sub_10016FE0();
	//virtual void sub_10017000();
	virtual void ClearColor4ub(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	virtual void sub_100170E0();
	virtual void sub_100172C0();
	virtual void sub_10028DF0();
	virtual void sub_100143C0();
	virtual void sub_10027C20();
	virtual void sub_100172F0();
	virtual void sub_10017320();
	virtual void sub_10017350();
	virtual void sub_10027C60();
	virtual void sub_10017C70();
	virtual void sub_10027CA0();
	virtual void sub_10014400();
	virtual void sub_1002AC30();
	virtual void sub_10017420();
	virtual void sub_10027D40();
	virtual void sub_100148D0();
	virtual void sub_10017380();
	virtual void sub_10014630();
	virtual void sub_10017450();
	virtual void sub_10017480();
	virtual void nullsub_22();
	virtual void sub_1002B990();
	virtual void sub_1002B990_1();
	virtual void sub_1002B990_2();
	virtual void UnlockRenderData();
	virtual void sub_100290F0();
	virtual void sub_10029100();
	virtual void sub_1002A400();
	virtual void sub_10024150();
	virtual void GetWindowSize(int &, int &);
	virtual void DrawScreenSpaceRectangle() = 0;
	virtual void sub_10027EA0() = 0;
	virtual void PushRenderTargetAndViewport() = 0;
	virtual void PushRenderTargetAndViewport(ITexture*) = 0;
	virtual void PushRenderTargetAndViewport(ITexture*, int, int, int, int) = 0;
	virtual void PushRenderTargetAndViewport(ITexture*, ITexture*, int, int, int, int) = 0;
	virtual void PopRenderTargetAndViewport() = 0;
	virtual void sub_10017610() = 0;
	virtual void CopyRenderTargetToTextureEx(ITexture*, int, Rect_t*, Rect_t*) = 0;
	virtual void sub_10028030() = 0;
	virtual void sub_10028770() = 0;
	virtual void sub_10017640() = 0;
	virtual void sub_100176E0() = 0;
	virtual void sub_10017820() = 0;
	virtual void sub_10017870() = 0;
	virtual void sub_100178B0() = 0;
	virtual void sub_10027620() = 0;
	virtual void sub_100179A0() = 0;
	virtual void sub_10017A20() = 0;
	virtual void sub_10023F80() = 0;
	virtual void sub_10023EF0() = 0;
	virtual void sub_10023F70() = 0;
	virtual void sub_10017A40() = 0;
	virtual void sub_10014770() = 0;
	virtual void sub_10025190() = 0;
	virtual void sub_10017A60() = 0;
	virtual void sub_10014870() = 0;
	virtual void sub_10017B10() = 0;
	virtual void sub_10027D00() = 0;
	virtual void sub_10023E40() = 0;
	virtual void sub_10023E80() = 0;
	virtual void sub_100192A0() = 0;
	virtual void sub_10017CB0() = 0;
	virtual void sub_10019310() = 0;
	virtual void sub_10028970() = 0;
	virtual void sub_100289A0() = 0;
	virtual void sub_10028A40() = 0;
	virtual void sub_10028AE0() = 0;
	virtual void sub_10023C70() = 0;
	virtual void sub_1002AB00() = 0;
	virtual void sub_1002AB30() = 0;
	virtual void sub_10017F60() = 0;
	virtual void sub_10014B10() = 0;
	virtual void sub_100178F0() = 0;
	virtual void sub_10017C50() = 0;
	virtual void sub_10027940() = 0;
	virtual void sub_10017AD0() = 0;
	virtual void sub_10017D30() = 0;
	virtual void sub_10017D50() = 0;
	virtual void nullsub_23() = 0;
	virtual void sub_100147C0() = 0;
	virtual void sub_10014810() = 0;
	virtual void sub_10014860() = 0;
	virtual void sub_10015060() = 0;
	virtual void sub_100250F0() = 0;
	virtual void sub_10027AA0() = 0;
	virtual void sub_10014350() = 0;
	virtual void sub_10023C80() = 0;
	virtual void sub_10014360() = 0;
	virtual void sub_10017DA0() = 0;
	virtual void sub_10024560() = 0;
	virtual void sub_100245B0() = 0;
	virtual void sub_10024600() = 0;
	virtual void sub_10024650() = 0;
	virtual void sub_100246A0() = 0;
	virtual void sub_10017DF0() = 0;
	virtual void sub_10017DD0() = 0;
	virtual void sub_10017E90() = 0;
	virtual void sub_10017F30() = 0;
	virtual void sub_10017FD0() = 0;
	virtual void sub_10018090() = 0;
	virtual void sub_10018130() = 0;
	virtual void sub_10014B40() = 0;
	virtual void sub_10017780() = 0;
	virtual void sub_10018180() = 0;
	virtual void sub_10028B00() = 0;
	virtual void sub_10028B00_1() = 0;
	virtual void sub_10028B00_2() = 0;
	virtual void sub_10028B00_3() = 0;
	virtual void sub_10028B00_4() = 0;
	virtual void OverrideAlphaWriteEnable(bool bEnable, bool bAlphaWriteEnable) = 0;
};

class CMatRenderContextPtr : public CRefPtr<IMatRenderContext>
{
	typedef CRefPtr<IMatRenderContext> BaseClass;
public:
	CMatRenderContextPtr() {}
	CMatRenderContextPtr(IMatRenderContext *pInit) : BaseClass(pInit) { if (BaseClass::m_pObject) BaseClass::m_pObject->BeginRender(); }
	CMatRenderContextPtr(IMaterialSystem *pFrom) : BaseClass(pFrom->GetRenderContext()) { if (BaseClass::m_pObject) BaseClass::m_pObject->BeginRender(); }
	~CMatRenderContextPtr() { if (BaseClass::m_pObject) BaseClass::m_pObject->EndRender(); }

	IMatRenderContext *operator=(IMatRenderContext *p) { if (p) p->BeginRender(); return BaseClass::operator=(p); }

	void SafeRelease() { if (BaseClass::m_pObject) BaseClass::m_pObject->EndRender(); BaseClass::SafeRelease(); }
	void AssignAddRef(IMatRenderContext *pFrom) { if (BaseClass::m_pObject) BaseClass::m_pObject->EndRender(); BaseClass::AssignAddRef(pFrom); BaseClass::m_pObject->BeginRender(); }

	void GetFrom(IMaterialSystem *pFrom) { AssignAddRef(pFrom->GetRenderContext()); }


private:
	CMatRenderContextPtr(const CMatRenderContextPtr &from);
	void operator=(const CMatRenderContextPtr &from);

};

class CMeleeWeaponInfoStore
{
public:
	char pad_0000[3236]; //0x0000
	char meleeWeaponName[256]; //0x0CA4
	char pad_0DA4[920]; //0x0DA4
}; //Size: 0x113C
static_assert(sizeof(CMeleeWeaponInfoStore) == 0x113C);

class IHandleEntity
{
public:
	virtual ~IHandleEntity() {}
	virtual void SetRefEHandle(int handle) = 0;
	virtual void GetRefEHandle() const = 0;
};

class IServerUnknown : public IHandleEntity
{
public:
	// Gets the interface to the collideable + networkable representation of the entity
	virtual void *GetCollideable() = 0;
	virtual void *GetNetworkable() = 0;
	virtual void *GetBaseEntity() = 0;
};

class IClientUnknown : public IHandleEntity
{
public:
	virtual void *GetCollideable() = 0;
	virtual void *GetClientNetworkable() = 0;
	virtual void *GetClientRenderable() = 0;
	virtual void *GetIClientEntity() = 0;
	virtual void *GetBaseEntity() = 0;
	virtual void *GetClientThinkable() = 0;
	virtual void *GetClientModelRenderable() = 0;
	virtual void *GetClientAlphaProperty() = 0;
};

class IClientEntity : public IClientUnknown
{
	virtual Vector &GetAbsOrigin() = 0;
	virtual QAngle &GetAbsAngles() = 0;
	virtual void *GetMouth() = 0;
	virtual bool GetSoundSpatialization() = 0;
	virtual bool IsBlurred() = 0;
};

class C_BaseEntity : public IClientEntity
{
public:
	virtual ~C_BaseEntity() = 0;
	virtual void *GetDataDescMap() = 0;
	virtual void *YouForgotToImplementOrDeclareClientClass() = 0;
	virtual void *GetPredDescMap() = 0;
	virtual void *FireBullets() = 0;
	virtual void *sub_1001A1E0() = 0;
	virtual void *sub_100194A0() = 0;
	virtual void *sub_1001B830() = 0;
	virtual void *sub_1001A1F0() = 0;
	virtual void *sub_1001A200() = 0;
	virtual void *TraceAttack() = 0;
	virtual void *sub_1001A210() = 0;
	virtual void *sub_1001A230() = 0;
	virtual void *sub_1001A2D0() = 0;
	virtual void *sub_1001A2F0() = 0;
	virtual void *sub_1001A300() = 0;
	virtual void *nullsub_7() = 0;
	virtual void *nullsub_170() = 0;
	virtual void *nullsub_70() = 0;
	virtual void *nullsub_171() = 0;
	virtual void *nullsub_172() = 0;
	virtual void *sub_1001A010() = 0;
	virtual void *sub_10019FA0() = 0;
	virtual void *KeyValue() = 0;
	virtual void *GetKeyValue () = 0;
	virtual void *nullsub_173() = 0;
	virtual void *sub_100487C0() = 0;
	virtual void *loc_1001EA50() = 0;
	virtual void *fn0() = 0;
	virtual void *sub_1004CBC0() = 0;
	virtual void *sub_10019530() = 0;
	virtual void *sub_10042370() = 0;
	virtual void *sub_10042380() = 0;
	virtual void *sub_10043470() = 0;
	virtual void *sub_100430D0() = 0;
	virtual void *sub_1004CD20() = 0;
	virtual void *sub_10049060() = 0;
	virtual void *nullsub_174() = 0;
	virtual void *fn1() = 0;
	virtual void *sub_100427B0() = 0;
	virtual void *sub_10043280() = 0;
	virtual void *sub_100474F0() = 0;
	virtual void *OnRestore() = 0;
	virtual void *sub_100432A0() = 0;
	virtual void *sub_10019950() = 0;
	virtual void *sub_10044FE0() = 0;
	virtual void *sub_10047500() = 0;
	virtual void *sub_1001A150() = 0;
	virtual void *sub_1001A120() = 0;
	virtual void *sub_1001DA90() = 0;
	virtual void *sub_10043E80() = 0;
	virtual void *sub_100421C0() = 0;
	virtual void *sub_100495A0() = 0;
	virtual void *sub_100495E0() = 0;
	virtual void *sub_10019830() = 0;
	virtual void *sub_10019850() = 0;
	virtual void *sub_1001BEE0() = 0;
	virtual void *nullsub_175() = 0;
	virtual void *sub_10019810() = 0;
	virtual void *sub_100197F0() = 0;
	virtual void *sub_100425D0() = 0;
	virtual void *sub_10048AF0() = 0;
	virtual void *locret_1001EA80() = 0;
	virtual void *sub_10042B10() = 0;
	virtual void *fn2() = 0;
	virtual void *fn3() = 0;
	virtual void *sub_10042B30() = 0;
	virtual void *sub_10042B40() = 0;
	virtual void *sub_10042B80() = 0;
	virtual void *sub_100195B0() = 0;
	virtual void *sub_100195C0() = 0;
	virtual void *sub_100195D0() = 0;
	virtual void *sub_100195E0() = 0;
	virtual void *sub_100195F0() = 0;
	virtual void *sub_10019600() = 0;
	virtual void *sub_100420C0() = 0;
	virtual void *sub_100445A0() = 0;
	virtual void *sub_1004D170() = 0;
	virtual void *loc_1001EA90() = 0;
	virtual void *sub_10019610() = 0;
	virtual void *sub_100428C0() = 0;
	virtual void *sub_10042780() = 0;
	virtual void *sub_10042520() = 0;
	virtual void *sub_100475B0() = 0;
	virtual void *nullsub_13() = 0;
	virtual void *sub_100465F0() = 0;
	virtual void *sub_10042790() = 0;
	virtual void *sub_1004ED10() = 0;
	virtual void *sub_10044690() = 0;
	virtual void *nullsub_9() = 0;
	virtual void *nullsub_10() = 0;
	virtual void *sub_10047260() = 0;
	virtual void *sub_1004DDB0() = 0;
	virtual void *sub_10042880() = 0;
	virtual void *sub_10044700() = 0;
	virtual void *sub_1004B620() = 0;
	virtual void *sub_10042620() = 0;
	virtual void *sub_10042910() = 0;
	virtual void *nullsub_176() = 0;
	virtual void *sub_10044A50() = 0;
	virtual void *nullsub_177() = 0;
	virtual void *sub_10019650() = 0;
	virtual void *sub_10019660() = 0;
	virtual void *sub_10019670() = 0;
	virtual void *sub_100467C0() = 0;
	virtual void *sub_10043070() = 0;
	virtual void *sub_1004C1C0() = 0;
	virtual void *sub_100471C0() = 0;
	virtual void *sub_100461B0() = 0;
	virtual void *sub_1004E2D0() = 0;
	virtual void *sub_100491E0() = 0;
	virtual void *sub_1001A0D0() = 0;
	virtual void *sub_1001A8D0() = 0;
	virtual void *sub_1001A950() = 0;
	virtual void *sub_10019680() = 0;
	virtual void *sub_10019690() = 0;
	virtual void *sub_10043420() = 0;
	virtual void *sub_100196B0() = 0;
	virtual void *sub_1004C230() = 0;
	virtual void *sub_100196C0() = 0;
	virtual void *sub_100196D0() = 0;
	virtual void *sub_101653F0() = 0;
	virtual void *nullsub_22() = 0;
	virtual void *sub_10164EC0() = 0;
	virtual void *nullsub_178() = 0;
	virtual void *sub_10165410() = 0;
	virtual void *nullsub_179() = 0;
	virtual void *sub_101686F0() = 0;
	virtual void *IsPlayer() = 0;
	virtual void *sub_10019700() = 0;
	virtual void *sub_10019710() = 0;
	virtual void *sub_10019720() = 0;
	virtual void *MyInfectedRagdollPointer() = 0;
	virtual void *IsNPC() = 0;
	virtual void *sub_10019750() = 0;
	virtual void *sub_10019760() = 0;
	virtual void *sub_1001E000() = 0;
	virtual void *sub_1001E010() = 0;
	virtual void *sub_10019770() = 0;
	virtual void *sub_10019780() = 0;
	virtual Vector EyePosition() = 0;
	virtual Vector *EyeAngles() = 0;
	virtual Vector *LocalEyeAngles() = 0;
	virtual void *sub_10019E10() = 0;
	virtual void *sub_1001A090() = 0;
	virtual void *sub_10019870() = 0;
	virtual const Vector& GetViewOffset() = 0;
	virtual void *SetViewOffset() = 0;
	virtual void *GetGroundVelocityToApply() = 0;
	virtual void *ShouldInterpolate() = 0;
	virtual void *BoneMergeFastCullBloat() = 0;
	virtual void *sub_10043080() = 0;
	virtual void *GetShadowUseOtherEntity() = 0;
	virtual void *SetShadowUseOtherEntity() = 0;
	virtual void *sub_100197E0() = 0;
	virtual void *loc_1001EAC0() = 0;
	virtual void *nullsub_180() = 0;
};

class C_BaseAnimating : public C_BaseEntity
{
public:
	virtual ~C_BaseAnimating() = 0;
	virtual void *GetBoneControllers() = 0;
	virtual void *SetBoneController() = 0;
	virtual void *GetPoseParameters() = 0;
	virtual void *sub_10039850() = 0;
	virtual void *sub_1002F430() = 0;
	virtual void *sub_100334A0() = 0;
	virtual void *sub_10033550() = 0;
	virtual void *sub_10030150() = 0;
	virtual void *sub_1002FD00() = 0;
	virtual void *sub_1002BEA0() = 0;
	virtual void *sub_10033F70() = 0;
	virtual void *sub_10034280() = 0;
	virtual void *sub_10038770() = 0;
	virtual void *sub_1002DD30() = 0;
	virtual void *DispatchMuzzleEffect() = 0;
	virtual void *sub_1003A3C0() = 0;
	virtual void *sub_1003C050() = 0;
	virtual void *sub_1003BDF0() = 0;
	virtual void *nullsub_5() = 0;
	virtual void *nullsub_79() = 0;
	virtual void *sub_1003AD80() = 0;
	virtual void *sub_1003CF70() = 0;
	virtual void *sub_1002BFE0() = 0;
	virtual void *sub_1002F590() = 0;
	virtual void *sub_1002B8D0() = 0;
	virtual void *GetRagdollInitBoneArrays() = 0;
	virtual void *sub_100345B0() = 0;
	virtual void *sub_100346C0() = 0;
	virtual void *sub_100314E0() = 0;
	virtual void *sub_1002C000() = 0;
	virtual void *sub_1002E740() = 0;
	virtual void *sub_1002BFF0() = 0;
	virtual void *nullsub_181() = 0;
	virtual void *sub_100198D0() = 0;
	virtual void *nullsub_182() = 0;
	virtual void *sub_1002C400() = 0;
	virtual void *ProcessMuzzleFlashEvent() = 0;
	virtual void *nullsub_183() = 0;
	virtual void *sub_10019900() = 0;
	virtual void *sub_1002C7B0() = 0;
	virtual void *sub_1002BAB0() = 0;
	virtual void *sub_10019910() = 0;
	virtual void *nullsub_184() = 0;
	virtual void *sub_1002BAC0() = 0;
	virtual void *sub_1002B9B0() = 0;
	virtual void *ComputeStencilState() = 0;
	virtual void *LastBoneChangedTime() = 0;
};

class C_BaseAnimatingOverlay : public C_BaseAnimating
{
public:
	virtual ~C_BaseAnimatingOverlay() = 0;
};

class C_BaseFlex : public C_BaseAnimatingOverlay
{
public:
	virtual ~C_BaseFlex() = 0;
	virtual void *sub_1004F2E0() = 0;
	virtual void *sub_1001E020() = 0;
	virtual void *sub_1001E030() = 0;
	virtual void *sub_1004F430() = 0;
	virtual void *sub_1004F1F0() = 0;
	virtual void *sub_1004F170() = 0;
	virtual void *sub_1004F1C0() = 0;
};

class C_BaseCombatCharacter : public C_BaseFlex
{
public:
	virtual ~C_BaseCombatCharacter() = 0;
	virtual void *sub_10012380() = 0;
	virtual void *sub_100122E0() = 0;
	virtual void *sub_10012620() = 0;
	virtual void *sub_10012430() = 0;
	virtual void *sub_10012DE0() = 0;
	virtual void *sub_10011DC0() = 0;
	virtual void *nullsub_205() = 0;
	virtual void *sub_10012EB0() = 0;
	virtual void *sub_1001E070() = 0;
	virtual void *sub_1001E080() = 0;
	virtual void *sub_1001E090() = 0;
	virtual void *GetFootstepRunThreshold() = 0;
	virtual void *GetClass() = 0;
	virtual void *sub_1001E0C0() = 0;
	virtual void* Weapon_GetSlot(int i) = 0;
	virtual void *sub_1001E0A0() = 0;
	virtual void *sub_10040B90() = 0;
	virtual C_BaseCombatWeapon *GetActiveWeapon() = 0;
};



class C_BaseCombatWeapon : public C_BaseAnimating
{
public:
	virtual ~C_BaseCombatWeapon() = 0;
	virtual void *sub_10019980() = 0;
	virtual void *sub_10019990() = 0;
	virtual void *sub_100199A0() = 0;
	virtual void Equip(void *pOwner) = 0;
	virtual void *nullsub_45() = 0;
	virtual void *sub_10017850() = 0;
	virtual void *sub_100155A0() = 0;
	virtual void *sub_100155B0() = 0;
	virtual void *sub_100155D0() = 0;
	virtual void *sub_100160D0() = 0;
	virtual void *nullsub_185() = 0;
	virtual void *nullsub_4() = 0;
	virtual void *sub_10016350() = 0;
	virtual void *nullsub_186() = 0;
	virtual void *nullsub_187() = 0;
	virtual void *sub_100163A0() = 0;
	virtual void *nullsub_188() = 0;
	virtual void *nullsub_189() = 0;
	virtual void *sub_10017890() = 0;
	virtual void *sub_100170D0() = 0;
	virtual void *sub_10016500() = 0;
	virtual void *sub_100199B0() = 0;
	virtual void *sub_100165D0() = 0;
	virtual void *sub_10015E60() = 0;
	virtual void *sub_100176C0() = 0;
	virtual void *sub_10015E80() = 0;
	virtual void *sub_10016680() = 0;
	virtual void *sub_100166D0() = 0;
	virtual void *sub_10016750() = 0;
	virtual void *sub_100199C0() = 0;
	virtual void *sub_10018970() = 0;
	virtual void *sub_100199D0() = 0;
	virtual void *sub_10015EA0() = 0;
	virtual void *sub_10018BC0() = 0;
	virtual void *sub_100199E0() = 0;
	virtual void *sub_100167D0() = 0;
	virtual void *sub_10016860() = 0;
	virtual void *sub_100178B0() = 0;
	virtual void *sub_10015660() = 0;
	virtual void *sub_100170E0() = 0;
	virtual void *sub_10017A40() = 0;
	virtual void *sub_10017E40() = 0;
	virtual void *nullsub_190() = 0;
	virtual void *sub_100157E0() = 0;
	virtual void *sub_100156D0() = 0;
	virtual void *nullsub_191() = 0;
	virtual void *sub_10019A10() = 0;
	virtual void *sub_10018160() = 0;
	virtual void *sub_10018380() = 0;
	virtual void *sub_100184F0() = 0;
	virtual void *sub_10018120() = 0;
	virtual void *sub_10018520() = 0;
	virtual void *nullsub_192() = 0;
	virtual void *sub_10016E80() = 0;
	virtual void *sub_10018DD0() = 0;
	virtual void *sub_10015810() = 0;
	virtual void *sub_10015820() = 0;
	virtual void *sub_10015670() = 0;
	virtual void *sub_100157D0() = 0;
	virtual void *sub_10019A30() = 0;
	virtual void *sub_10015740() = 0;
	virtual void *sub_10019A40() = 0;
	virtual void *sub_10015750() = 0;
	virtual void *sub_10019A70() = 0;
	virtual void *sub_100157A0() = 0;
	virtual void *sub_10019A80() = 0;
	virtual void *sub_10019A90() = 0;
	virtual void *sub_10019AA0() = 0;
	virtual void *sub_10019AB0() = 0;
	virtual void *sub_10019AC0() = 0;
	virtual void *sub_100169B0() = 0;
	virtual void *sub_10016B70() = 0;
	virtual void *sub_10015790() = 0;
	virtual void *sub_10019B00() = 0;
	virtual void *sub_10019B10() = 0;
	virtual void *sub_10019B20() = 0;
	virtual void *sub_10019B30() = 0;
	virtual void *sub_10019B40() = 0;
	virtual void *sub_10016450() = 0;
	virtual void *nullsub_193() = 0;
	virtual void *sub_10015840() = 0;
	virtual void *nullsub_194() = 0;
	virtual void *nullsub_195() = 0;
	virtual void *sub_10019B60() = 0;
	virtual void *sub_10015850() = 0;
	virtual void *sub_10015860() = 0;
	virtual void *sub_10019B70() = 0;
	virtual void *sub_10019B80() = 0;
	virtual void *sub_10019B90() = 0;
	virtual void *sub_100151C0() = 0;
	virtual void *sub_100151E0() = 0;
	virtual void *sub_10015200() = 0;
	virtual void *sub_10015240() = 0;
	virtual void *sub_10015260() = 0;
	virtual void *sub_10015280() = 0;
	virtual void *sub_100152A0() = 0;
	virtual void *sub_10015310() = 0;
	virtual void *sub_10015330() = 0;
	virtual void *sub_10015350() = 0;
	virtual void *sub_10015370() = 0;
	virtual int GetSlot() = 0;
	virtual int GetPosition() = 0;
	virtual char *GetName() = 0;
	virtual char *GetPrintName() = 0;
	virtual char *GetShootSound(int index) = 0;
	virtual void *sub_10015580() = 0;
	virtual void *sub_100152C0() = 0;
	virtual void *sub_100152F0() = 0;
	virtual void *sub_100152E0() = 0;
	virtual void *nullsub_196() = 0;
	virtual void *sub_10015190() = 0;
	virtual void *sub_10019CD0() = 0;
	virtual void *sub_10019CE0() = 0;
	virtual void *sub_100153F0() = 0;
	virtual void *sub_10015410() = 0;
	virtual void *sub_10015430() = 0;
	virtual void *sub_10015450() = 0;
	virtual void *sub_10015470() = 0;
	virtual void *sub_100154D0() = 0;
	virtual void *sub_100154F0() = 0;
	virtual void *sub_10015510() = 0;
	virtual void *sub_10015530() = 0;
	virtual void *sub_10015490() = 0;
	virtual void *sub_100154B0() = 0;
	virtual void *sub_10015870() = 0;
	virtual void *sub_10019BB0() = 0;
	virtual void *sub_10019BC0() = 0;
	virtual void *sub_100157B0() = 0;
	virtual void *sub_100157C0() = 0;
	virtual void *sub_10019BD0() = 0;
	virtual void *sub_10040C60() = 0;
	virtual void *nullsub_197() = 0;
	virtual void *sub_10040E80() = 0;
	virtual void *sub_10019BE0() = 0;
	virtual void *sub_10040CA0() = 0;
	virtual void *sub_10040FF0() = 0;
	virtual void *sub_10040CF0() = 0;
	virtual void *nullsub_198() = 0;
	virtual void *nullsub_199() = 0;
	virtual void *nullsub_200() = 0;
	virtual void *fn0() = 0;
	virtual void *sub_10019C30() = 0;
	virtual void *nullsub_201() = 0;
	virtual void *sub_10040E70() = 0;
	virtual void *sub_10041020() = 0;
	virtual void *nullsub_202() = 0;
	virtual void *sub_10019C60() = 0;
	virtual void *sub_10019C70() = 0;
	virtual void *sub_10019C80() = 0;
	virtual void HideThink() = 0;
	virtual void *nullsub_203() = 0;
	virtual void *nullsub_204() = 0;
};

class C_WeaponCSBase : public C_BaseCombatWeapon
{
public:
	enum WeaponID
	{
		NONE,
		PISTOL,
		UZI,
		PUMPSHOTGUN,
		AUTOSHOTGUN,
		M16A1,
		HUNTING_RIFLE,
		MAC10,
		SHOTGUN_CHROME,
		SCAR,
		SNIPER_MILITARY,
		SPAS,
		FIRST_AID_KIT,
		MOLOTOV,
		PIPE_BOMB,
		PAIN_PILLS,
		GASCAN,
		PROPANE_TANK,
		OXYGEN_TANK,
		MELEE,
		CHAINSAW,
		GRENADE_LAUNCHER,
		AMMO_PACK,
		ADRENALINE,
		DEFIBRILLATOR,
		VOMITJAR,
		AK47,
		GNOME_CHOMPSKI,
		COLA_BOTTLES,
		FIREWORKS_BOX,
		INCENDIARY_AMMO,
		FRAG_AMMO,
		MAGNUM,
		MP5,
		SG552,
		AWP,
		SCOUT,
		M60,
		TANK_CLAW,
		HUNTER_CLAW,
		CHARGER_CLAW,
		BOOMER_CLAW,
		SMOKER_CLAW,
		SPITTER_CLAW,
		JOCKEY_CLAW,
		MACHINEGUN,
		VOMIT,
		SPLAT,
		POUNCE,
		LOUNGE,
		PULL,
		CHOKE,
		ROCK,
		PHYSICS,
		AMMO,
		UPGRADE_ITEM
	};

	virtual ~C_WeaponCSBase() = 0;
	virtual bool unknown0() = 0;
	virtual bool IsHelpingHandExtended() = 0;
	virtual void *sub_102316A0() = 0;
	virtual char IsAttacking() = 0;
	virtual void *unknown_libname_20() = 0;
	virtual void *sub_10231290() = 0;
	virtual void *sub_10230AB0() = 0;
	virtual void *sub_102314E0() = 0;
	virtual int IsAwp() = 0;
	virtual bool CanZoom() = 0;
	virtual bool HasScope() = 0;
	virtual void *CycleZoom() = 0;
	virtual void *sub_10231AC0() = 0;
	virtual WeaponID GetWeaponID() = 0;
	virtual void *sub_10230B00() = 0;
	virtual void *sub_102325B0() = 0;
	virtual void *sub_10230B10() = 0;
	virtual void *sub_10230B20() = 0;
	virtual void *sub_10231F60() = 0;
	virtual void *sub_10231BE0() = 0;
	virtual void *sub_10231760() = 0;
	virtual void *sub_10231740() = 0;
	virtual void *sub_10230B30() = 0;
	virtual void *sub_10230B40() = 0;
	virtual void *sub_10230B50() = 0;
	virtual void *sub_10231860() = 0;
	virtual void *sub_10231880() = 0;
	virtual void *sub_10230B70() = 0;
	virtual void *sub_102315E0() = 0;
	virtual void *sub_10230BC0() = 0;
	virtual void *sub_102315D0() = 0;
	virtual void *sub_102318A0() = 0;
	virtual void *sub_10230B80() = 0;
	virtual void *sub_10230B90() = 0;
	virtual void *sub_10230BA0() = 0;
	virtual void *sub_10230BB0() = 0;

	int padding_0[826];
	int m_MapBasedMeleeID;
};

class C_BasePlayer : public C_BaseCombatCharacter
{
public:
	virtual ~C_BasePlayer() = 0;
	virtual void *sub_10021E00() = 0;
	virtual void *nullsub_240() = 0;
	virtual void *sub_10021980() = 0;
	virtual void *sub_1001F0F0() = 0;
	virtual void CalcViewModelView(const Vector& eyeOrigin, const QAngle& eyeAngles) = 0;
	virtual void *sub_10069800() = 0;
	virtual void *sub_1001F290() = 0;
	virtual void *sub_1001F270() = 0;
	virtual void *sub_1001ED40() = 0;
	virtual void *nullsub_241() = 0;
	virtual void *sub_100648E0() = 0;
	virtual void *sub_10065CB0() = 0;
	virtual void *sub_1001FB30() = 0;
	virtual void *nullsub_242() = 0;
	virtual void *sub_100636B0() = 0;
	virtual void *sub_10069820() = 0;
	virtual void *sub_100211C0() = 0;
	virtual void *sub_100636F0() = 0;
	virtual void *nullsub_243() = 0;
	virtual void *nullsub_244() = 0;
	virtual void *sub_10063CC0() = 0;
	virtual void *sub_10063C70() = 0;
	virtual void *sub_10069880() = 0;
	virtual void *sub_10063810() = 0;
	virtual void *nullsub_245() = 0;
	virtual void *sub_10069890() = 0;
	virtual void *sub_100698A0() = 0;
	virtual void *sub_100698B0() = 0;
	virtual void *sub_100698C0() = 0;
	virtual void *sub_100698D0() = 0;
	virtual void *sub_100EC8B0() = 0;
	virtual void *sub_10069A40() = 0;
	virtual void *sub_100634D0() = 0;
	virtual void *sub_10067B70() = 0;
	virtual void *sub_100698E0() = 0;
	virtual void *sub_100698F0() = 0;
	virtual void *sub_10069900() = 0;
	virtual void *sub_10063540() = 0;
	virtual void *sub_10063490() = 0;
	virtual void *sub_1001F360() = 0;
	virtual void *sub_10020D90() = 0;
	virtual void *sub_10063840() = 0;
	virtual void *sub_10069170() = 0;
	virtual void *sub_10064530() = 0;
	virtual void *sub_1001FFF0() = 0;
	virtual void *sub_10020110() = 0;
	virtual void *sub_1001EE20() = 0;
	virtual void *sub_1001F940() = 0;
	virtual void *sub_10020F90() = 0;
	virtual void *sub_10069940() = 0;
	virtual void *sub_1001EE50() = 0;
	virtual void *sub_10069A50() = 0;
	virtual void *sub_1001EF00() = 0;
	virtual void *sub_1001EE70() = 0;
	virtual void *sub_100672A0() = 0;
	virtual void *sub_100674C0() = 0;
	virtual void *sub_1001FAC0() = 0;
	virtual void *sub_10069950() = 0;
	virtual void *sub_10021880() = 0;
	virtual void *nullsub_246() = 0;
	virtual char *GetCharacterDisplayName() = 0;
	virtual void *sub_1001F3A0() = 0;
	virtual void *sub_1001F430() = 0;
	virtual void *sub_10065850() = 0;
	virtual void *nullsub_247() = 0;
	virtual void *sub_10064940() = 0;
	virtual void *sub_10063700() = 0;
	virtual void *sub_100692A0() = 0;
	virtual void *sub_1001F4C0() = 0;
	virtual void *sub_10022020() = 0;
	virtual void *sub_1001ECB0() = 0;
	virtual void *sub_1001F850() = 0;
	virtual void *sub_1001F8B0() = 0;
	virtual void *nullsub_248() = 0;
	virtual void *sub_100699B0() = 0;
	virtual void *sub_100699C0() = 0;
	virtual void *sub_10063820() = 0;
	virtual void *sub_100699D0() = 0;
	virtual void *nullsub_249() = 0;
	virtual void *sub_1001F020() = 0;
	virtual void *sub_10066250() = 0;
	virtual void *sub_10066350() = 0;
	virtual void *sub_10066C00() = 0;
	virtual void *sub_10066EB0() = 0;
	virtual void *sub_10064130() = 0;
	virtual void *sub_10066780() = 0;
	virtual void *sub_100633E0() = 0;
	virtual void *sub_10063410() = 0;
	virtual void *sub_100699F0() = 0;
	virtual void *sub_10069A00() = 0;
	virtual void *sub_10069A10() = 0;
	virtual void *sub_10069A20() = 0;
	virtual void *sub_10069A30() = 0;

	bool IsMeleeWeaponActive()
	{
		/*C_WeaponCSBase *weapon = (C_WeaponCSBase *)GetActiveWeapon();
		if (weapon)
			return weapon->GetWeaponID() == 19;*/

		return false;
	}

	char pad_0004[260]; //0x0004
	Vector m_vecVelocity; //0x0108
	char pad_010C[48]; //0x0114
	int m_hGroundEntity; //0x0144
}; //Size: 0x0148
static_assert(sizeof(C_BasePlayer) == 0x0148);

class CBaseEdict
{
public:

	// Returns an IServerEntity if FL_FULLEDICT is set or NULL if this 
	// is a lightweight networking entity.
	void *GetIServerEntity();
	const void *GetIServerEntity() const;

	void *GetNetworkable();
	IServerUnknown *GetUnknown();

	// Set when initting an entity. If it's only a networkable, this is false.
	void				SetEdict(IServerUnknown *pUnk, bool bFullEdict);

	int					AreaNum() const;
	const char *GetClassName() const;

	bool				IsFree() const;
	void				SetFree();
	void				ClearFree();

	bool				HasStateChanged() const;
	void				ClearStateChanged();
	void				StateChanged();
	void				StateChanged(unsigned short offset);

	void				ClearTransmitState();

	void SetChangeInfo(unsigned short info);
	void SetChangeInfoSerialNumber(unsigned short sn);
	unsigned short	 GetChangeInfo() const;
	unsigned short	 GetChangeInfoSerialNumber() const;

public:

	// NOTE: this is in the edict instead of being accessed by a virtual because the engine needs fast access to it.
	// NOTE: YOU CAN'T CHANGE THE LAYOUT OR SIZE OF CBASEEDICT AND REMAIN COMPATIBLE WITH HL2_VC6!!!!!
#ifdef _XBOX
	unsigned short m_fStateFlags;
#else
	int	m_fStateFlags;
#endif	

	// NOTE: this is in the edict instead of being accessed by a virtual because the engine needs fast access to it.
	// int m_NetworkSerialNumber;

	// NOTE: m_EdictIndex is an optimization since computing the edict index
	// from a CBaseEdict* pointer otherwise requires divide-by-20. values for
	// m_NetworkSerialNumber all fit within a 16-bit integer range, so we're
	// repurposing the other 16 bits to cache off the index without changing
	// the overall layout or size of this struct. existing mods compiled with
	// a full 32-bit serial number field should still work. henryg 8/17/2011
#if VALVE_LITTLE_ENDIAN
	short m_NetworkSerialNumber;
	short m_EdictIndex;
#else
	short m_EdictIndex;
	short m_NetworkSerialNumber;
#endif

	// NOTE: this is in the edict instead of being accessed by a virtual because the engine needs fast access to it.
	void *m_pNetworkable;

	IServerUnknown *m_pUnk;


public:

	void *GetChangeAccessor(); // The engine implements this and the game .dll implements as
	const void *GetChangeAccessor() const; // The engine implements this and the game .dll implements as
	// as callback through to the engine!!!

	// NOTE: YOU CAN'T CHANGE THE LAYOUT OR SIZE OF CBASEEDICT AND REMAIN COMPATIBLE WITH HL2_VC6!!!!!
	// This breaks HL2_VC6!!!!!
	// References a CEdictChangeInfo with a list of modified network props.
	//unsigned short m_iChangeInfo;
	//unsigned short m_iChangeInfoSerialNumber;

	friend void InitializeEntityDLLFields(void *pEdict);
};

/*struct cplane_t
{
	Vector	normal;
	float	dist;
	byte	type;
	byte	signbits;
	byte	pad[2];
};
struct csurface_t
{
	const char* name;
	short			surfaceProps;
	unsigned short	flags;
};

struct trace_t : public CGameTrace
{
	Vector start;
	Vector end;
	cplane_t plane;
	float fraction;
	int contents;
	WORD dispFlags;
	bool allsolid;
	bool startsolid;
	float fractionleftsolid;
	csurface_t surface;
	int hitgroup;
	short physicsbone;
	CBaseEntity* m_pEnt;
	int hitbox;
}*/

struct edict_t : public CBaseEdict
{
public:
	void *GetCollideable();

	// The server timestampe at which the edict was freed (so we can try to use other edicts before reallocating this one)
	float		freetime;
};

enum ButtonCode_t
{
	KEY_SPACE = 65,
	KEY_ESCAPE = 70,
	KEY_UP = 88, 
	KEY_LEFT,
	KEY_DOWN,
	KEY_RIGHT,
	MOUSE_LEFT = 107
};

typedef ButtonCode_t MouseCode;
typedef ButtonCode_t KeyCode;

class IInput
{
public:
	virtual ~IInput();
	virtual void SetMouseFocus(void);;
	virtual void SetMouseCapture(void);
	virtual void GetKeyCodeText(ButtonCode_t, char *, int);
	virtual void GetFocus(void);
	virtual void GetCalculatedFocus(void);
	virtual void GetMouseOver(void);
	virtual void SetCursorPos(int, int);
	virtual void GetCursorPos(int &, int &);
	virtual void WasMousePressed(ButtonCode_t);
	virtual void WasMouseDoublePressed(ButtonCode_t);
	virtual void IsMouseDown(ButtonCode_t);
	virtual void SetCursorOveride(void);
	virtual void GetCursorOveride(void);
	virtual void WasMouseReleased(ButtonCode_t);
	virtual void WasKeyPressed(ButtonCode_t);
	virtual void IsKeyDown(ButtonCode_t);
	virtual void WasKeyTyped(ButtonCode_t);
	virtual void WasKeyReleased(ButtonCode_t);
	virtual void GetAppModalSurface(void);
	virtual void SetAppModalSurface(void);
	virtual void ReleaseAppModalSurface(void);
	virtual void GetCursorPosition(int &, int &);
	virtual void SetIMEWindow(void *);
	virtual void GetIMEWindow(void);
	virtual void OnChangeIME(bool);
	virtual void GetCurrentIMEHandle(void);
	virtual void GetEnglishIMEHandle(void);
	virtual void GetIMELanguageName(wchar_t *, int);
	virtual void GetIMELanguageShortCode(wchar_t *, int);
	virtual void GetIMELanguageList(void);
	virtual void GetIMEConversionModes(void);
	virtual void GetIMESentenceModes(void);
	virtual void OnChangeIMEByHandle(int);
	virtual void OnChangeIMEConversionModeByHandle(int);
	virtual void OnChangeIMESentenceModeByHandle(int);
	virtual void OnInputLanguageChanged(void);
	virtual void OnIMEStartComposition(void);
	virtual void OnIMEComposition(int);
	virtual void OnIMEEndCompositionEv(void);;
	virtual void OnIMEShowCandidates(void);
	virtual void OnIMEChangeCandidates(void);
	virtual void OnIMECloseCandidates(void);
	virtual void OnIMERecomputeModes(void);
	virtual void GetCandidateListCount(void);
	virtual void GetCandidate(int, wchar_t *, int);
	virtual void GetCandidateListSelectedItem(void);
	virtual void GetCandidateListPageSize(void);
	virtual void GetCandidateListPageStart(void);
	virtual void SetCandidateWindowPos(int, int);
	virtual void GetShouldInvertCompositionString(void);
	virtual void CandidateListStartsAtOne(void);
	virtual void SetCandidateListPageStart(int);
	virtual void SetMouseCaptureEx(void);
	virtual void RegisterKeyCodeUnhandledListener(void);
	virtual void UnregisterKeyCodeUnhandledListener(void);
	virtual void OnKeyCodeUnhandled(void);
	virtual void SetModalSubTree(void);
	virtual void ReleaseModalSubTree(void);
	virtual void GetModalSubTree(void);
	virtual void SetModalSubTreeReceiveMessages(bool);
	virtual void ShouldModalSubTreeReceiveMessages(void);
	virtual void GetMouseCapture(void);
	virtual void GetMouseFocus(void);
	virtual void RunFrame(void);
	virtual void UpdateMouseFocus(int, int);
	virtual void PanelDeleted(void);
	virtual void InternalCursorMoved(void);
	virtual void InternalMousePressed(ButtonCode_t);
	virtual void InternalMouseDoublePressed(ButtonCode_t);
	virtual void InternalMouseReleased(ButtonCode_t);
	virtual void InternalMouseWheeled(int);
	virtual void InternalKeyCodePressed(KeyCode);
	virtual void InternalKeyCodeTyped(KeyCode code);
	virtual void InternalKeyTyped(void);
	virtual void InternalKeyCodeReleased(KeyCode code);
	virtual void CreateInputContext(void);
	virtual void DestroyInputContext(int);
	virtual void AssociatePanelWithInputContext(void);
	virtual void ActivateInputContext(int);
	virtual void PostCursorMessageEv(void);
	virtual void UpdateCursorPosInternal(int, int);
	virtual void HandleExplicitSetCursor(void);
	virtual void SetKeyCodeState(ButtonCode_t, bool);
	virtual void SetMouseCodeState(void);
	virtual void UpdateButtonState(void);
	virtual void ResetInputContext(int);
	virtual void IsChildOfModalPanel(void);
};

class ISurface
{
public:
	virtual void sub_10012FD0() = 0;
	virtual void sub_100130F0() = 0;
	virtual void sub_1000A8A0() = 0;
	virtual void sub_10010D40() = 0;
	virtual void sub_10014120() = 0;
	virtual void sub_10008140() = 0;
	virtual void sub_10008060() = 0;
	virtual void sub_10008030() = 0;
	virtual void sub_10013610() = 0;
	virtual void sub_10011190() = 0;
	virtual void sub_10008210() = 0;
	virtual void sub_100081E0() = 0;
	virtual void sub_1000C930() = 0;
	virtual void sub_1000CAB0() = 0;
	virtual void sub_100083E0() = 0;
	virtual void sub_1000B840() = 0;
	virtual void sub_1000B900() = 0;
	virtual void sub_100087F0() = 0;
	virtual void sub_10008860() = 0;
	virtual void sub_10008800() = 0;
	virtual void sub_100088D0() = 0;
	virtual void sub_100088F0() = 0;
	virtual void sub_1000E870() = 0;
	virtual void sub_10008950() = 0;
	virtual void sub_1000E4E0() = 0;
	virtual void sub_10008510() = 0;
	virtual void sub_100084B0() = 0;
	virtual void sub_10008530() = 0;
	virtual void sub_10009A60() = 0;
	virtual void sub_1000D910() = 0;
	virtual void sub_100085D0() = 0;
	virtual void sub_1000D940() = 0;
	virtual void sub_10009A30() = 0;
	virtual void sub_10008490() = 0;
	virtual void sub_10008450() = 0;
	virtual void sub_1000E890() = 0;
	virtual void nullsub_28() = 0;
	virtual void sub_10008EC0() = 0;
	virtual void sub_10008D40() = 0;
	virtual void nullsub_29() = 0;
	virtual void sub_10008D60() = 0;
	virtual void sub_10008DB0() = 0;
	virtual void GetScreenSize(int& iWide, int& iTall) = 0;
	virtual void sub_10013B40() = 0;
	virtual void nullsub_31() = 0;
	virtual void sub_10013BC0() = 0;
	virtual void nullsub_32() = 0;
	virtual void nullsub_33() = 0;
	virtual void sub_10008FA0() = 0;
	virtual void sub_10009A00() = 0;
	virtual void sub_10009A00_1() = 0;
	virtual void sub_10009A00_2() = 0;
	virtual void sub_10009A00_3() = 0;
	virtual void sub_10009A00_4() = 0;
	virtual void sub_10009A00_5() = 0;
	virtual void sub_10009A00_6() = 0;
	virtual bool IsCursorVisible() = 0;
	virtual void nullsub_3() = 0;
	virtual void sub_10005A00() = 0;
	virtual void sub_1002E170() = 0;
	virtual void sub_10004550() = 0;
	virtual void sub_10005C00() = 0;
	virtual void nullsub_2_2_2() = 0;
	virtual void sub_1009F2F0() = 0;
	virtual void sub_100065F0() = 0;
	virtual void sub_10006610() = 0;
	virtual void nullsub_2_2_2_2() = 0;
	virtual void sub_1009F2F0_2() = 0;
	virtual void sub_10005AB0() = 0;
	virtual void sub_10005230() = 0;
	virtual void sub_10005240() = 0;
	virtual void sub_1000FEF0() = 0;
	virtual void sub_100052C0() = 0;
	virtual void sub_100052E0() = 0;
	virtual void sub_10005300() = 0;
	virtual void sub_10005320() = 0;
	virtual void sub_10005350() = 0;
	virtual void sub_100053A0() = 0;
	virtual void sub_1009F2F0_3() = 0;
	virtual void nullsub_4() = 0;
	virtual void sub_10005B30() = 0;
	virtual void sub_10010EF0() = 0;
	virtual void sub_10010F30() = 0;
	virtual void sub_10005A10() = 0;
	virtual void sub_10005A60() = 0;
	virtual void sub_10005BC0() = 0;
	virtual void sub_1000FA80() = 0;
	virtual void sub_10010430() = 0;
	virtual void sub_10010630() = 0;
	virtual void sub_1000BA90() = 0;
	virtual void sub_10005CE0() = 0;
	virtual void sub_10005B90() = 0;
	virtual void sub_100058B0() = 0;
	virtual void sub_10006630() = 0;
	virtual void sub_10010E10() = 0;
	virtual void sub_10006660() = 0;
	virtual void sub_10006980() = 0;
	virtual void sub_1002E170_2() = 0;
	virtual void sub_10006990() = 0;
	virtual void sub_100069B0() = 0;
	virtual void sub_10008190() = 0;
	virtual void sub_1000A400() = 0;
	virtual void sub_10004710() = 0;
	virtual void sub_1000AA10() = 0;
	virtual void sub_1000AB40() = 0;
	virtual void sub_1000DDA0() = 0;
	virtual void sub_10006420() = 0;
	virtual void sub_10005940() = 0;
	virtual void sub_10004A70() = 0;
	virtual void sub_100055F0() = 0;
	virtual void sub_10007470() = 0;
	virtual void sub_10007650() = 0;
	virtual void sub_100069D0() = 0;
	virtual void sub_100064F0() = 0;
	virtual void OnScreenSizeChanged(int nOldWidth, int nOldHeight) = 0;
	virtual void sub_100069E0() = 0;
	virtual void sub_10007410() = 0;
	virtual void sub_1000BAC0() = 0;
	virtual void sub_10005EA0() = 0;
	virtual void sub_10006A00() = 0;
	virtual void sub_10004760() = 0;
	virtual void sub_10009830() = 0;
	virtual void sub_10006580() = 0;
	virtual void sub_100054E0() = 0;
	virtual void sub_10005280() = 0;
	virtual void sub_10010170() = 0;
	virtual void sub_10011380() = 0;
	virtual void sub_100109C0() = 0;
	virtual void sub_10005400() = 0;
	virtual void sub_100114A0() = 0;
	virtual void sub_10005560() = 0;
	virtual void sub_1000B400() = 0;
	virtual void sub_10005410() = 0;
	virtual bool ForceScreenSizeOverride(bool bState, int wide, int tall) = 0;
	virtual bool ForceScreenPosOffset(bool bState, int x, int y) = 0;
	virtual void OffsetAbsPos(int& x, int& y) = 0;
	virtual void SetAbsPosForContext(int id, int x, int y) = 0;
	virtual void GetAbsPosForContext(int id, int& x, int& y) = 0;
	virtual void ResetFontCaches() = 0;
	virtual bool IsScreenSizeOverrideActive() = 0;
};
/*
		typedef Server_WeaponCSBase *(__thiscall *tGetActiveWep)(void *thisptr);
		static tGetActiveWep oGetActiveWep = (tGetActiveWep)(m_Game->m_Offsets->GetActiveWeapon.address);
		Server_WeaponCSBase *curWep = oGetActiveWep(pPlayer);
*/
class CWeaponPortalBase
{
public:
	//char pad_0000[3740]; //0000
	char pad_0000[300];
	CBaseEntity* m_hOwner;
	char pad_0001[3436];
	int m_iLastFiredPortal; //0xE9C
}; static_assert(sizeof(CWeaponPortalBase) == 0xEA0);

class C_Portal_Player
{
public:
	inline CWeaponPortalBase* GetActivePortalWeapon() {
		typedef CWeaponPortalBase* (__thiscall* tGetActivePortalWeapon)(void* thisptr);
		//static tGetActivePortalWeapon oGetActivePortalWeapon = (tGetActivePortalWeapon)(g_Game->m_Offsets->GetActivePortalWeapon.address);
		static tGetActivePortalWeapon oGetActivePortalWeapon = (tGetActivePortalWeapon)(*(uintptr_t*)this + 968);
		return oGetActivePortalWeapon(this);
	};

	char pad_0000[9152]; //0000
	CNewParticleEffect* m_PointLaser; //0x23C0
};

class VPanel
{
public:
	VPanel();
	virtual ~VPanel();

	virtual void Init(void* attachedClientPanel);

	virtual void* Plat();
	virtual void SetPlat(void* pl);

	virtual void GetHPanel(); // safe pointer handling
	virtual void SetHPanel(void* hPanel);

	virtual bool IsPopup();
	virtual void SetPopup(bool state);
	virtual bool IsFullyVisible();

	virtual void SetPos(int x, int y);
	virtual void GetPos(int& x, int& y);
	virtual void SetSize(int wide, int tall);
	virtual void GetSize(int& wide, int& tall);
	virtual void SetMinimumSize(int wide, int tall);
	virtual void GetMinimumSize(int& wide, int& tall);
	virtual void SetZPos(int z);
	virtual int  GetZPos();

	virtual void GetAbsPos(int& x, int& y);
	virtual void GetClipRect(int& x0, int& y0, int& x1, int& y1);
	virtual void SetInset(int left, int top, int right, int bottom);
	virtual void GetInset(int& left, int& top, int& right, int& bottom);

	virtual void Solve();

	virtual void SetVisible(bool state);
	virtual void SetEnabled(bool state);
	virtual bool IsVisible();
	virtual bool IsEnabled();
	virtual void SetParent(VPanel* newParent);
	virtual int GetChildCount();
	virtual VPanel* GetChild(int index);
	virtual void* GetChildren();
	virtual VPanel* GetParent();
	virtual void MoveToFront();
	virtual void MoveToBack();
	virtual bool HasParent(VPanel* potentialParent);

	// gets names of the object (for debugging purposes)
	virtual const char* GetName();
	virtual const char* GetClassName();

	virtual void GetScheme();

	// handles a message
	virtual void SendMessage(void* params, VPanel ifromPanel);

	// wrapper to get Client panel interface
	virtual void* Client();

	// input interest
	virtual void SetKeyBoardInputEnabled(bool state);
	virtual void SetMouseInputEnabled(bool state);
	virtual bool IsKeyBoardInputEnabled();
	virtual bool IsMouseInputEnabled();

	virtual bool IsTopmostPopup() const;
	virtual void SetTopmostPopup(bool bEnable);

	virtual void SetMessageContextId(int nContextId);
	virtual int GetMessageContextId();

	virtual void OnUnserialized(void* pElement);
	// sibling pins
	virtual void SetSiblingPin(VPanel* newSibling, byte iMyCornerToPin = 0, byte iSiblingCornerToPinTo = 0);

public:
	virtual void GetInternalAbsPos(int& x, int& y);
};
