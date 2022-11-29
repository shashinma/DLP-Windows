#include "ActivitySecure.h"
#include <windows.h>


void HideWindow() {
    HWND hWindow = GetConsoleWindow();
    if (hWindow != NULL) {
        if (IsWindowVisible(hWindow) != 0) {
            ShowWindow(hWindow, SW_HIDE);
        }
        CloseHandle(hWindow);
    }
}

