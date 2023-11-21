
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <algorithm>
#include <string>

#include "MeasureType.hpp"
#include "WeatherInfo.hpp"

typedef void* MeasurePtr;
typedef void* SkinPtr;

constexpr int64_t MinUpdateTime = 60;
constexpr int64_t DefaultUpdateTime = 600;

class MeasureBase
{
public:
	std::wstring source;
	MeasureType type = MeasureType::None;
	MeasurePtr rmPtr;
	SkinPtr skinPtr;

protected:
	MeasureBase(MeasureType _t, std::wstring _s, MeasurePtr _rmPtr, SkinPtr _skinPtr)
		: type{ _t }, source{ _s }, rmPtr{ _rmPtr }, skinPtr{ _skinPtr } {}

public:
	bool isParentMeasure() { return type == MeasureType::Parent; }
};

class MeasureParent : public MeasureBase
{
private:
	int64_t lastUpdate;
	int64_t updateFrequency; // in seconds -- default = 10 minutes, lowest is one minute

public:
	WeatherInfo wdata{};

	MeasureParent(std::wstring _source, MeasurePtr _rmPtr, SkinPtr _skinPtr) :
		MeasureBase(MeasureType::Parent, _source, _rmPtr, _skinPtr),
		updateFrequency{}, lastUpdate{} {}

	void setUpdateFrequency(int64_t period) { updateFrequency = std::max(period, MinUpdateTime); }
	uint64_t getLastUpdateTime() { return lastUpdate; }
	uint64_t timeUntilNextUpdate();
	void forceUpdate() { lastUpdate = 0; }
	bool needsUpdate();
	void updateTime();
};

class MeasureChild : public MeasureBase
{
public:
	MeasureChild(std::wstring _source, MeasurePtr _rmPtr, SkinPtr _skinPtr)
		: MeasureBase(MeasureType::None, _source, _rmPtr, _skinPtr) {}
};
