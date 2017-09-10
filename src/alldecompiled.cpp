#include "alldecompiled.h"
#include <cstdio>
#include <cstdarg>

void Com_Assertf(const char* const File_, const int Line_, const int DoDebugBreak_, const char* const Fmt_, ...)
{
    va_list va;
    va_start(va, Fmt_);

    char buffer[4096];
    vsnprintf_s(buffer, sizeof(buffer), sizeof(buffer) - 1, Fmt_, va);
    va_end(va);

    ((void(__cdecl*)(const char* const, const int, const int, const char* const))0x0048E6A0)(File_, Line_, DoDebugBreak_, buffer);
}
