// Fixes $blendmodulatetexture not appearing while rendering under projected lights
// Affects LightmappedGeneric / WorldVertexTransition shaders
// by ficool2

#include "plugin.h"
#include "patch.h"

//#define COMBO_TEST

#ifdef COMBO_TEST
#include "flashlightcombotest.h"
#endif

#define MATERIAL_VAR_TYPE_TEXTURE 3

static char bDrawFlashlightBlendModulate = false;
static int nDrawFlashlightBlendModulateVar = -1;

void* CBaseVSShader__BindTexture = NULL;

DEFINE_NAKED_HOOK( CBaseVSShader__DrawFlashlight_dx90 )
{
	__asm
	{
		// eax = LightmappedGeneric_DX9_Vars_t ptr
		mov		eax, [ebp+18h]
		// offset to m_nBlendModulateTexture
		mov		eax, [eax+94h]
		mov		[nDrawFlashlightBlendModulateVar], eax

		// thrashed
		push	ebp
		mov		ebp, esp
		sub		esp, 2C4h

		// get the material var
		// edx = IMaterialVar params
		mov		edx, [ebp+8]
		// eax = IMaterialVar ptr
		mov		eax, [edx+eax*4]
		// fetch m_Type
		mov		al, [eax+1Ch]
		and		al, 0Fh
		cmp		al, MATERIAL_VAR_TYPE_TEXTURE
		sete	al
		mov		[bDrawFlashlightBlendModulate], al

		jmp		Ret_CBaseVSShader__DrawFlashlight_dx90
	}
}

DEFINE_NAKED_HOOK( CBaseVSShader__DrawFlashlight_dx90_EnableTexture2 )
{
	__asm
	{
		// thrashed
		push	1
		push	4
		mov		ecx, esi
		call	eax

		// check blend modulate is being used
		mov		al, [bDrawFlashlightBlendModulate]
		test	al, al
		jz		RETURN

		// pShaderShadow->EnableTexture( SHADER_SAMPLER9, true )
		mov     edx, [esi]
		mov     eax, [edx+54h]
		push    1
		push    9
		mov     ecx, esi
		call    eax

		// pShaderShadow->EnableSRGBRead( SHADER_SAMPLER9, false )
		mov     edx, [esi]
		mov     eax, [edx+50h]
		push    0
		push    9
		mov     ecx, esi
		call    eax

	RETURN:
		jmp		Ret_CBaseVSShader__DrawFlashlight_dx90_EnableTexture2
	}
}

DEFINE_NAKED_HOOK( CBaseVSShader__DrawFlashlight_dx90_GetStaticPSIndex )
{
	__asm
	{
		xor		ecx, ecx
		mov		cl, [bDrawFlashlightBlendModulate]

		// stick in the new combos
		lea     edx, [ecx+ecx*2]
		lea     eax, [eax+edx*2]

		// thrashed
		add		eax, ebx
		lea		ecx, [eax+eax*2]

		jmp		Ret_CBaseVSShader__DrawFlashlight_dx90_GetStaticPSIndex
	}
}

DEFINE_NAKED_HOOK( CBaseVSShader__DrawFlashlight_dx90_BindTexture2 )
{
	__asm
	{
		// thrashed
		call	CBaseVSShader__BindTexture

		mov		al, [bDrawFlashlightBlendModulate]
		test	al, al
		jz		RETURN

		push	-1
		mov		eax, [nDrawFlashlightBlendModulateVar]
		push	eax
		push	9
		call	CBaseVSShader__BindTexture

	RETURN:
		jmp		Ret_CBaseVSShader__DrawFlashlight_dx90_BindTexture2
	}
}

// test to see optimized compiler output when adding new combo
#ifdef COMBO_TEST
__declspec( noinline ) int ComboTestMOD( int NORMALMAP, int NORMALMAP2, int WORLDVERTEXTRANSITION, int SEAMLESS, int DETAILTEXTURE, int DETAIL_BLEND_MODE, int FLASHLIGHTDEPTHFILTERMODE, int FANCY_BLENDING )
{
	flashlight_ps30_MOD_Static_Index pshIndex;

	pshIndex.SetNORMALMAP( NORMALMAP );
	pshIndex.SetNORMALMAP2( NORMALMAP2 );
	pshIndex.SetWORLDVERTEXTRANSITION( WORLDVERTEXTRANSITION );
	pshIndex.SetSEAMLESS( SEAMLESS );
	pshIndex.SetDETAILTEXTURE( DETAILTEXTURE );
	pshIndex.SetDETAIL_BLEND_MODE( DETAIL_BLEND_MODE );
	pshIndex.SetFLASHLIGHTDEPTHFILTERMODE( FLASHLIGHTDEPTHFILTERMODE );
	pshIndex.SetFANCY_BLENDING( FANCY_BLENDING );

	return pshIndex.GetIndex();
}

__declspec( noinline ) int ComboTestSFM( int NORMALMAP, int NORMALMAP2, int WORLDVERTEXTRANSITION, int SEAMLESS, int DETAILTEXTURE, int DETAIL_BLEND_MODE, int FLASHLIGHTDEPTHFILTERMODE)
{
	flashlight_ps30_SFM_Static_Index pshIndex;

	pshIndex.SetNORMALMAP( NORMALMAP );
	pshIndex.SetNORMALMAP2( NORMALMAP2 );
	pshIndex.SetWORLDVERTEXTRANSITION( WORLDVERTEXTRANSITION );
	pshIndex.SetSEAMLESS( SEAMLESS );
	pshIndex.SetDETAILTEXTURE( DETAILTEXTURE );
	pshIndex.SetDETAIL_BLEND_MODE( DETAIL_BLEND_MODE );
	pshIndex.SetFLASHLIGHTDEPTHFILTERMODE( FLASHLIGHTDEPTHFILTERMODE );

	return pshIndex.GetIndex();
}
#endif

class CPlugin_BlendModulateLightFix : public IServerPluginCallbacks
{
	bool Load( CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory ) override;
	void Unload( void ) override {}
	void Pause( void ) override {}
	void UnPause( void ) override {}
	const char* GetPluginDescription( void ) override { return PLUGIN_NAME; }
	void LevelInit( char const* pMapName ) override {}
	void ServerActivate( edict_t* pEdictList, int edictCount, int clientMax ) override {}
	void GameFrame( bool simulating ) override {}
	void LevelShutdown( void ) override {}
	void ClientActive( edict_t* pEntity ) override {}
	void ClientFullyConnect( edict_t* pEntity ) override {}
	void ClientDisconnect( edict_t* pEntity ) override {}
	void ClientPutInServer( edict_t* pEntity, char const* playername ) override {}
	void SetCommandClient( int index ) override {}
	void ClientSettingsChanged( edict_t* pEdict ) override {}
	PLUGIN_RESULT ClientConnect( bool* bAllowConnect, edict_t* pEntity, const char* pszName, const char* pszAddress, char* reject, int maxrejectlen ) override { return PLUGIN_CONTINUE; }
	PLUGIN_RESULT ClientCommand( edict_t* pEntity, const CCommand& args ) override { return PLUGIN_CONTINUE; }
	PLUGIN_RESULT NetworkIDValidated( const char* pszUserName, const char* pszNetworkID ) override { return PLUGIN_CONTINUE; }
	void OnQueryCvarValueFinished( QueryCvarCookie_t iCookie, edict_t* pPlayerEntity, int eStatus, const char* pCvarName, const char* pCvarValue ) override {}
	void OnEdictAllocated( edict_t* edict ) override {}
	void OnEdictFreed( const edict_t* edict )  override {}
};

bool CPlugin_BlendModulateLightFix::Load( CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory )
{
	LOG( "Loading...\n" );

	auto stdshader_dx9 = ( unsigned char* )GetModuleHandle( "stdshader_dx9" );
	if ( stdshader_dx9 == NULL )
	{
		LOG( "Failed to find stdshader_dx9\n" );
		return false;
	}

	CBaseVSShader__BindTexture = stdshader_dx9 + 0x65350;
	INITIALIZE_NAKED_HOOK( CBaseVSShader__DrawFlashlight_dx90, stdshader_dx9 + 0x3160, 4 );
	INITIALIZE_NAKED_HOOK( CBaseVSShader__DrawFlashlight_dx90_EnableTexture2, stdshader_dx9 + 0x338a, 3 );
	INITIALIZE_NAKED_HOOK( CBaseVSShader__DrawFlashlight_dx90_GetStaticPSIndex, stdshader_dx9 + 0x385f, 0 );
	INITIALIZE_NAKED_HOOK( CBaseVSShader__DrawFlashlight_dx90_BindTexture2, stdshader_dx9 + 0x3e87, 0 );

#ifdef COMBO_TEST
	LOG( "ComboTestMOD %d\n", ComboTestMOD( rand() % 3, rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 12, rand() % 3, rand() % 2 ) );
	LOG( "ComboTestSFM %d\n", ComboTestSFM( rand() % 3, rand() % 2, rand() % 2, rand() % 2, rand() % 2, rand() % 12, rand() % 3 ) );
#endif

	return true;
}

static CPlugin_BlendModulateLightFix g_PluginBlendModulateLightFix;
IServerPluginCallbacks* g_pPlugin = &g_PluginBlendModulateLightFix;