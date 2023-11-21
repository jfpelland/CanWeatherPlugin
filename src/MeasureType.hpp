
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <string>

enum class MeasureType
{
	None,
	Error,
	Parent,
	ReportTimestamp,
	Province,
	City,
	ConditionStr,
	CurrentIcon,
	CurrentTemp,
	PressureUnits,
	PressureValue,
	HumidityUnits,
	HumidityValue,
	WindUnits,
	WindSpeed,
	WindDirection,
	PrecipUnits,
	PrecipChance,
	PrecipDescription,
	TodayTonightString,
	TodayTonightIcon,
	TodayTemp,
	TonightTemp,
	Day1Name,
	Day1Icon,
	Day1High,
	Day1Low,
	Day2Name,
	Day2Icon,
	Day2High,
	Day2Low,
	Day3Name,
	Day3Icon,
	Day3High,
	Day3Low,
	Day4Name,
	Day4Icon,
	Day4High,
	Day4Low,
	SunriseTime,
	SunsetTime,
	WarningURL,
	WarningDescription,
};

std::wstring getStringFromType(MeasureType mt);
MeasureType getTypeFromString(std::wstring s);
