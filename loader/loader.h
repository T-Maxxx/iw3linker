#ifndef LOADER
#define LOADER

#include <stdio.h>

#include "imports.h"

#include "windows.h"

#define LINKERPC_ENTRY_POINT (0x004B79A0)

#define LINKERPC_TEXT        ((void*)0x00401000)
#define LINKERPC_IDATA       ((void*)0x004D1000)
#define LINKERPC_RDATA       ((void*)0x004D11F0)
#define LINKERPC_DATA        ((void*)0x00510000)

#define LINKERPC_TEXT_SIZE   (0x000D0000)
#define LINKERPC_IDATA_SIZE  (0x000D0000)
#define LINKERPC_RDATA_SIZE  (0x0003F000)
#define LINKERPC_DATA_SIZE   (0x0000B000)
#define LINKERPC_DATA_SIZE_F (0x117C1000)

extern unsigned char g_linkerPCText[];
extern unsigned char g_linkerPCRData[];
extern unsigned char g_linkerPCData[];

int load_original_binary();

#endif /* LOADER */
