#ifndef _MACROIZER_H_
#define _MACROIZER_H_

extern "C"
{
	__declspec(dllexport) int record(std::string p);
	__declspec(dllexport) int stop_record();
}

#endif