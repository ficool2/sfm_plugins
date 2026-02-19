// Utility code for patching

#include "patch.h"

#include <string.h>

void* Patch::WriteJump( void* address, void* trampoline, int pad )
{
    DWORD oldProtect;
    VirtualProtect( address, 5, PAGE_EXECUTE_READWRITE, &oldProtect );

    unsigned char* p = ( unsigned char* )address;
    p[0] = 0xE9; // jmp

    uintptr_t rel = ( uintptr_t )trampoline - ( ( uintptr_t )address + 5 );
    *( int* )( p + 1 ) = ( int )rel;

    VirtualProtect( address, 5, oldProtect, &oldProtect );

    return ( void* )( ( uintptr_t )address + 5 + pad );
}

void Patch::WriteNoop( void* address, int length )
{
    DWORD oldProtect;
    VirtualProtect( address, length, PAGE_EXECUTE_READWRITE, &oldProtect );

    for ( int i = 0; i < length; i++ )
        ( ( unsigned char* )address )[i] = 0x90;

    VirtualProtect( address, length, oldProtect, &oldProtect );
}

void Patch::WriteString( void* address, const char* string )
{
    int len = strlen( string );

    DWORD oldProtect;
    VirtualProtect( address, len + 1, PAGE_EXECUTE_READWRITE, &oldProtect );

    strcpy( (char*)address, string );

    VirtualProtect( address, len + 1, oldProtect, &oldProtect );
}