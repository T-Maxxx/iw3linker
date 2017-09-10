#include <stdlib.h>
#include <cstdio>
#include <Windows.h>
#include "../types.h"
#include "../console.h"
#include "db_stream.h"
#include <alldecompiled.h>

void DB_InitStream()
{
    byte_t *memory = static_cast<byte_t *>(VirtualAlloc(nullptr, 0x18000000 + 0x14000000 + 0x8000000, MEM_RESERVE, PAGE_READWRITE));
    if (memory)
    {
        g_streamOutMemory = memory;
        g_streamMemory = g_streamOutMemory + 0x18000000;
        g_tempStreamMemory = g_streamMemory + 0x14000000;
        return;
    }

    g_streamOutMemory = static_cast<byte_t *>(VirtualAlloc(nullptr, 0x18000000, MEM_RESERVE, PAGE_READWRITE));
    QASSERTMSG(g_streamOutMemory, "VirtualAlloc returned NULL; may be out of memory");

    g_streamMemory = static_cast<byte_t *>(VirtualAlloc(nullptr, 0x14000000, MEM_RESERVE, PAGE_READWRITE));
    QASSERTMSG(g_streamMemory, "VirtualAlloc returned NULL; may be out of memory");

    g_tempStreamMemory = static_cast<byte_t *>(VirtualAlloc(nullptr, 0x8000000, MEM_RESERVE, PAGE_READWRITE));
    QASSERTMSG(g_tempStreamMemory, "VirtualAlloc returned NULL; may be out of memory");
}

void DB_InitStreamOut()
{
    QASSERT(!DB_GetStreamOut());
    QASSERT(g_streamOutMemory);

    DB_SetStreamOut(g_streamOutMemory);
    DB_SetStreamOutPos(g_streamOutMemory);
}

void DB_FreeStreamOut()
{
    QASSERT(DB_GetStreamOut() == g_streamOutMemory);
    VirtualFree(DB_GetStreamOut(), 0, MEM_DECOMMIT);
    DB_SetStreamOut(nullptr);
}

void __cdecl DB_WriteDataToStream(char DoWrite_, byte *Data_, int Size_, int *pStreamOutPos_)
{
    if (DoWrite_)
    {
        if (Size_)
        {
            byte_t* streamPos = DB_GetStreamPos();
            QASSERT(Size_ > 0);
            QASSERT(!((signed int)(&streamPos[Size_] - *((int *)g_streamZoneMem + 2 * g_streamPosIndex)) > g_streamBlockSize[g_streamPosIndex]));

            if ((unsigned int)(g_streamPosIndex - 1) < 3)
            {
                *pStreamOutPos_ = 0;
                if (g_streamPosIndex != 1)
                {
                    QASSERTF(g_streamDelayIndex < 4096, "g_streamDelayIndex doesn't index ARRAY_COUNT( g_streamDelayArray )\n\t%i not in [0, %i)", g_streamDelayIndex, 4096);

                    g_streamDelayArray[g_streamDelayIndex].Address = Data_;
                    g_streamDelayArray[g_streamDelayIndex].Size = Size_;
                    g_streamDelayIndex = g_streamDelayIndex + 1;
                }
            }
            else
            {
                byte_t* streamOutPos = DB_GetStreamOutPos();
                QASSERTF(Size_ + DB_GetStreamOutOffset() <= STREAM_OUT_SIZE, "Size_ %d, offset = %d", Size_, DB_GetStreamOutOffset());

                int oldPageIndex = (unsigned int)(&streamOutPos[4095]) & 0xFFFFF000;
                int newPageIndex = (unsigned int)&streamOutPos[Size_ + 4095] & 0xFFFFF000;
                if (oldPageIndex != newPageIndex)
                {
                    void* buf = VirtualAlloc((LPVOID)((unsigned int)(&streamOutPos[4095]) & 0xFFFFF000), newPageIndex - oldPageIndex, MEM_COMMIT, PAGE_READWRITE);
                    QASSERT(buf);
                }
                memcpy(streamOutPos, Data_, Size_);
                *pStreamOutPos_ = (int)streamOutPos;
                DB_SetStreamOutPos(&streamOutPos[Size_]);
            }
            DB_IncreaseStreamPos(Size_);
        }
        DB_SetSourcePos(&Data_[Size_]);
    }
}

void DB_ProcessDelayedStream()
{
    byte *streamOutPos;        // esi@2
    size_t size;               // edi@3
    unsigned int oldPageIndex; // ecx@5
    unsigned int newPageIndex; // eax@5
    void *address;             // [sp+4h] [bp-4h]@3

    if (g_streamDelayIndex)
    {
        for (int i = 0; i < g_streamDelayIndex; ++i)
        {
            streamOutPos = DB_GetStreamOutPos();
            size = g_streamDelayArray[i].Size;
            address = g_streamDelayArray[i].Address;
            QASSERT(size + DB_GetStreamOutOffset() <= STREAM_OUT_SIZE);
            /* expr mismatch
            if ( (signed int)(size + streamOutPos - g_streamOut) > 0x18000000 )
            {
                Com_Assertf(
                "C:\\trees\\cod3-pc\\cod3-modtools\\cod3src\\src\\database\\db_stream_save.cpp",
                278,
                0,
                "%s",
                "(g_streamOutPos + size) - g_streamOut <= STREAM_OUT_SIZE");
                streamOutPos = g_streamOutPos;
            }*/
            oldPageIndex = (unsigned int)(&streamOutPos[4095]) & 0xFFFFF000;
            newPageIndex = (unsigned int)&streamOutPos[size + 4095] & 0xFFFFF000;
            if (oldPageIndex != newPageIndex)
            {
                void* buf = VirtualAlloc((LPVOID)((unsigned int)(&streamOutPos[4095]) & 0xFFFFF000), newPageIndex - oldPageIndex, MEM_COMMIT, PAGE_READWRITE);
                QASSERT(buf);
            }
            memcpy(streamOutPos, address, size);
            DB_SetStreamOutPos(&streamOutPos[size]);
        }
    }
}
