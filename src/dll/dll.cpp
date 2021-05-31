#include "pch.h"

HINSTANCE hi;
HHOOK mouse;
HHOOK keyboard;

std::string path;
DWORD firstInput = 0;

int __stdcall DllMain(HINSTANCE hInst, DWORD fdwReason, void* pReserved)
{
    hi = hInst;
    return 1;
}

LRESULT __stdcall mProc(int nCode, WPARAM wParam, LPARAM lParam) {
    MOUSEHOOKSTRUCT* mHook = (MOUSEHOOKSTRUCT*)lParam;
    if (mHook != NULL) {
        if (wParam == WM_LBUTTONDOWN || wParam == WM_RBUTTONDOWN)
        {
            FILE* f = fopen(path.c_str(), "a");
            int n = 0 ? 1 : wParam == WM_RBUTTONDOWN;
            int elapsed = GetTickCount() - firstInput;
            std::string s = "1/" + std::to_string(elapsed) + "/" + std::to_string(n) + "/" + std::to_string(mHook->pt.x) + "/" + std::to_string(mHook->pt.y) + "/";
            fwrite(s.c_str(), 1, s.length(), f);
            fclose(f);
        }
    }
    return CallNextHookEx(mouse, nCode, wParam, lParam);
}

LRESULT __stdcall kProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (wParam == WM_KEYDOWN) {
        int kc = ((KBDLLHOOKSTRUCT*)lParam)->vkCode;
        int elapsed = GetTickCount() - firstInput;
        FILE* f = fopen(path.c_str(), "a");
        std::string s = "0/" + std::to_string(elapsed) + "/" + std::to_string(kc) + "/";
        fwrite(s.c_str(), 1, s.length(), f);
        fclose(f);
    }
    return CallNextHookEx(mouse, nCode, wParam, lParam);
}

extern "C"
{
    int record(std::string p) {
        path = p;
        firstInput = GetTickCount();
        mouse = SetWindowsHookExW(WH_MOUSE, mProc, hi, NULL);
        keyboard = SetWindowsHookExW(WH_KEYBOARD_LL, kProc, hi, NULL);
        return GetLastError();
    }
    int stop_record() {
        UnhookWindowsHookEx(mouse);
        UnhookWindowsHookEx(keyboard);
        return GetLastError();
    }
}