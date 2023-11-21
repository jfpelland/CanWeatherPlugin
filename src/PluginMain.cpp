
//                Copyright JF Pelland 2023.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include <Windows.h>

#ifdef _DEBUG
	#include "DebugFunctions.hpp"
#else
	#include "..\..\rainmeter-plugin-sdk\API\RainmeterAPI.h"
#endif // _DEBUG

#include <unordered_map>
#include <string>
#include <strsafe.h>
#include <atlbase.h>

#include "WeatherIO.hpp"
#include "WeatherMeasure.hpp"

using std::transform;
using std::string;
using std::wstring;
using std::unordered_map;

using pugi::xml_parse_result;

typedef unordered_map<SkinPtr, unordered_map<wstring, MeasureParent*>> ParentTableType;
ParentTableType parentTable{};

bool isParentMeasure(void* data)
{
	return static_cast<MeasureBase*>(data)->isParentMeasure();
}

MeasureParent* getParentMeasure(MeasureBase* mb)
{
	if(isParentMeasure(mb))
	{
		return static_cast<MeasureParent*>(mb);
	}
	return parentTable[mb->skinPtr][mb->source];
}

// Return value uses dynamically allocated memory. Needs to be freed by caller.
// Returns name of measure enclosed in brackets.
LPCWSTR getMeasureName(void *rm)
{
	auto measureName = RmGetMeasureName(rm);
	auto length = wcslen(measureName) + 3; // +3 for '[', ']', and '\0';
	WCHAR* buffer = new WCHAR[length]{ L'[', L'\0' };
	StringCchCatW(buffer, length, measureName);
	buffer[length - 2] = L']';
	buffer[length - 1] = L'\0';
	return buffer;
}

void logDownloadError(DownloadErrorCode dlResult, MeasurePtr rm)
{
	switch(dlResult)
	{
	case DownloadErrorCode::CURL_INIT_FAIL:
		RmLog(rm, LOG_ERROR, L"Error: CURL failed to initiate properly.");
		break;
	case DownloadErrorCode::CURL_ERROR:
		RmLog(rm, LOG_ERROR, L"Error: CURL download failed.");
		break;
	case DownloadErrorCode::FILE_IO_ERROR:
		RmLog(rm, LOG_ERROR, L"Error: How did you get here?");
		break;
	case DownloadErrorCode::OK:
		RmLog(rm, LOG_ERROR, L"Error: No error detected...?");
		break;
	default:
		RmLog(rm, LOG_ERROR, L"Error: Unknown error.");
		break;
	}
}

void logXMLParseError(xml_parse_result& parseResult, MeasurePtr rm)
{
	auto descriptionWideStr = CA2W(parseResult.description());
	RmLog(rm, LOG_ERROR, descriptionWideStr);
}

PLUGIN_EXPORT void Initialize(void** data, MeasurePtr rm)
{
	MeasureBase* measure;
	auto source = RmReadString(rm, L"Source", L"N/A", 0);
	SkinPtr parentSkin = RmGetSkin(rm);

	if(source[0] == '[')
	{
		measure = new MeasureChild(source, rm, parentSkin);
	}
	else
	{
		// parent  measure
		auto measureName = getMeasureName(rm);
		measure = new MeasureParent(source, rm, parentSkin);
		parentTable[parentSkin][measureName] = static_cast<MeasureParent*>(measure);
		delete[] measureName;
	}
	*data = measure;
}

PLUGIN_EXPORT void Reload(void* data, MeasurePtr rm, double* maxValue)
{
	auto mb = static_cast<MeasureBase*>(data);
	mb->source = RmReadString(rm, L"Source", L"N/A", false);

	if(mb->isParentMeasure())
	{
		auto mp = static_cast<MeasureParent*>(mb);
		auto period = RmReadInt(rm, L"RefreshTime", DefaultUpdateTime);
		mp->setUpdateFrequency(period);
	}
	else
	{
		auto dataField = RmReadString(rm, L"Data", L"N/A");
		mb->type = getTypeFromString(dataField);
	}
}

PLUGIN_EXPORT double Update(void* data)
{
	auto mb = static_cast<MeasureBase*>(data);
	if(mb->isParentMeasure())
	{
		auto mp = static_cast<MeasureParent*>(mb);
		if(mp->needsUpdate())
		{
			mp->wdata.setErrorState(true);
			mp->updateTime();

			string xmlFile;
			auto narrowString = CW2A(mp->source.c_str());
			auto dlResult = downloadData(narrowString, xmlFile);
			if(dlResult != DownloadErrorCode::OK)
			{
				logDownloadError(dlResult, mp->rmPtr);
				return 0.0;
			}
			auto parseResult = parseXMLData(xmlFile, mp->wdata);
			if(!parseResult)
			{
				logXMLParseError(parseResult, mp->rmPtr);
				return 0.0;
			}
			mp->wdata.setErrorState(false);
			RmLog(mp->rmPtr, LOG_NOTICE, L"Weather data successfully updated.");
		}
		return static_cast<MeasureParent*>(data)->timeUntilNextUpdate();
	}
	else
	{
		return getParentMeasure(mb)->wdata[mb->type]->numValue;
	}
}

PLUGIN_EXPORT void Finalize(void* data)
{
	if(isParentMeasure(data))
	{
		delete static_cast<MeasureParent*>(data);
	}
	else
	{
		delete static_cast<MeasureChild*>(data);;
	}
}

PLUGIN_EXPORT LPCWSTR GetString(void* data)
{
	auto mb = static_cast<MeasureBase*>(data);
	if(mb->isParentMeasure())
	{
		return mb->source.c_str();
	}
	return getParentMeasure(mb)->wdata[mb->type]->strValue;
}

PLUGIN_EXPORT void ExecuteBang(void* data, LPCWSTR args)
{
	if(isParentMeasure(data))
	{
		auto mp = static_cast<MeasureParent*>(data);
		if(lstrcmpW(args, L"ForceRefresh") == 0)
		{
			mp->forceUpdate();
			RmLog(mp->rmPtr, LOG_NOTICE, L"Notice: ForceRefresh called on parent measure.");
		}
		else
		{
			RmLog(mp->rmPtr, LOG_WARNING, L"Warning: !CommandMeasure used with invalid command. Ignoring command.");
		}
	}
	else
	{
		auto mb = static_cast<MeasureBase*>(data);
		RmLog(mb->rmPtr, LOG_WARNING, L"Warning: !CommandMeasure used on non-parent measure. Ignoring command.");
	}
}

#ifdef _DEBUG
int main()
{
#pragma warning(disable: 4311)
	void *ptr, *ptr2;
	Initialize(&ptr, reinterpret_cast<void*>(1));
	Initialize(&ptr2, reinterpret_cast<void*>(2));
	Reload(ptr, reinterpret_cast<void*>(1), nullptr);
	Reload(ptr2, reinterpret_cast<void*>(2), nullptr);
	Update(ptr);
	Update(ptr2);
	Finalize(ptr);
	Finalize(ptr2);
#pragma warning(default: 4311)
	return 0;
}
#endif // _DEBUG
