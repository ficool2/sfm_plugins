// Unrestricts uploading files of any extension and path under Scripts category
// by ficool2

#include "plugin.h"
#include "patch.h"

class CPlugin_ScriptUpload : public IServerPluginCallbacks
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

bool CPlugin_ScriptUpload::Load( CreateInterfaceFn interfaceFactory, CreateInterfaceFn gameServerFactory )
{
	LOG( "Loading...\n" );

	auto ifm = ( unsigned char* )GetModuleHandle( "ifm" );
	if ( ifm == NULL )
	{
		LOG( "Failed to find ifm\n" );
		return false;
	}

	// replace scripts *.py with all files *.* string
	{
		char** string = ( char** )( ifm + 0x1c031c );
		char** replace = ( char** )( ifm + 0xa95848 );
		Patch::WriteData( string, replace );
	}

	// remove check for wrong path
	{
		unsigned char* checkbadpath = ifm + 0x1c0d72;

		// nop, jmp
		Patch::WriteNoop( checkbadpath, 6 );
	}

	return true;
}

static CPlugin_ScriptUpload g_PluginScriptUpload;
IServerPluginCallbacks* g_pPlugin = &g_PluginScriptUpload;