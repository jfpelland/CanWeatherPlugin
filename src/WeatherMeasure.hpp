
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

constexpr int MinUpdateTime = 60;
constexpr int DefaultUpdateTime = 600;

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

public:
	int updateFrequency; // in seconds -- default = 10 minutes, lowest is one minute
	WeatherInfo wdata{};

	MeasureParent(int _seconds, std::wstring _source, MeasurePtr _rmPtr, SkinPtr _skinPtr) :
		MeasureBase(MeasureType::Parent, _source, _rmPtr, _skinPtr),
		updateFrequency{ std::max(_seconds, MinUpdateTime) },
		lastUpdate{ 0 } {}

	uint64_t getLastUpdateTime() { return lastUpdate; }
	uint64_t timeUntilNextUpdate();
	void forceUpdate() { lastUpdate = 0; }
	bool needsUpdate();
	void updateTime();
};

class MeasureChild : public MeasureBase
{
public:
	MeasureChild(MeasureType _t, std::wstring _source, MeasurePtr _rmPtr, SkinPtr _skinPtr)
		: MeasureBase(_t, _source, _rmPtr, _skinPtr) {}
};