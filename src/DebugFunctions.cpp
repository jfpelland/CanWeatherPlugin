
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifdef _DEBUG

#include "DebugFunctions.hpp"
#include <iostream>
#include <string>

LPCWSTR RmReadString(void* rm, LPCWSTR option, LPCWSTR defValue, BOOL replaceMeasures)
{
	switch((int)rm)
	{
	case 1:
		if(option == L"Source")
		{
			return L"";
		}
		else if(option == L"RefreshTime")
		{
			return L"600";
		}
		break;
	case 2:
		if(option == L"Source")
		{
			return L"[WeatherParent]";
		}
		else if(option == L"Data")
		{
			return L"WindSpeedd";
		}
		break;
	}
	return defValue;
}

int RmReadInt(void* rm, LPCWSTR option, int defValue)
{
	switch((int)rm)
	{
	case 1:
		if(option == L"RefreshTime")
		{
			return 600;
		}
		break;
	}
	return defValue;
}

double RmReadDouble(void* rm, LPCWSTR option, double defValue)
{
	switch((int)rm)
	{
	case 1:
		if(option == L"RefreshTime")
		{
			return 600;
		}
		break;
	}
	return defValue;
}

LPCWSTR RmReadPath(void* rm, LPCWSTR option, LPCWSTR defValue)
{
	return defValue;
}

void RmExecute(void* skin, LPCWSTR command)
{

}

LPCWSTR RmReplaceVariables(void* rm, LPCWSTR str)
{
	return L"No.";
}

LPCWSTR RmGetMeasureName(void* rm)
{
	switch((int)rm)
	{
	case 1:
		return L"WeatherParent";
		break;
	case 2:
		return L"WeatherChild";
		break;
	}
	return L"";
}

void* RmGetSkin(void* rm)
{
	return nullptr;
}

LPCWSTR RmGetSkinName(void* rm)
{
	return L"WeatherSkin";
}

HWND RmGetSkinWindow(void* rm)
{
	return nullptr;
}

LPCWSTR GetSettingsFile()
{
	return L"No.";
}

void RmLog(void* rm, int level, LPCWSTR message)
{
	std::wcout << L"RmLog: Level=" << std::to_wstring(level) << L", message=\"" << message << L"\"" << std::endl;
}

void RmLogF(void* rm, int level, LPCWSTR format, ...)
{
	
}

#endif // _DEBUG
