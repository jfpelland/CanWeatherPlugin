
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <memory>
#include <unordered_map>
#include <pugixml.hpp>

#include "MeasureType.hpp"
#include "WeatherElement.hpp"

class WeatherInfo
{
private:
	std::unordered_map<MeasureType, std::shared_ptr<WeatherElement>> info;
	bool errorState;

public:
	WeatherInfo();

	std::shared_ptr<WeatherElement> operator[](MeasureType mt);

	bool contains(MeasureType mt) { return info.contains(mt); }

	void addString(std::string s, MeasureType mt);
	void addString(const pugi::xml_node& node, MeasureType mt);
	void addNumber(const pugi::xml_node& node, MeasureType mt);
	void addNumberWithAttribute(const pugi::xml_node& node, MeasureType mt_attr, MeasureType mt_num, const pugi::char_t* attr);

	void setErrorState(bool state) { errorState = state; }
	bool isErrorState() { return errorState; }

	std::wstring prettyPrint() const;
};
