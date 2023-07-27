
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "WeatherIO.hpp"

#include <curl\curl.h>
#include <pugixml.hpp>

using std::string;

using pugi::xml_attribute;
using pugi::xml_document;
using pugi::xml_node;
using pugi::xml_parse_result;

size_t curlWriteCallback(char *ptr, size_t size, size_t nmemb, void *userData)
{
	size_t realsize = size * nmemb;
	string* mem = static_cast<std::string*>(userData);
	mem->append(ptr, realsize);
	return realsize;
}

#pragma warning(disable: 26812)
DownloadErrorCode downloadData(const char* url, string& output)
{
	DownloadErrorCode errorCode = DownloadErrorCode::OK;
	CURL* curl = curl_easy_init();

	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curlWriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output);
		auto result = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
		if(result)
		{
			errorCode = DownloadErrorCode::CURL_ERROR;
		}
	}
	else
	{
		errorCode = DownloadErrorCode::CURL_INIT_FAIL;
	}
	return errorCode;
}
#pragma warning(default: 26812)

// Can't pass string literals to templates
constexpr char reportTimeStr[] = "xmlCreation";
constexpr char sunriseStr[] = "sunrise";
constexpr char sunsetStr[] = "sunset";

template <char const* c>
bool dateTimePred(xml_node n)
{
	return !strcmp(n.attribute("name").value(), c) && (n.attribute("UTCOffset").as_int() == 0);
};

pugi::xml_parse_result parseXMLData(string& xmlFile, WeatherInfo& weatherInfo)
{
	xml_document doc;
	xml_node node;

	auto result = doc.load_string(xmlFile.c_str());
	if(result)
	{
		auto root = doc.child("siteData");
		weatherInfo.addString(root.find_child(dateTimePred<reportTimeStr>).child("timeStamp"), MeasureType::ReportTimestamp);

		node = root.child("location");
		if(!node.first_child().empty())
		{
			weatherInfo.addString(node.child("province"), MeasureType::Province);
			weatherInfo.addString(node.child("name"), MeasureType::City);
		}

		node = root.child("warnings");
		if(!node.first_child().empty())
		{
			weatherInfo.addString(node.attribute("url").value(), MeasureType::WarningURL);
			string info = "";
			for(auto const &warn : node.children("event"))
			{
				// concatenate warning info. Delimited by pipe '|'
				info += warn.attribute("description").value();
				info += " (";
				info += warn.attribute("priority").value();
				info += " priority)|";
			}
			info.pop_back(); // remove last |
			weatherInfo.addString(info, MeasureType::WarningDescription);
		}

		node = root.child("currentConditions");
		if(!node.first_child().empty())
		{
			weatherInfo.addString(node.child("condition"), MeasureType::ConditionStr);
			weatherInfo.addNumber(node.child("iconCode"), MeasureType::CurrentIcon);
			weatherInfo.addNumber(node.child("temperature"), MeasureType::CurrentTemp);
			weatherInfo.addNumberWithAttribute(node.child("pressure"), MeasureType::PressureUnits, MeasureType::PressureValue, "units");
			weatherInfo.addNumberWithAttribute(node.child("relativeHumidity"), MeasureType::HumidityUnits, MeasureType::HumidityValue, "units");
			weatherInfo.addNumberWithAttribute(node.child("wind").child("speed"), MeasureType::WindUnits, MeasureType::WindSpeed, "units");
			weatherInfo.addString(node.child("wind").child("direction"), MeasureType::WindDirection);
		}

		node = root.child("forecastGroup");
		if(!node.first_child().empty())
		{
			auto forecasts = node.children("forecast").begin();
			weatherInfo.addNumber(forecasts->child("abbreviatedForecast").child("iconCode"), MeasureType::TodayTonightIcon);
			weatherInfo.addNumberWithAttribute(forecasts->child("abbreviatedForecast").child("pop"), MeasureType::PrecipUnits, MeasureType::PrecipChance, "units");
			weatherInfo.addString(forecasts->child("abbreviatedForecast").child("textSummary"), MeasureType::PrecipDescription);
			string period = forecasts->child("period").attribute("textForecastName").value();
			weatherInfo.addString(period, MeasureType::TodayTonightString);
			if(period == "Today") // Needs special treatment because "Today" isn't always present
			{
				weatherInfo.addNumber(forecasts->child("temperatures").child("temperature"), MeasureType::TodayTemp);
				forecasts++;
			}
			else // Tonight
			{
				weatherInfo.addString("---", MeasureType::TodayTemp);
			}
			weatherInfo.addNumber(forecasts->child("temperatures").child("temperature"), MeasureType::TonightTemp);
			forecasts++;
			// Day 1
			weatherInfo.addString(forecasts->child("period"), MeasureType::Day1Name);
			weatherInfo.addNumber(forecasts->child("abbreviatedForecast").child("iconCode"), MeasureType::Day1Icon);
			weatherInfo.addNumber(forecasts->child("temperatures").child("temperature"), MeasureType::Day1High);
			forecasts++;
			weatherInfo.addNumber(forecasts->child("temperatures").child("temperature"), MeasureType::Day1Low);
			forecasts++;
			// Day 2
			weatherInfo.addString(forecasts->child("period"), MeasureType::Day2Name);
			weatherInfo.addNumber(forecasts->child("abbreviatedForecast").child("iconCode"), MeasureType::Day2Icon);
			weatherInfo.addNumber(forecasts->child("temperatures").child("temperature"), MeasureType::Day2High);
			forecasts++;
			weatherInfo.addNumber(forecasts->child("temperatures").child("temperature"), MeasureType::Day2Low);
			forecasts++;
			// Day 3
			weatherInfo.addString(forecasts->child("period"), MeasureType::Day3Name);
			weatherInfo.addNumber(forecasts->child("abbreviatedForecast").child("iconCode"), MeasureType::Day3Icon);
			weatherInfo.addNumber(forecasts->child("temperatures").child("temperature"), MeasureType::Day3High);
			forecasts++;
			weatherInfo.addNumber(forecasts->child("temperatures").child("temperature"), MeasureType::Day3Low);
			forecasts++;
			// Day 4
			weatherInfo.addString(forecasts->child("period"), MeasureType::Day4Name);
			weatherInfo.addNumber(forecasts->child("abbreviatedForecast").child("iconCode"), MeasureType::Day4Icon);
			weatherInfo.addNumber(forecasts->child("temperatures").child("temperature"), MeasureType::Day4High);
			forecasts++;
			weatherInfo.addNumber(forecasts->child("temperatures").child("temperature"), MeasureType::Day4Low);
		}

		node = root.child("riseSet");
		if(!node.first_child().empty())
		{
			weatherInfo.addString(node.find_child(dateTimePred<sunriseStr>).child("timeStamp"), MeasureType::SunriseTime);
			weatherInfo.addString(node.find_child(dateTimePred<sunsetStr>).child("timeStamp"), MeasureType::SunsetTime);
		}

		// Sanity Checks
		if(lstrlenW(weatherInfo[MeasureType::PrecipChance]->strValue) == 0)
		{
			auto precip = weatherInfo[MeasureType::PrecipChance];
			precip->setStringValue(L"---");
			precip->setStringOnly();
		}
		if(lstrlenW(weatherInfo[MeasureType::WindSpeed]->strValue) == 0)
		{
			auto windSpeed = weatherInfo[MeasureType::WindSpeed];
			windSpeed->setStringValue(L"---");
			windSpeed->setStringOnly();
			weatherInfo[MeasureType::WindDirection]->setStringValue(L"N/A");
		}
		doc.reset();
	}
	return result;
}
