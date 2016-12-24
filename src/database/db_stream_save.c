#include <stdlib.h>
#include <Windows.h>
#include "../types.h"
#include "../console.h"

#define g_streamMemory     (*((byte_t **)0x0065696C))
#define g_tempStreamMemory (*((byte_t **)0x00656968))
#define g_streamOutMemory  (*((byte_t **)0x00656B70))

void DB_InitStream()
{
    g_streamOutMemory = VirtualAlloc(0, 0x18000000, MEM_RESERVE, PAGE_READWRITE);
    BOOL_ASSERT(
        g_streamOutMemory,
        "%s\n%s",
        "(g_streamOutMemory)",
        "VirtualAlloc returned NULL; may be out of memory",
        GetLastError()
    );

    g_streamMemory = VirtualAlloc(0, 0x14000000, MEM_RESERVE, PAGE_READWRITE);
    BOOL_ASSERT(
        g_streamMemory,
        "%s\n%s\nGetLastError() = %d",
        "(g_streamMemory)",
        "VirtualAlloc returned NULL; may be out of memory",
        GetLastError()
    );

    g_tempStreamMemory =  VirtualAlloc(0, 0x8000000, MEM_RESERVE, PAGE_READWRITE);
    BOOL_ASSERT(
        g_tempStreamMemory,
        "%s\n%s\nGetLastError() = %d",
        "(g_tempStreamMemory)",
        "VirtualAlloc returned NULL; may be out of memory",
        GetLastError()
    );
}
