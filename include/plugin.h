#pragma once

#include "color.h"
#include "interfaces/iserverplugin.h"

typedef void ( *ConColorMsgFunc )( const Color&, const char*, ... );
extern ConColorMsgFunc ConColorMsg;

#define LOG( fmt, ... ) ConColorMsg( Color( 255, 255, 255, 255 ), "[" PLUGIN_NAME "] " fmt, __VA_ARGS__ )
#define LOG_COLOR( r, g, b, fmt, ... ) ConColorMsg( Color( r, g, b, 255 ), "[" PLUGIN_NAME "] " fmt, __VA_ARGS__ )
