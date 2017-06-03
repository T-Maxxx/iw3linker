#ifndef IMPORTS
#define IMPORTS

#define IMPORTS_ADVAPI32_ADDR (0x004D1000)
#define IMPORTS_KERNEL32_ADDR (0x004D1010)
#define IMPORTS_USER32_ADDR   (0x004D11AC)
#define IMPORTS_WINMM_ADDR    (0x004D11CC)
#define IMPORTS_D3DX9_34_ADDR (0x004D11D4)
#define IMPORTS_MSS32_ADDR    (0x004D11E8)

typedef struct import_info_s
{
	char*  libName;
	int    startAddress;
	int    functionsCount;
	char** functions;
} import_info_t;

extern import_info_t imports[6];

#endif
