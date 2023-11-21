
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "WeatherElement.hpp"

using std::wstring;

wstring WeatherElement::prettyPrint() const
{
	auto output = L"[\"" + static_cast<wstring>(strValue.GetString()) + L"\"";
	if(_hasNum)
	{
		output += L", " + std::to_wstring(numValue);
	}
	output += L"]";
	return output;
}
