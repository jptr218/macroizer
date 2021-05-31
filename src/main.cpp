#include "macroizer.h"

int main(int argc, char* argv[]) {
	if (argc < 3) {
		cout << "Usage:" << endl << "macroizer record [macro]" << endl << "macroizer play [macro]" << endl << "macroizer clear [macro]" << endl;
		return 1;
	}

	if (string(argv[1]) == "record") {
		TCHAR t_fileName[MAX_PATH];
		GetModuleFileName(NULL, t_fileName, MAX_PATH);
		wstring w_fileName(&t_fileName[0]);
		string dir(w_fileName.begin(), w_fileName.end());
		dir = dir.substr(0, dir.size() - 13);
		
		fclose(fopen((dir + argv[2]).c_str(), "w"));
		record(dir + argv[2]);
		ShowWindow(GetConsoleWindow(), SW_HIDE);
		MessageBoxA(GetConsoleWindow(), "Press OK when you would like to stop recording", "Macroizer", MB_TOPMOST);
		stop_record();
		ShowWindow(GetConsoleWindow(), SW_SHOW);
	}
	else if (string(argv[1]) == "play") {
		macro m = load(argv[2]);
		play(m);
	}
	else if (string(argv[1]) == "clear") {
		fclose(fopen(argv[2], "w"));
	}
	
	return 1;
}