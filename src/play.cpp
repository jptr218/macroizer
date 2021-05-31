#include "macroizer.h"

void play(macro m) {
	int t = 0;
	for (macro_elem i : m) {
		Sleep(i.time - t);
		t = i.time;

		INPUT inp;
		ZeroMemory(&inp, sizeof(inp));
		switch (i.type) {
			case KEY_EVENT:
				inp.type = INPUT_KEYBOARD;
				inp.ki.wScan = 0;
				inp.ki.time = 0;
				inp.ki.dwExtraInfo = 0;
				inp.ki.wVk = i.key;
				inp.ki.dwFlags = 0;
				SendInput(1, &inp, sizeof(INPUT));
				inp.ki.dwFlags = KEYEVENTF_KEYUP;
				SendInput(1, &inp, sizeof(INPUT));
				break;
			case MOUSE_EVENT:
				float sw = GetSystemMetrics(SM_CXSCREEN) - 1;
				float sh = GetSystemMetrics(SM_CYSCREEN) - 1;
				
				inp.type = INPUT_MOUSE;
				inp.mi.dx = i.x * (65535.0f / sw);
				inp.mi.dy = i.y * (65535.0f / sh);
				int f = MOUSEEVENTF_LEFTDOWN;
				int f2 = MOUSEEVENTF_LEFTUP;
				if (i.button) {
					f = MOUSEEVENTF_RIGHTDOWN;
					f2 = MOUSEEVENTF_RIGHTUP;
				}
				inp.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | f;
				SendInput(1, &inp, sizeof(INPUT));
				inp.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE | f2;
				SendInput(1, &inp, sizeof(INPUT));
				break;
		}
	}
}