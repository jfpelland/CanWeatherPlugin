
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <string>
#include "WeatherInfo.hpp"

enum class DownloadErrorCode
{
	OK = 0,
	FILE_IO_ERROR,
	CURL_INIT_FAIL,
	CURL_ERROR,
};

DownloadErrorCode downloadData(const char* url, std::string& output);

pugi::xml_parse_result parseXMLData(std::string& xmlData, WeatherInfo& weatherInfo);
