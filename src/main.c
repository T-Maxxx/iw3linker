#include "loader/loader.h"
#include "updater/updater.h"

int main(int argc, const char* argv[])
{
    LaunchUpdater();

    entry_point_t start = (entry_point_t)load_original_binary();
    start();

    if (IsUpdateAvailable())
        NotifyUser();
    return 0;
}
