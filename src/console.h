#pragma once
#include <alldecompiled.h>

//#define QASSERT_GENERAL(expr, msg, fmt, ...) if ()

#define QASSERT(expr) if (!(expr)) Com_Assertf(__FILE__, __LINE__, 0, "%s\n", #expr)
#define QASSERTMSG(expr, msg) if (!(expr)) Com_Assertf(__FILE__, __LINE__, 0, "%s\n" msg, #expr)
#define QASSERTF(expr, fmt, ...) if (!(expr)) Com_Assertf(__FILE__, __LINE__, 0, "%s\n" fmt, #expr, __VA_ARGS__)

