#pragma once

///////////////////////
// Updater system.
//
// Ask Github repo for updates, show notify
//   and open repo in browser to download update manually.
///////////////////////

void LaunchUpdater();
int IsUpdateAvailable();
void NotifyUser();
