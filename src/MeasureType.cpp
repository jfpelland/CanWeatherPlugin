
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "MeasureType.hpp"

#include <boost/assign.hpp>
#include <boost/bimap.hpp>
#include <boost/bimap/unordered_set_of.hpp>

using boost::bimap;
using boost::bimaps::unordered_set_of;
using std::wstring;

typedef bimap<unordered_set_of<MeasureType>, unordered_set_of<wstring>> TypeMap;

const TypeMap tmap = boost::assign::list_of<TypeMap::relation>
	(MeasureType::ReportTimestamp, L"ReportTimestamp")
	(MeasureType::Province, L"Province")
	(MeasureType::City, L"City")
	(MeasureType::ConditionStr, L"ConditionText")
	(MeasureType::CurrentIcon, L"CurrentIcon")
	(MeasureType::CurrentTemp, L"CurrentTemp")
	(MeasureType::PressureUnits, L"PressureUnits")
	(MeasureType::PressureValue, L"PressureValue")
	(MeasureType::HumidityUnits, L"HumidityUnits")
	(MeasureType::HumidityValue, L"HumidityValue")
	(MeasureType::WindUnits, L"WindUnits")
	(MeasureType::WindSpeed, L"WindSpeed")
	(MeasureType::WindDirection, L"WindDirection")
	(MeasureType::PrecipUnits, L"PrecipitationUnits")
	(MeasureType::PrecipChance, L"PrecipitationChance")
	(MeasureType::PrecipDescription, L"PrecipitationText")
	(MeasureType::TodayTonightString, L"TodayTonightString")
	(MeasureType::TodayTonightIcon, L"TodayTonightIcon")
	(MeasureType::TodayTemp, L"TodayTemp")
	(MeasureType::TonightTemp, L"TonightTemp")
	(MeasureType::Day1Name, L"Day1Name")
	(MeasureType::Day1Icon, L"Day1Icon")
	(MeasureType::Day1High, L"Day1High")
	(MeasureType::Day1Low, L"Day1Low")
	(MeasureType::Day2Name, L"Day2Name")
	(MeasureType::Day2Icon, L"Day2Icon")
	(MeasureType::Day2High, L"Day2High")
	(MeasureType::Day2Low, L"Day2Low")
	(MeasureType::Day3Name, L"Day3Name")
	(MeasureType::Day3Icon, L"Day3Icon")
	(MeasureType::Day3High, L"Day3High")
	(MeasureType::Day3Low, L"Day3Low")
	(MeasureType::Day4Name, L"Day4Name")
	(MeasureType::Day4Icon, L"Day4Icon")
	(MeasureType::Day4High, L"Day4High")
	(MeasureType::Day4Low, L"Day4Low")
	(MeasureType::SunriseTime, L"SunriseTime")
	(MeasureType::SunsetTime, L"SunsetTime")
	(MeasureType::WarningURL, L"WarningURL")
	(MeasureType::WarningDescription, L"WarningText");

MeasureType getTypeFromString(std::wstring s)
{
	auto result = tmap.right.find(s);
	return result == tmap.right.end() ? MeasureType::None : result->second;
}

std::wstring getStringFromType(MeasureType mt)
{
	auto result = tmap.left.find(mt);
	return result == tmap.left.end() ? L"None" : result->second;
}
