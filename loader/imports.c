#include "imports.h"

char* g_impADVAPI32[] = {
	"CryptReleaseContext",
	"CryptGenRandom",
	"CryptAcquireContextA"
};

char* g_impKERNEL32[] = {
	"SetConsoleMode",
	"ReadConsoleInputA",
	"GetConsoleScreenBufferInfo",
	"GetStdHandle",
	"SetConsoleTextAttribute",
	"VirtualAlloc",
	"VirtualFree",
	"FindClose",
	"FindNextFileA",
	"GetLastError",
	"CompareFileTime",
	"DeleteFileA",
	"FindFirstFileA",
	"SystemTimeToFileTime",
	"GetSystemTime",
	"RemoveDirectoryA",
	"GetModuleHandleA",
	"GlobalUnlock",
	"GlobalLock",
	"GlobalAlloc",
	"ExitProcess",
	"GetModuleFileNameA",
	"DebugBreak",
	"IsDebuggerPresent",
	"TerminateProcess",
	"GetCurrentProcess",
	"UnhandledExceptionFilter",
	"SetUnhandledExceptionFilter",
	"RaiseException",
	"RtlUnwind",
	"HeapFree",
	"EnterCriticalSection",
	"LeaveCriticalSection",
	"FileTimeToSystemTime",
	"FileTimeToLocalFileTime",
	"GetDriveTypeA",
	"GetFullPathNameA",
	"HeapAlloc",
	"GetProcAddress",
	"MoveFileA",
	"GetSystemTimeAsFileTime",
	"GetCommandLineA",
	"GetVersionExA",
	"GetProcessHeap",
	"CreateDirectoryA",
	"WriteConsoleW",
	"GetFileType",
	"GetModuleFileNameW",
	"HeapReAlloc",
	"GetCPInfo",
	"InterlockedIncrement",
	"InterlockedDecrement",
	"GetACP",
	"GetOEMCP",
	"IsValidCodePage",
	"TlsGetValue",
	"TlsAlloc",
	"TlsSetValue",
	"TlsFree",
	"SetLastError",
	"GetCurrentThreadId",
	"LCMapStringA",
	"WideCharToMultiByte",
	"MultiByteToWideChar",
	"LCMapStringW",
	"HeapDestroy",
	"HeapCreate",
	"DeleteCriticalSection",
	"WriteFile",
	"GetConsoleCP",
	"GetConsoleMode",
	"FlushFileBuffers",
	"SetHandleCount",
	"GetStartupInfoA",
	"Sleep",
	"GetCurrentDirectoryA",
	"LoadLibraryA",
	"InitializeCriticalSection",
	"CloseHandle",
	"ReadFile",
	"SetFilePointer",
	"HeapSize",
	"FreeEnvironmentStringsA",
	"GetEnvironmentStrings",
	"FreeEnvironmentStringsW",
	"GetEnvironmentStringsW",
	"QueryPerformanceCounter",
	"GetTickCount",
	"GetCurrentProcessId",
	"GetTimeZoneInformation",
	"LoadLibraryW",
	"GetStringTypeA",
	"GetStringTypeW",
	"GetLocaleInfoA",
	"WriteConsoleA",
	"GetConsoleOutputCP",
	"SetStdHandle",
	"CreateFileA",
	"SetEndOfFile",
	"CompareStringA",
	"CompareStringW",
	"SetEnvironmentVariableA"
};

char* g_impUSER32[] = {
	"GetDesktopWindow",
	"MessageBoxA",
	"GetActiveWindow",
	"CloseClipboard",
	"SetClipboardData",
	"EmptyClipboard",
	"OpenClipboard"
};

char* g_impWINMM[] = {
	"timeGetTime"
};

char* g_impD3DX9_34[] = {
	"D3DXGetShaderOutputSemantics",
	"D3DXCreateBuffer",
	"D3DXGetShaderInputSemantics",
	"D3DXGetShaderConstantTable"
};

char* g_impMSS32[] = {
	"_AIL_WAV_info@8"
};

import_info_t imports[6] =
{
	{
		"ADVAPI32.dll",
		IMPORTS_ADVAPI32_ADDR,
		sizeof(g_impADVAPI32) / sizeof(g_impADVAPI32[0]),
		g_impADVAPI32
	},
	{
		"KERNEL32.dll",
		IMPORTS_KERNEL32_ADDR,
		sizeof(g_impKERNEL32) / sizeof(g_impKERNEL32[0]),
		g_impKERNEL32
	},
	{
		"USER32.dll",
		IMPORTS_USER32_ADDR,
		sizeof(g_impUSER32) / sizeof(g_impUSER32[0]),
		g_impUSER32
	},
	{
		"WINMM.dll",
		IMPORTS_WINMM_ADDR,
		sizeof(g_impWINMM) / sizeof(g_impWINMM[0]),
		g_impWINMM
	},
	{
		"d3dx9_34.dll",
		IMPORTS_D3DX9_34_ADDR,
		sizeof(g_impD3DX9_34) / sizeof(g_impD3DX9_34[0]),
		g_impD3DX9_34
	},
	{
		"mss32.dll",
		IMPORTS_MSS32_ADDR,
		sizeof(g_impMSS32) / sizeof(g_impMSS32[0]),
		g_impMSS32
	}
};
