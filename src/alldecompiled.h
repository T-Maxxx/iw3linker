#pragma once
#include "database/db_stream.h"

#define g_streamMemory (*((byte_t **)0x0065696C))
#define g_tempStreamMemory (*((byte_t **)0x00656968))
#define g_streamOutMemory (*((byte_t **)0x00656B70))
#define g_streamZoneMem (*((SZone**)0x118A54AC))
#define g_streamPosIndex (*((int*)0x118A54E4))
#define g_streamDelayIndex (*((int*)0x118A54B4))
#define g_streamDelayArray (((SStreamDelay*)0x118A54E8))
#define g_streamBlockSize (((int*)0x005109F8))
#define STREAM_OUT_SIZE (0x18000000)
#define g_streamPos (*((byte_t**)0x118A54B8))

void Com_Assertf(const char* const File_, const int Line_, const int DoDebugBreak_, const char* const Fmt_, ...);
