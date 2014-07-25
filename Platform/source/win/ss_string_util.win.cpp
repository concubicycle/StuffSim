#ifndef SS_STRING_UTIL_H
#define SS_STRING_UTIL_H

#include "ss_string_util.h"



std::string StuffSim::OSStringToCharString(const OSString& stringToConvert)
{

	//setup converter
	typedef std::codecvt_utf8<wchar_t> convert_typeX;
	std::wstring_convert<convert_typeX, wchar_t> converterX;

	return converterX.to_bytes(stringToConvert);
}

#endif // SS_STRING_UTIL_H