#include "updater.h"
#include <Windows.h>

HANDLE g_UpdaterThread;

static DWORD WINAPI UpdaterThread(LPVOID arg)
{
    UNREFERENCED_PARAMETER(arg);

    return 0; // Return "No updates available"
}

void LaunchUpdater()
{
    g_UpdaterThread = CreateThread(NULL, 0, UpdaterThread, NULL, 0, NULL);
}

int IsUpdateAvailable()
{
    DWORD dwWaitResult = WaitForSingleObject(g_UpdaterThread, 1000); // Give thread 1 second to end.
    if (dwWaitResult == WAIT_OBJECT_0) // Thread done.
    {
        DWORD exitCode;
        GetExitCodeThread(g_UpdaterThread, &exitCode);
        if (exitCode == 1) // Guard other values.
            return 1;
    }
    // Thread still works or something goes wrong.
    return 0;
}

// TODO: show version.
void NotifyUser()
{
    if (MessageBox(0, "New update available. Would you like to browse Github repo?", "New update", MB_OKCANCEL | MB_TOPMOST) == IDOK)
    {
        ShellExecute(0, 0, "https://github.com/T-Maxxx/iw3linker/releases", 0, 0 , SW_SHOW);
    }
}
