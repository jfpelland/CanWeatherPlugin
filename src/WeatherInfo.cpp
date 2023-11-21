
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "WeatherInfo.hpp"

using std::make_shared;
using std::shared_ptr;
using std::string;
using std::wstring;

using pugi::xml_node;

WeatherInfo::WeatherInfo()
{
	errorState = false;
	info[MeasureType::None] = make_shared<WeatherElement>("None");
	info[MeasureType::Error] = make_shared<WeatherElement>("---");
}

shared_ptr<WeatherElement> WeatherInfo::operator[](MeasureType mt)
{
	if(isErrorState())
	{
		return info[MeasureType::Error];
	}
	return info.contains(mt) ? info[mt] : info[MeasureType::None];
}

void WeatherInfo::addString(string s, MeasureType mt)
{
	info[mt] = make_shared<WeatherElement>(s);
}

void WeatherInfo::addString(const xml_node& node, MeasureType mt)
{
	info[mt] = make_shared<WeatherElement>(node.child_value());
}

void WeatherInfo::addNumber(const xml_node& node, MeasureType mt)
{
	info[mt] = make_shared<WeatherElement>(node.child_value(), node.text().as_float());
}

void WeatherInfo::addNumberWithAttribute(const xml_node& node, MeasureType mt_attr, MeasureType mt_num, const pugi::char_t* attr)
{
	info[mt_attr] = make_shared<WeatherElement>(node.attribute(attr).value());
	info[mt_num] = make_shared<WeatherElement>(node.child_value(), node.text().as_double());
}

wstring WeatherInfo::prettyPrint() const
{
	wstring output = L"WeatherData[";
	for(auto const& [key, val] : info)
	{
		output += L"\n\t" + getStringFromType(key) + L":\t\t" + val->prettyPrint();
	}
	output += L"\n]";
	return output;
}
