
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <string>
#include <Windows.h>

class WeatherElement
{
public:
	LPCWSTR strValue;
	double numValue;

private:
	bool _hasNum = false;

public:
	WeatherElement() : WeatherElement("", 0.0, false) {}
	WeatherElement(std::string _s) : WeatherElement(_s, 0.0, false) {}
	WeatherElement(std::string _s, double _d) : WeatherElement(_s, _d, true) {}
	~WeatherElement();

	void setStringValue(std::wstring newStr);
	void setStringOnly() { _hasNum = false; }

	bool hasNumber() const { return _hasNum; }
	std::wstring prettyPrint() const;

private:
	WeatherElement(std::string _s, double _d, bool _hasNum);
};
