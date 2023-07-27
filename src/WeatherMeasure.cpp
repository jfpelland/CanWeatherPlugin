
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "WeatherMeasure.hpp"

#include <chrono>

using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;

uint64_t MeasureParent::timeUntilNextUpdate()
{
	auto currentTime = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
	return (lastUpdate + updateFrequency) - currentTime;
}

bool MeasureParent::needsUpdate()
{
	auto currentTime = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
	return (lastUpdate + updateFrequency) <= currentTime;
}

void MeasureParent::updateTime()
{
	lastUpdate = duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
}
