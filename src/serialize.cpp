#include "macroizer.h"

macro load(string f) {
	FILE* fs = fopen(f.c_str(), "rb");
	macro o;
	if (fs == INVALID_HANDLE_VALUE) {
		cout << "The specifed macro does not exist." << endl;
		return macro();
	}
	
	while (!feof(fs)) {
		string s;
		macro_elem ir;

		s += fgetc(fs);
		if (s.c_str()[0] == EOF) {
			break;
		}
		int type = stoi(s);
		s = "";

		fgetc(fs);

		char tmp;
		switch (type + 1) {
			case KEY_EVENT:
				while ((tmp = fgetc(fs)) != '/') {
					s += tmp;
				}

				ir.type = KEY_EVENT;
				ir.time = stoi(s);
				s = "";
				
				while ((tmp = fgetc(fs)) != '/') {
					s += tmp;
				}
				
				ir.key = stoi(s);
				s = "";

				o.push_back(ir);

				break;
			case MOUSE_EVENT:
				int x;
				int y;
				int b;

				while ((tmp = fgetc(fs)) != '/') {
					s += tmp;
				}

				ir.time = stoi(s);
				s = "";

				while ((tmp = fgetc(fs)) != '/') {
					s += tmp;
				}

				b = stoi(s);
				s = "";

				while ((tmp = fgetc(fs)) != '/') {
					s += tmp;
				}
				
				x = stoi(s);
				s = "";

				while ((tmp = fgetc(fs)) != '/') {
					s += tmp;
				}
				
				y = stoi(s);
				s = "";

				ir.type = MOUSE_EVENT;
				ir.button = b;
				ir.x = x;
				ir.y = y;

				o.push_back(ir);

				break;
		}
	}

	return o;
}