#ifndef SS_STRING_UTIL_H
#define SS_STRING_UTIL_H

#include "ss_string_util.h"



std::string StuffSim::OSStringToCharString(const OSString& stringToConvert)
{
	//setup converter
	typedef std::codecvt_utf16<wchar_t> convert_type;
	std::wstring_convert<convert_type, wchar_t> converter;

	return converter.to_bytes(stringToConvert);
}

#endif // SS_STRING_UTIL_H