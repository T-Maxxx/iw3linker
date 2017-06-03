#include "loader.h"
#include "../database/db_stream_save.h"

#define SET_JUMP(addr, target) \
    do { \
        *(unsigned char*)(addr) = 0xE9; \
        *(unsigned int*)((addr) + 1) = (unsigned int)(target) - (unsigned int)(addr) - 5;\
    } while(0)

int (__cdecl* _fpmath)(int a1) = (int(__cdecl*)(int))0x004B32DB;

static void unprotect_segments()
{
    DWORD oldProtect;

    VirtualProtect(LINKERPC_TEXT, LINKERPC_TEXT_SIZE, PAGE_READWRITE,
                   &oldProtect);
    VirtualProtect(LINKERPC_IDATA, LINKERPC_IDATA_SIZE, PAGE_READWRITE,
                   &oldProtect);
    VirtualProtect(LINKERPC_RDATA, LINKERPC_RDATA_SIZE, PAGE_READWRITE,
                   &oldProtect);
    VirtualProtect(LINKERPC_DATA, LINKERPC_DATA_SIZE_F, PAGE_READWRITE,
                   &oldProtect);
}

static void copy_segments()
{
    memset(LINKERPC_TEXT, 0, LINKERPC_TEXT_SIZE);
    memcpy(LINKERPC_TEXT, g_linkerPCText, LINKERPC_TEXT_SIZE);

    memset(LINKERPC_RDATA, 0, LINKERPC_RDATA_SIZE);
    memcpy(LINKERPC_RDATA, g_linkerPCRData, LINKERPC_RDATA_SIZE);

    memset(LINKERPC_DATA, 0, LINKERPC_DATA_SIZE_F);
    memcpy(LINKERPC_DATA, g_linkerPCData, LINKERPC_DATA_SIZE);
}

static void prepare_imports()
{
    int i = 0;
    int j = 0;
    int func_cnt = 0;
    HMODULE lib = 0;
    FARPROC* ptr = NULL;

    for(i = 0; i < (sizeof(imports) / sizeof(imports[0])); ++i)
    {
        lib = LoadLibraryA(imports[i].libName);

        if (lib == 0)
            exit(1);

        ptr = (FARPROC*)imports[i].startAddress;
        for(j = 0; j < imports[i].functionsCount; ++j)
        {
            ptr[j] = GetProcAddress(lib, imports[i].functions[j]);
            if(ptr[j] == 0)
                exit(2);
        }
    }
}

static void protect_segments()
{
    DWORD oldProtect;

    VirtualProtect(LINKERPC_TEXT, LINKERPC_TEXT_SIZE, PAGE_EXECUTE_READ,
                   &oldProtect);
    VirtualProtect(LINKERPC_IDATA, LINKERPC_IDATA_SIZE, PAGE_READONLY,
                   &oldProtect);
    VirtualProtect(LINKERPC_RDATA, LINKERPC_RDATA_SIZE, PAGE_READONLY,
                   &oldProtect);
    VirtualProtect(LINKERPC_DATA, LINKERPC_DATA_SIZE_F, PAGE_EXECUTE_READWRITE,
                   &oldProtect);
}

static void patch_binary()
{
    /* Initialize floating point math to fix _fptrap stuff */
    _fpmath(1);
    /* Fix VirtualAlloc calls. */
    SET_JUMP(0x0044B270, DB_InitStream);
}

static int get_entry_point()
{
    return LINKERPC_ENTRY_POINT;
}

int load_original_binary()
{
    unprotect_segments();
    copy_segments();
    prepare_imports();
    patch_binary();
    protect_segments();
    return get_entry_point();
}
