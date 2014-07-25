#include "ss_iostream.h"

namespace StuffSim
{
	std::wostream &select_cout<wchar_t>::cout = std::wcout;
	std::ostream &select_cout<char>::cout = std::cout;

	std::basic_ostream<OSChar>& StuffSim::cout = select_cout<OSChar>::cout;
}

