#pragma once
#pragma comment(lib, "macroizer_dll.lib")

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
using namespace std;

struct macro_elem {
	int type;
	int time;
	int key;
	int button;
	int x;
	int y;
};

#define macro vector<macro_elem>

void play(macro m);
macro load(string f);

extern "C"
{
	__declspec(dllimport) int record(string p);
	__declspec(dllimport) int stop_record();
}