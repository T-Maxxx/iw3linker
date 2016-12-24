#pragma once

extern void (*Com_Assertf)(const char *file_path, const int line, int unknown, const char *text, ...);

#define BOOL_ASSERT(expression, text, ... ) if (!(expression)) Com_Assertf(__FILE__,__LINE__,0,(text),__VA_ARGS__);
