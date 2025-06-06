#pragma once
#include <Windows.h>
#include<string>
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <vector>

using namespace std;

void DebugOut(wchar_t* fmt, ...);

vector<string> split(string line, string delimeter = " ");
wstring ToWSTR(string st);
LPCWSTR ToLPCWSTR(string st);
