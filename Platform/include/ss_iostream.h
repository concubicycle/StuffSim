#ifndef SSIM_IOSTREAM_H
#define SSIM_IOSTREAM_H

#include <iostream>
#include "system_header.h"

namespace StuffSim
{
	template<typename T> struct select_cout;

	template<> struct select_cout < char > { static std::ostream &cout; };
	template<> struct select_cout < wchar_t > { static std::wostream &cout; };
	
	// global StuffSim cout
	extern std::basic_ostream<OSChar> &cout;
}

#endif