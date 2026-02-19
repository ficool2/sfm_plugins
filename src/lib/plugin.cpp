// Base code for all plugins
// by ficool2

#include "plugin.h"

#include <windows.h>

ConColorMsgFunc ConColorMsg = nullptr;

extern IServerPluginCallbacks* g_pPlugin;

extern "C" __declspec( dllexport ) void* CreateInterface( const char* pName, int* pReturnCode )
{
	if ( !strcmp( INTERFACEVERSION_ISERVERPLUGINCALLBACKS, pName ) )
	{
		if ( pReturnCode )
			*pReturnCode = 0;
		return g_pPlugin;
	}

	if ( pReturnCode )
		*pReturnCode = 1;

	return nullptr;
}

BOOL WINAPI DllMain( HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved )
{
	if ( fdwReason == DLL_PROCESS_ATTACH )
	{
		HMODULE tier0 = GetModuleHandle( "tier0" );
		ConColorMsg = ( ConColorMsgFunc )GetProcAddress( tier0, "?ConColorMsg@@YAXABVColor@@PBDZZ" );
		if ( !ConColorMsg )
			return FALSE;
	}

	return TRUE;
}