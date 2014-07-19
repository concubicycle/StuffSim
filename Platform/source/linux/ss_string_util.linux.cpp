#include "ss_string_util.h"

using namespace StuffSim;

std::string OSStringToCharString(const OSString& stringToConvert)
{
	//have to return a copy of string, because user may make changes to copy 
	//not realizing he is changing the original
	return std::string(stringToConvert);
}

