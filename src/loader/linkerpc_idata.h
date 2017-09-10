#pragma once
#include "../types.h"

struct SImportInfo
{
    const char* libName;
    int startAddress;
    int functionsCount;
    const char** functions;
};

const SImportInfo* GetImportsData();
uint_t GetImportsCount();
byte_t* GetOriginalSegmentLocation_idata();
uint_t GetOriginalSegmentSize_idata();
