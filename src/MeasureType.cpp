
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "MeasureType.hpp"

inline std::map<MeasureType, std::wstring> measureTypeToString{
	{MeasureType::ReportTimestamp, L"ReportTimestamp"},
	{MeasureType::Province, L"Province"},
	{MeasureType::City, L"City"},
	{MeasureType::ConditionStr, L"ConditionText"},
	{MeasureType::CurrentIcon, L"CurrentIcon"},
	{MeasureType::CurrentTemp, L"CurrentTemp"},
	{MeasureType::PressureUnits, L"PressureUnits"},
	{MeasureType::PressureValue, L"PressureValue"},
	{MeasureType::HumidityUnits, L"HumidityUnits"},
	{MeasureType::HumidityValue, L"HumidityValue"},
	{MeasureType::WindUnits, L"WindUnits"},
	{MeasureType::WindSpeed, L"WindSpeed"},
	{MeasureType::WindDirection, L"WindDirection"},
	{MeasureType::PrecipUnits, L"PrecipitationUnits"},
	{MeasureType::PrecipChance, L"PrecipitationChance"},
	{MeasureType::PrecipDescription, L"PrecipitationText"},
	{MeasureType::TodayTonightString, L"TodayTonightString"},
	{MeasureType::TodayTonightIcon, L"TodayTonightIcon"},
	{MeasureType::TodayTemp, L"TodayTemp"},
	{MeasureType::TonightTemp, L"TonightTemp"},
	{MeasureType::Day1Name, L"Day1Name"},
	{MeasureType::Day1Icon, L"Day1Icon"},
	{MeasureType::Day1High, L"Day1High"},
	{MeasureType::Day1Low, L"Day1Low"},
	{MeasureType::Day2Name, L"Day2Name"},
	{MeasureType::Day2Icon, L"Day2Icon"},
	{MeasureType::Day2High, L"Day2High"},
	{MeasureType::Day2Low, L"Day2Low"},
	{MeasureType::Day3Name, L"Day3Name"},
	{MeasureType::Day3Icon, L"Day3Icon"},
	{MeasureType::Day3High, L"Day3High"},
	{MeasureType::Day3Low, L"Day3Low"},
	{MeasureType::Day4Name, L"Day4Name"},
	{MeasureType::Day4Icon, L"Day4Icon"},
	{MeasureType::Day4High, L"Day4High"},
	{MeasureType::Day4Low, L"Day4Low"},
	{MeasureType::SunriseTime, L"SunriseTime"},
	{MeasureType::SunsetTime, L"SunsetTime"},
	{MeasureType::WarningURL, L"WarningURL"},
	{MeasureType::WarningDescription, L"WarningText"},
};

inline std::map<std::wstring, MeasureType> stringToMeasureType{
	{L"ReportTimestamp", MeasureType::ReportTimestamp},
	{L"Province", MeasureType::Province},
	{L"City", MeasureType::City},
	{L"ConditionText", MeasureType::ConditionStr},
	{L"CurrentIcon", MeasureType::CurrentIcon},
	{L"CurrentTemp", MeasureType::CurrentTemp},
	{L"PressureUnits", MeasureType::PressureUnits},
	{L"PressureValue", MeasureType::PressureValue},
	{L"HumidityUnits", MeasureType::HumidityUnits},
	{L"HumidityValue", MeasureType::HumidityValue},
	{L"WindUnits", MeasureType::WindUnits},
	{L"WindSpeed", MeasureType::WindSpeed},
	{L"WindDirection", MeasureType::WindDirection},
	{L"PrecipitationUnits", MeasureType::PrecipUnits},
	{L"PrecipitationChance", MeasureType::PrecipChance},
	{L"PrecipitationText", MeasureType::PrecipDescription},
	{L"TodayTonightString", MeasureType::TodayTonightString},
	{L"TodayTonightIcon", MeasureType::TodayTonightIcon},
	{L"TodayTemp", MeasureType::TodayTemp},
	{L"TonightTemp", MeasureType::TonightTemp},
	{L"Day1Name", MeasureType::Day1Name},
	{L"Day1Icon", MeasureType::Day1Icon},
	{L"Day1High", MeasureType::Day1High},
	{L"Day1Low", MeasureType::Day1Low},
	{L"Day2Name", MeasureType::Day2Name},
	{L"Day2Icon", MeasureType::Day2Icon},
	{L"Day2High", MeasureType::Day2High},
	{L"Day2Low", MeasureType::Day2Low},
	{L"Day3Name", MeasureType::Day3Name},
	{L"Day3Icon", MeasureType::Day3Icon},
	{L"Day3High", MeasureType::Day3High},
	{L"Day3Low", MeasureType::Day3Low},
	{L"Day4Name", MeasureType::Day4Name},
	{L"Day4Icon", MeasureType::Day4Icon},
	{L"Day4High", MeasureType::Day4High},
	{L"Day4Low", MeasureType::Day4Low},
	{L"SunriseTime", MeasureType::SunriseTime},
	{L"SunsetTime", MeasureType::SunsetTime},
	{L"WarningURL", MeasureType::WarningURL},
	{L"WarningText", MeasureType::WarningDescription},
};

std::wstring getStringFromType(MeasureType mt)
{
	return measureTypeToString.contains(mt) ? measureTypeToString[mt] : L"";
}

MeasureType getTypeFromString(std::wstring s)
{
	return stringToMeasureType.contains(s) ? stringToMeasureType[s] : MeasureType::None;
}
