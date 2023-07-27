
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "WeatherInfo.hpp"

using std::string;
using std::wstring;

using pugi::xml_node;

WeatherInfo::WeatherInfo()
{
	errorState = false;
	info[MeasureType::None] = new WeatherElement("None");
	info[MeasureType::Error] = new WeatherElement("---");
}

WeatherInfo::~WeatherInfo()
{
	for(auto const &[key, val] : info)
	{
		if(val)
		{
			delete val;
		}
	}
}

WeatherElement* WeatherInfo::operator[](MeasureType mt)
{
	if(isErrorState())
	{
		return info[MeasureType::Error];
	}
	return info.contains(mt) ? info[mt] : info[MeasureType::None];
}

void WeatherInfo::addString(string s, MeasureType mt)
{
	info[mt] = new WeatherElement(s);
}

void WeatherInfo::addString(const xml_node& node, MeasureType mt)
{
	info[mt] = new WeatherElement(node.child_value());
}

void WeatherInfo::addNumber(const xml_node& node, MeasureType mt)
{
	info[mt] = new WeatherElement(node.child_value(), node.text().as_float());
}

void WeatherInfo::addNumberWithAttribute(const xml_node& node, MeasureType mt_attr, MeasureType mt_num, const pugi::char_t* attr)
{
	info[mt_attr] = new WeatherElement(node.attribute(attr).value());
	info[mt_num] = new WeatherElement(node.child_value(), node.text().as_double());
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
