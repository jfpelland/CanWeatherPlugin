
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "WeatherElement.hpp"

#include <strsafe.h>

using std::string;
using std::wstring;

WeatherElement::WeatherElement(string _s, double _d, bool _hasNum)
	: numValue{ _d }, _hasNum{ _hasNum }
{
	int numWchars = MultiByteToWideChar(CP_UTF8, 0, _s.c_str(), -1, nullptr, 0);
	strValue = new WCHAR[numWchars];
	MultiByteToWideChar(CP_UTF8, 0, _s.c_str(), -1, const_cast<LPWSTR>(strValue), numWchars);
}

WeatherElement::~WeatherElement()
{
	if(strValue)
	{
		delete[] strValue;
	}
}

void WeatherElement::setStringValue(std::wstring newStr)
{
	if(strValue)
	{
		delete[] strValue;
	}
	auto newSize = newStr.length() + 1;
	strValue = new WCHAR[newSize];
	StringCchCopyW(const_cast<LPWSTR>(strValue), newSize, newStr.c_str());
}

wstring WeatherElement::prettyPrint() const
{
	wstring output = L"[\"" + static_cast<wstring>(strValue) + L"\"";
	if(_hasNum)
	{
		output += L", " + std::to_wstring(numValue);
	}
	output += L"]";
	return output;
}
