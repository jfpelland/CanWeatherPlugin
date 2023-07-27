
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

// Veeery basic implementations of Rainmeter's plugin API
// so that plugin logic can be tested as a command-line app.

#pragma once

#ifdef _DEBUG

#include <Windows.h>

#define PLUGIN_EXPORT

enum LOGLEVEL
{
	LOG_ERROR = 1,
	LOG_WARNING = 2,
	LOG_NOTICE = 3,
	LOG_DEBUG = 4
};

LPCWSTR RmReadString(void* rm, LPCWSTR option, LPCWSTR defValue, BOOL replaceMeasures = 1);

int RmReadInt(void* rm, LPCWSTR option, int defValue);

double RmReadDouble(void* rm, LPCWSTR option, double defValue);

LPCWSTR RmReadPath(void* rm, LPCWSTR option, LPCWSTR defValue);

void RmExecute(void* skin, LPCWSTR command);

LPCWSTR RmReplaceVariables(void* rm, LPCWSTR str);

LPCWSTR RmGetMeasureName(void* rm);

void* RmGetSkin(void* rm);

LPCWSTR RmGetSkinName(void* rm);

HWND RmGetSkinWindow(void* rm);

LPCWSTR GetSettingsFile();

void RmLog(void* rm, int level, LPCWSTR message);

void RmLogF(void* rm, int level, LPCWSTR format, ...);

#endif // _DEBUG
