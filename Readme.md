﻿# CanWeatherPlugin for Rainmeter
CanWeatherPlugin is a simple plugin for Rainmeter that takes weather information provided by Environment and Climate Change Canada and exposes it in a simple, easy to use format.

## Usage
CanWeatherPlugin's usage is similar to Rainmeter's WebParser plugin. You want to first start by defining a main or parent measure, as such:
 
```
[MeasureWeather]
Measure=Plugin
Plugin=CanWeatherPlugin
Source=https://dd.weather.gc.ca/citypage_weather/xml/NS/s0000096_e.xml
RefreshTime=600
DynamicVariables=1
```

And then sub or child measures that point to a parent measure. Example:

```
[MeasureProvince]
Measure=Plugin
Plugin=CanWeatherPlugin
Source=[MeasureWeather]
Data=Province
```

All child measures will return string values. Some may return numerical values when appropriate.

### Parent measure options
The parent measure supports two options: Source and RefreshTime.

**Source** is a URL pointing containing the weather data. Finding the location nearest you is a two-step process.

First, find your town or area here: https://collaboration.cmc.ec.gc.ca/cmc/cmos/public_doc/msc-data/citypage-weather/site_list_en.geojson. The relevant value is the eight character alphanumeric sequence following "Codes".

Copy that value and then open this link: https://dd.weather.gc.ca/citypage_weather/xml/. Choose your province and then search for the aforementioned code in the list. There's two options, one ending in _e for english text and the other ending in _f for french text.

**RefreshTime** is the time, in seconds, until the parent measure will check the source URL for updates. Default is 600 seconds (10 minutes). Lowest allowed is 60 seconds (1 minute). Values lower than 60 will be overriden to 60 seconds.

The string value returned by a parent measure is the source URL and the numerical value returned is the number of seconds until the next update.

### Child measure options
Child measures support two options: Source and Data.

**Source** should be a reference to a parent measure.

**Data** is the information that is to be retrieved from the parent measure.

The following is a list of all accepted values:

* ReportTimestamp
  * The time the report was generated by EnvironmentCanada.
* Province
* City
* ConditionText
  * Brief description of the current weather.
* CurrentIcon
  * Icon code for current weather. More details can found here: https://collaboration.cmc.ec.gc.ca/cmc/cmos/public_doc/msc-data/citypage-weather/
* CurrentTemp
  * Current temperature in celsius.
* PressureUnits
  * Units used for atmospheric pressure.
* PressureValue
  * Current atmospheric pressure.
* HumidityUnits
  * Units used for relative humidity.
* HumidityValue
  * Current relative humidity.
* WindUnits
  * Units used for wind speed.
* WindSpeed
  * Current wind speed.
* WindDirection
  * Current wind direction.
* PrecipitationUnits
  * Units used for chance of precipitation.
* PrecipitationChance
  * Today/Tonight's chance of precipitation.
* PrecipitationText
  * Brief text describing the above.
* TodayTonightString
  * Text string denoting whether or not the immediate weather forecast is for today or tonight. This will change depending on time of day. Skins can use this to determine whether or not to include forecasts for the current day.
* TodayTonightIcon
  * Icon code for the weather forecast for today/tonight.
* TodayTemp
  * Forecasted high for the current day.
* TonightTemp
  * Forecasted low for the current/oncoming night.
* Day1Name
  * Tomorrow's day.
* Day1Icon
  * Icon code for tomorrow's weather forecast. Uses icon code for the day rather than the night.
* Day1High
  * Forecasted high for tomorrow.
* Day1Low
  * Forecasted low for tomorrow.
* Day2Name
  * Same as above but for the day after tomorrow.
* Day2Icon
* Day2High
* Day2Low
* Day3Name
* Day3Icon
* Day3High
* Day3Low
* Day4Name
* Day4Icon
* Day4High
* Day4Low
* SunriseTime
  * Timestamp denoting the expected sunrise time.
* SunsetTime
  * Timestamp denoting the expected sunset time.
* WarningURL
  * URL for any weather or climate related warnings issued by EnvironmentCanada. Usually for things like severe weather, poor air quality, etc.
* WarningText
  * Brief text description of all issued warnings, along with their assigned priority. If multiple warnings have been issued, they will be delimited by a pipe symbol '|'.

All timestamps are given in UTC+0. Timestamp format is %Y%m%d%H%M%S. See the format codes section of this webpage for more details: https://docs.rainmeter.net/manual/measures/time/

## Compiling
The following libraries are required for compilation: libcurl, pugixml, and, shockingly, Rainmeter's SDK. The project is configured to statically link with these libraries.

rainmeter-plugin-sdk should be located in the same parent folder as CanWeatherPlugin. File structure should look something like this:
```
└── CodingFolder\
    ├── CanWeatherPlugin\
    │   └── ...
    └── rainmeter-plugin-sdk\
        ├── API\
        │   ├── x32\
        │   │   └── Rainmeter.lib
        │   ├── x64\
        │   │   └── Rainmeter.lib
        │   ├── RainmeterAPI.h
        │   └── ...
        └── ...
```

libcurl and pugixml should be installed via vcpkg. vcpkg can be installed by following the instructions found in this webpage: https://vcpkg.io/en/getting-started.html

Once vcpkg is installed, run the following command:
```
vcpkg.exe install curl:x64-windows-static-md curl:x86-windows-static-md pugixml:x64-windows-static-md pugixml:x86-windows-static-md
```
## Changelog
### 1.0:
* Initial release.

# License
Unless otherwise noted, this repository is licensed under the Boost Software License v1.0. See accompanying file LICENSE_1_0.txt or copy at https://www.boost.org/LICENSE_1_0.txt.

# Notice

## Data Source
The data used by this plugin is sourced from Environment and Climate Change Canada. Please see the full license text for more details: https://eccc-msc.github.io/open-data/licence/readme_en/

## pugixml
This software uses the pugixml library (http://pugixml.org). pugixml is Copyright (C) 2006-2018 Arseny Kapoulkine.

## libcurl
This software uses the libcurl library (https://curl.se/). The following notice is included to satisfy distribution terms: 

COPYRIGHT AND PERMISSION NOTICE

Copyright (c) 1996 - 2023, Daniel Stenberg, daniel@haxx.se, and many contributors, see the THANKS file.

All rights reserved.

Permission to use, copy, modify, and distribute this software for any purpose with or without fee is hereby granted, provided that the above copyright notice and this permission notice appear in all copies.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of a copyright holder shall not be used in advertising or otherwise to promote the sale, use or other dealings in this Software without prior written authorization of the copyright holder.

-----------
