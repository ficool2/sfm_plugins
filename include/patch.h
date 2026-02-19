#pragma once

#include <Windows.h>

#define DEFINE_NAKED_HOOK( name ) void* name = NULL; \
void* Ret_##name = NULL; \
__declspec( naked ) void Hook_##name()

#define INITIALIZE_NAKED_HOOK( name, address, pad ) \
name = address; \
Ret_##name = Patch::WriteJump( address, Hook_##name, pad )

namespace Patch
{
	template <size_t N>
	struct Payload
	{
		unsigned char payload[N];
	};

	// writes 5 bytes, returns the return address
	void* WriteJump( void* address, void* trampoline, int pad );

	// writes arbitrary payload
	template <typename T>
	void WriteData( void* address, const T& data )
	{
		DWORD oldProtect;
		VirtualProtect( address, sizeof( data ), PAGE_EXECUTE_READWRITE, &oldProtect );

		memcpy( address, &data, sizeof( data ) );

		VirtualProtect( address, 5, oldProtect, &oldProtect );
	}

	// writes nop instructions
	void WriteNoop( void* address, int length );

	// writes string including null terminator
	void WriteString( void* address, const char* string );
}