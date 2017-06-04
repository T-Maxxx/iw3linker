#include <stdio.h>
#include <Windows.h>

#include "loader.h"
#include "linkerpc_data.h"
#include "linkerpc_rdata.h"
#include "linkerpc_text.h"
#include "linkerpc_idata.h"

#include "../database/db_stream_save.h"

#define LINKERPC_ENTRY_POINT (0x004B79A0)

#define SET_JUMP(addr, target) \
    do { \
        *(unsigned char*)(addr) = 0xE9; \
        *(unsigned int*)((addr) + 1) = (unsigned int)(target) - (unsigned int)(addr) - 5;\
    } while(0)

int (__cdecl* _fpmath)(int a1) = (int(__cdecl*)(int))0x004B32DB;

static void unprotect_segments()
{
    DWORD oldProtect;
    // .text
    VirtualProtect(
        GetOriginalSegmentLocation_text(),
        GetOriginalSegmentSize_text(),
        PAGE_READWRITE,
        &oldProtect
    );
    // .rdata
    VirtualProtect(
        GetOriginalSegmentLocation_rdata(),
        GetOriginalSegmentSize_rdata(),
        PAGE_READWRITE,
        &oldProtect
    );
    // .data
    VirtualProtect(
        GetOriginalSegmentLocation_data(),
        GetOriginalSegmentFullSize_data(),
        PAGE_READWRITE,
        &oldProtect
    );
    // .idata
    VirtualProtect(
        GetOriginalSegmentLocation_idata(),
        GetOriginalSegmentSize_idata(),
        PAGE_READWRITE,
        &oldProtect
    );
}

static void copy_segments()
{
    // .text
    memset(GetOriginalSegmentLocation_text(), 0, GetOriginalSegmentSize_text());
    memcpy(GetOriginalSegmentLocation_text(), GetOriginalSegmentData_text(), GetOriginalSegmentSize_text());

    // .rdata
    memset(GetOriginalSegmentLocation_rdata(), 0, GetOriginalSegmentSize_rdata());
    memcpy(GetOriginalSegmentLocation_rdata(), GetOriginalSegmentData_rdata(), GetOriginalSegmentSize_rdata());
    
    // .data
    memset(GetOriginalSegmentLocation_data(), 0, GetOriginalSegmentSize_data());
    memcpy(GetOriginalSegmentLocation_data(), GetOriginalSegmentData_data(), GetOriginalSegmentSize_data());
}

static void update_imports_table()
{
    int i = 0;
    int j = 0;
    HMODULE lib = 0;
    FARPROC* ptr = NULL;
    import_info_t* imports = GetImportsData();

    for(i = 0; i < GetImportsCount(); ++i)
    {
        lib = LoadLibraryA(imports[i].libName);

        if (lib == 0)
            exit(1);

        ptr = (FARPROC*)imports[i].startAddress;
        for(j = 0; j < imports[i].functionsCount; ++j)
        {
            ptr[j] = GetProcAddress(lib, imports[i].functions[j]);
            if(ptr[j] == 0)
            {
                MessageBoxA(0, "Can't update import table", "Error", MB_OK);
                exit(EXIT_FAILURE);
            }
        }
    }
}

static void protect_segments()
{
    DWORD oldProtect;
    // .text
    VirtualProtect(
        GetOriginalSegmentLocation_text(),
        GetOriginalSegmentSize_text(),
        PAGE_EXECUTE_READ,
        &oldProtect
    );
    // .rdata
    VirtualProtect(
        GetOriginalSegmentLocation_rdata(),
        GetOriginalSegmentSize_rdata(),
        PAGE_READONLY,
        &oldProtect
    );
    // .data
    VirtualProtect(
        GetOriginalSegmentLocation_data(),
        GetOriginalSegmentFullSize_data(),
        PAGE_READWRITE, // PAGE_EXECUTE_READWRITE
        &oldProtect
    );
    // .idata
    VirtualProtect(
        GetOriginalSegmentLocation_idata(),
        GetOriginalSegmentSize_idata(),
        PAGE_READONLY,
        &oldProtect
    );
}

static void patch_binary()
{
    /* Initialize floating point math to fix _fptrap stuff */
    _fpmath(1);
    /* Fix VirtualAlloc calls. */
    SET_JUMP(0x0044B270, DB_InitStream);
}

static entry_point_t get_entry_point()
{
    return (entry_point_t)LINKERPC_ENTRY_POINT;
}

entry_point_t load_original_binary()
{
    unprotect_segments();
    copy_segments();
    update_imports_table();
    patch_binary();
    protect_segments();
    return get_entry_point();
}
