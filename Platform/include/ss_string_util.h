#ifndef SS_STRING_FUNCTIONS_H
#define SS_STRING_FUNCTIONS_H

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <codecvt>

#include "system_header.h"

namespace StuffSim
{
	std::string OSStringToCharString(const OSString& stringToConvert);



	/*~~ Inline functions ~~*/

	// trim from start
	inline OSString& ltrim(OSString& s) {
		s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
		return s;
	}

	// trim from end
	inline OSString& rtrim(OSString& s) {
		s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
		return s;
	}

	// trim from both ends
	inline OSString& trim(OSString& s) {
		return ltrim(rtrim(s));
	}
}

#endif
