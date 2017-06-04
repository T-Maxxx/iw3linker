#pragma once
#include "../types.h"

typedef struct import_info_t
{
    char*  libName;
    int    startAddress;
    int    functionsCount;
    char** functions;
} import_info_t;

import_info_t* GetImportsData();
uint_t GetImportsCount();
byte_t* GetOriginalSegmentLocation_idata();
uint_t GetOriginalSegmentSize_idata();
